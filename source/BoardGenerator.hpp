#pragma once

#include "BoardAggressions.hpp"
#include "Pathway.hpp"
#include "SelectedSystemIds.hpp"
#include "Tiles6Players.hpp"

namespace TI4Cartographer {

template <BoardLayout board_layout> class BoardGenerator {

public:

  BoardGenerator(const BoardAggression board_aggression, const uint64_t number_of_iterations, const SelectedSystemIds& selected_system_ids) {
    std::sort(tiles_.begin(), tiles_.end());
    initialize_player_scores();
    initialize_system_ids(board_aggression, selected_system_ids);
    message_in_slice_and_equidistant_system_ids();
    iterate(number_of_iterations);
    messages_final();
  }

protected:

  /// \brief Each player's score.
  std::map<uint8_t, double> player_scores_;

  std::vector<std::string> equidistant_system_ids_;

  std::vector<std::string> in_slice_system_ids_;

  std::vector<Tile> tiles_{Tiles<board_layout>};

  void initialize_player_scores() noexcept {
    const uint8_t number_of_players_{number_of_players(board_layout)};
    for (uint8_t player = 1; player <= number_of_players_; ++player) {
      player_scores_.insert({player, 0.0});
    }
  }

  void initialize_system_ids(const BoardAggression board_aggression, const SelectedSystemIds& selected_system_ids) noexcept {
    const uint8_t number_of_equidistant_systems_{number_of_equidistant_systems(tiles_)};
    std::vector<SystemIdAndScore> system_ids_and_scores;
    for (const std::string& id : selected_system_ids) {
      system_ids_and_scores.push_back({id, Systems.find({id})->score()});
    }
    std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_by_descending_score());
    uint8_t start_index{0};
    switch (board_aggression) {
      case BoardAggression::VeryLow:
        start_index = selected_system_ids.size() - number_of_equidistant_systems_;
        break;
      case BoardAggression::Low:
        start_index = static_cast<uint8_t>(std::floor(selected_system_ids.size() * 0.7 - number_of_equidistant_systems_ * 0.5));
        break;
      case BoardAggression::Medium:
        start_index = static_cast<uint8_t>(std::round(selected_system_ids.size() * 0.5 - number_of_equidistant_systems_ * 0.5));
        break;
      case BoardAggression::High:
        start_index = static_cast<uint8_t>(std::ceil(selected_system_ids.size() * 0.3 - number_of_equidistant_systems_ * 0.5));
        break;
      case BoardAggression::VeryHigh:
        start_index = 0;
        break;
    }
    for (uint8_t index = 0; index < system_ids_and_scores.size(); ++index) {
      if (index >= start_index && index < start_index + number_of_equidistant_systems_) {
        equidistant_system_ids_.push_back(system_ids_and_scores[index].id());
      } else {
        in_slice_system_ids_.push_back(system_ids_and_scores[index].id());
      }
    }
  }

  void message_in_slice_and_equidistant_system_ids() const noexcept {
    message("In-Slice System IDs: " + print_in_slice_system_ids());
    message("Equidistant System IDs: " + print_equidistant_system_ids());
    message("In-Slice Systems:");
    for (const std::string& system_id : in_slice_system_ids_) {
      const std::unordered_set<System>::const_iterator found{Systems.find({system_id})};
      if (found != Systems.cend()) {
        message("- " + score_to_string(found->score()) + "  " + found->print());
      }
    }
    message("Equidistant Systems:");
    for (const std::string& system_id : equidistant_system_ids_) {
      const std::unordered_set<System>::const_iterator found{Systems.find({system_id})};
      if (found != Systems.cend()) {
        message("- " + score_to_string(found->score()) + "  " + found->print());
      }
    }
  }

  void iterate(const uint64_t number_of_iterations) {
    std::map<uint8_t, double> best_player_scores;
    std::vector<Tile> best_tiles;
    double best_score_imbalance{std::numeric_limits<double>::max()};
    for (uint64_t counter = 0; counter < number_of_iterations; ++counter) {
      shuffle_system_ids();
      assign_system_ids_to_tiles();
      // TODO: Check if tiles are in a valid configuration (no adjacent anomalies and no adjacent wormholes of the same kind).
      calculate_player_scores();
      const double score_imbalance_{score_imbalance()};
      if (score_imbalance_ < best_score_imbalance) {
        best_score_imbalance = score_imbalance_;
        best_player_scores = player_scores_;
        best_tiles = tiles_;
        message("Iteration " + std::to_string(counter + 1) + ": Player score imbalance: " + score_imbalance_to_string(score_imbalance_));
        if (score_imbalance_ <= ScoreImbalanceTolerance) {
          message("Generated an optimal game board after " + std::to_string(counter + 1) + " iterations.");
          break;
        }
      }
    }
    player_scores_ = best_player_scores;
    tiles_ = best_tiles;
  }

  void shuffle_system_ids() noexcept {
    std::shuffle(equidistant_system_ids_.begin(), equidistant_system_ids_.end(), RandomEngine);
    std::shuffle(in_slice_system_ids_.begin(), in_slice_system_ids_.end(), RandomEngine);
  }

  void assign_system_ids_to_tiles() {
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (std::vector<Tile>::iterator tile = tiles_.begin(); tile != tiles_.end(); ++tile) {
      if (tile->is_planetary_anomaly_wormhole_empty()) {
        if (tile->is_equidistant()) {
          tile->set_system_id(equidistant_system_ids_[equidistant_system_ids_index]);
          ++equidistant_system_ids_index;
        } else {
          tile->set_system_id(in_slice_system_ids_[in_slice_system_ids_index]);
          ++in_slice_system_ids_index;
        }
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
    for (std::map<uint8_t, double>::iterator player_score = player_scores_.begin(); player_score != player_scores_.end(); ++player_score) {
      player_score->second = 0.0;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets an equal fraction of its score.
  void add_system_scores() noexcept {
    for (const Tile& tile : tiles_) {
      if (tile.is_planetary_anomaly_wormhole_empty()) {
        const double score{Systems.find({tile.system_id()})->score() / tile.nearest_players().size()};
        for (const uint8_t player_index : tile.nearest_players()) {
          player_scores_[player_index] += score;
        }
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

  void messages_final() const noexcept {
    message("Player scores: " + print_player_scores());
    message("Player score imbalance: " + score_imbalance_to_string(score_imbalance()));
    message("System IDs: " + print_system_ids());
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

  std::string print_in_slice_system_ids() const noexcept {
    std::string text;
    for (const std::string& in_slice_system_id : in_slice_system_ids_) {
      if (!text.empty()) {
        text += " ";
      }
      text += in_slice_system_id;
    }
    return text;
  }

  std::string print_equidistant_system_ids() const noexcept {
    std::string text;
    for (const std::string& equidistant_system_id : equidistant_system_ids_) {
      if (!text.empty()) {
        text += " ";
      }
      text += equidistant_system_id;
    }
    return text;
  }



}; // class BoardGenerator

} // namespace TI4Cartographer
