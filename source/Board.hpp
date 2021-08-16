#pragma once

#include "BoardAggressions.hpp"
#include "Pathway.hpp"
#include "SelectedSystemIds.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief Abstract template base class for the game board.
class Board {

public:

  Board(const BoardLayout board_layout) noexcept {
    const uint8_t number_of_players_{number_of_players(board_layout)};
    for (uint8_t player = 1; player <= number_of_players_; ++player) {
      player_scores_.insert({player, 0.0});
    }
  }

  const std::vector<Tile>& tiles() const noexcept {
    return tiles_;
  }

protected:

  /// \brief Each player's score. The vector index is the player index.
  std::map<uint8_t, double> player_scores_;

  /// \brief This contains all the tiles on the board. Correctly ordered after initialization.
  std::vector<Tile> tiles_;

  /// \brief Each player has one or more pathways to Mecatol Rex.
  std::map<uint8_t, std::vector<Pathway>> player_pathways_to_mecatol_rex;

  /// \brief Each player has one or more tile positions that are 1 ahead of his/her home system.
  std::map<uint8_t, std::set<Position>> player_forward_positions_;

  /// \brief Each player has one or more tile positions that are 1 lateral to starboard of his/her home system.
  std::map<uint8_t, std::set<Position>> player_lateral_starboard_positions_;

  /// \brief Each player has one or more tile positions that are 1 lateral to port of his/her home system.
  std::map<uint8_t, std::set<Position>> player_lateral_port_positions_;

  std::vector<std::string> equidistant_system_ids_;

  std::vector<std::string> slice_system_ids_;

  void run(const BoardAggression board_aggression, const uint64_t number_of_iterations, const SelectedSystemIds& selected_system_ids) noexcept {
    initialize_tiles();
    std::sort(tiles_.begin(), tiles_.end());
    initialize_player_pathways_to_mecatol_rex();
    initialize_player_forward_positions();
    initialize_player_lateral_starboard_positions();
    initialize_player_lateral_port_positions();
    initialize_system_ids(board_aggression, selected_system_ids);
    iterate(number_of_iterations);
    finalize();
  }

  virtual void initialize_tiles() noexcept = 0;

  virtual void initialize_player_pathways_to_mecatol_rex() noexcept = 0;

  virtual void initialize_player_forward_positions() noexcept = 0;

  virtual void initialize_player_lateral_starboard_positions() noexcept = 0;

  virtual void initialize_player_lateral_port_positions() noexcept = 0;

  virtual void initialize_system_ids(const BoardAggression board_aggression, const SelectedSystemIds& selected_system_ids) noexcept {
    uint8_t number_of_equidistant_systems{0};
    for (const Tile& tile : tiles_) {
      if (tile.is_equidistant()) {
        ++number_of_equidistant_systems;
      }
    }
    std::vector<SystemIdAndScore> system_ids_and_scores;
    for (const std::string& id : selected_system_ids) {
      system_ids_and_scores.push_back({id, Systems.find({id})->score()});
    }
    std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_descending());
    uint8_t start_index{0};
    switch (board_aggression) {
      case BoardAggression::VeryLow:
        start_index = selected_system_ids.size() - number_of_equidistant_systems;
        break;
      case BoardAggression::Low:
        start_index = static_cast<uint8_t>(std::floor(selected_system_ids.size() * 0.7 - number_of_equidistant_systems * 0.5));
        break;
      case BoardAggression::Medium:
        start_index = static_cast<uint8_t>(std::round(selected_system_ids.size() * 0.5 - number_of_equidistant_systems * 0.5));
        break;
      case BoardAggression::High:
        start_index = static_cast<uint8_t>(std::ceil(selected_system_ids.size() * 0.3 - number_of_equidistant_systems * 0.5));
        break;
      case BoardAggression::VeryHigh:
        start_index = 0;
        break;
    }
    for (uint8_t index = 0; index < system_ids_and_scores.size(); ++index) {
      if (index >= start_index && start_index < start_index + number_of_equidistant_systems) {
        equidistant_system_ids_.push_back(system_ids_and_scores[index].id());
      } else {
        slice_system_ids_.push_back(system_ids_and_scores[index].id());
      }
    }
  }

  void iterate(const uint64_t number_of_iterations) noexcept {
    std::map<uint8_t, double> best_player_scores;
    std::vector<Tile> best_tiles;
    double best_score_imbalance{std::numeric_limits<double>::max()};
    for (uint64_t counter = 0; counter < number_of_iterations; ++counter) {
      shuffle_system_ids();
      assign_system_ids_to_tiles();
      calculate_player_scores();
      const double score_imbalance_{score_imbalance()};
      if (score_imbalance_ < best_score_imbalance) {
        best_score_imbalance = score_imbalance_;
        best_player_scores = player_scores_;
        best_tiles = tiles_;
        message("Iteration " + std::to_string(counter + 1) + ": Player score imbalance: " + score_to_string(score_imbalance()));
        if (score_imbalance_ <= ScoreImbalanceTolerance) {
          message("Generated an optimal game board after " + std::to_string(counter + 1) + " iterations.");
          break;
        }
      }
    }
    player_scores_ = best_player_scores;
    tiles_ = best_tiles;
  }

  void finalize() const noexcept {
    message("Player scores: " + print_player_scores());
    message("Player score imbalance: " + score_to_string(score_imbalance()));
    message("System IDs: " + print_system_ids());
  }

  void shuffle_system_ids() noexcept {
    std::shuffle(equidistant_system_ids_.begin(), equidistant_system_ids_.end(), RandomEngine);
    std::shuffle(slice_system_ids_.begin(), slice_system_ids_.end(), RandomEngine);
  }

  void assign_system_ids_to_tiles() noexcept {
    uint8_t equidistant_system_ids_index{0};
    uint8_t slice_system_ids_index{0};
    for (Tile& tile : tiles_) {
      if (tile.is_equidistant()) {
        tile.set_system_id(equidistant_system_ids_[equidistant_system_ids_index]);
        ++equidistant_system_ids_index;
      } else {
        tile.set_system_id(equidistant_system_ids_[slice_system_ids_index]);
        ++slice_system_ids_index;
      }
    }
  }

  void calculate_player_scores() noexcept {
    reset_scores();
    add_system_scores();
    add_pathway_to_mecatol_rex_scores();
    add_forward_space_dock_scores();
    add_lateral_starboard_system_scores();
    add_lateral_port_system_scores();
  }

  void reset_scores() noexcept {
    for (std::size_t i = 1; i <= player_scores_.size(); ++i) {
      player_scores_[i] = 0.0;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets an equal fraction of its score.
  void add_system_scores() noexcept {
    for (const Tile& tile : tiles_) {
      const double score{Systems.find({tile.system_id()})->score() / tile.nearest_players().size()};
      for (const uint8_t player_index : tile.nearest_players()) {
        player_scores_[player_index] += score;
      }
    }
  }

  /// \brief If a player does not have a clear pathway to Mecatol Rex, the score is penalized.
  void add_pathway_to_mecatol_rex_scores() noexcept {





  }

  /// \brief If a player does not have a good planet on which to build a forward space dock on his/her path to Mecatol Rex, the score is penalized.
  void add_forward_space_dock_scores() noexcept {





  }

  /// \brief If a player's lateral starboard systems protect his/her home system, the score is increased (more than port).
  void add_lateral_starboard_system_scores() noexcept {





  }

  /// \brief If a player's lateral port systems protect his/her home system, the score is increased (but not as much as starboard).
  void add_lateral_port_system_scores() noexcept {





  }

  double score_imbalance() const noexcept {
    double maximum_score{std::numeric_limits<double>::lowest()};
    double minimum_score{std::numeric_limits<double>::max()};
    for (const std::pair<uint8_t, double> player_score : player_scores_) {
      if (player_score.second > maximum_score) {
        maximum_score = player_score.second;
      }
      if (player_score.second < minimum_score) {
        minimum_score = player_score.second;
      }
    }
    return maximum_score - minimum_score;
  }

  std::string print_player_scores() const noexcept {
    std::string text;
    for (const std::pair<uint8_t, double> player_score : player_scores_) {
      if (!text.empty()) {
        text += " ";
      }
      text += score_to_string(player_score.second);
    }
    return text;
  }

  std::string print_system_ids() const noexcept {
    std::string text;
    for (const Tile& tile : tiles_) {
      if (!text.empty()) {
        text += " ";
      }
      text += tile.system_id();
    }
    return text;
  }

}; // class Board

} // namespace TI4Cartographer
