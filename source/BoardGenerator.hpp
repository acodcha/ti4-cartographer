#pragma once

#include "Aggressions.hpp"
#include "Chronometre.hpp"
#include "Pathway.hpp"
#include "SelectedSystemIds.hpp"
#include "Tiles6Players.hpp"

namespace TI4Cartographer {

template <Layout layout> class BoardGenerator {

public:

  BoardGenerator(const Chronometre& chronometre, const Aggression aggression, const uint64_t maximum_number_of_iterations, const SelectedSystemIds& selected_system_ids) {
    initialize_player_scores();
    initialize_system_ids(aggression, selected_system_ids);
    initialize_tiles();
    message_in_slice_and_equidistant_system_ids();
    iterate(maximum_number_of_iterations);
    messages_final(chronometre);
  }

protected:

  /// \brief Each player's score.
  std::map<uint8_t, double> player_scores_;

  std::vector<std::string> equidistant_system_ids_;

  std::vector<std::string> in_slice_system_ids_;

  std::map<Position, Tile> tiles_;

  uint8_t maximum_distance_to_mecatol_rex_{0};

  void initialize_player_scores() noexcept {
    const uint8_t number_of_players_{number_of_players(layout)};
    for (uint8_t player = 1; player <= number_of_players_; ++player) {
      player_scores_.insert({player, 0.0});
    }
  }

  void initialize_system_ids(const Aggression aggression, const SelectedSystemIds& selected_system_ids) noexcept {
    const uint8_t number_of_equidistant_systems_{number_of_equidistant_systems(Tiles<layout>)};
    std::vector<SystemIdAndScore> system_ids_and_scores;
    for (const std::string& id : selected_system_ids) {
      system_ids_and_scores.push_back({id, Systems.find({id})->score()});
    }
    std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_by_descending_score());
    uint8_t start_index{0};
    switch (aggression) {
      case Aggression::VeryLow:
        start_index = selected_system_ids.size() - number_of_equidistant_systems_;
        break;
      case Aggression::Low:
        start_index = static_cast<uint8_t>(std::floor(selected_system_ids.size() * 0.7 - number_of_equidistant_systems_ * 0.5));
        break;
      case Aggression::Medium:
        start_index = static_cast<uint8_t>(std::round(selected_system_ids.size() * 0.5 - number_of_equidistant_systems_ * 0.5));
        break;
      case Aggression::High:
        start_index = static_cast<uint8_t>(std::ceil(selected_system_ids.size() * 0.3 - number_of_equidistant_systems_ * 0.5));
        break;
      case Aggression::VeryHigh:
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

  void initialize_tiles() noexcept {
    for (const Tile& tile : Tiles<layout>) {
      tiles_.insert({tile.position(), tile});
      if (tile.distance_to_mecatol_rex() > maximum_distance_to_mecatol_rex_) {
        maximum_distance_to_mecatol_rex_ = tile.distance_to_mecatol_rex();
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

  void iterate(const uint64_t maximum_number_of_iterations) {
    std::map<uint8_t, double> best_player_scores;
    std::map<Position, Tile> best_tiles;
    double best_score_imbalance{std::numeric_limits<double>::max()};
    uint64_t number_of_iterations{0};
    uint64_t number_of_valid_boards{0};
    for (uint64_t counter = 0; counter < maximum_number_of_iterations; ++counter) {
      ++number_of_iterations;
      shuffle_system_ids();
      assign_system_ids_to_tiles();
      if (!contains_adjacent_anomalies_or_wormholes_within_inner_layers()) {
        ++number_of_valid_boards;
        calculate_player_scores();
        const double score_imbalance_{score_imbalance()};
        if (score_imbalance_ < best_score_imbalance) {
          best_score_imbalance = score_imbalance_;
          best_player_scores = player_scores_;
          best_tiles = tiles_;
          message("Iteration " + std::to_string(number_of_iterations) + ": Player score imbalance: " + score_imbalance_to_string(score_imbalance_));
          if (score_imbalance_ <= ScoreImbalanceTolerance) {
            break;
          }
        }
      }
    }
    player_scores_ = best_player_scores;
    tiles_ = best_tiles;
    message("Found an optimal game board after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
  }

  void shuffle_system_ids() noexcept {
    std::shuffle(equidistant_system_ids_.begin(), equidistant_system_ids_.end(), RandomEngine);
    std::shuffle(in_slice_system_ids_.begin(), in_slice_system_ids_.end(), RandomEngine);
  }

  void assign_system_ids_to_tiles() {
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (std::map<Position, Tile>::iterator tile = tiles_.begin(); tile != tiles_.end(); ++tile) {
      if (tile->second.is_planetary_anomaly_wormhole_empty()) {
        if (tile->second.is_equidistant()) {
          tile->second.set_system_id(equidistant_system_ids_[equidistant_system_ids_index]);
          ++equidistant_system_ids_index;
        } else {
          tile->second.set_system_id(in_slice_system_ids_[in_slice_system_ids_index]);
          ++in_slice_system_ids_index;
        }
      }
    }
  }

  void calculate_player_scores() noexcept {
    reset_scores();
    add_system_scores();
    add_pathway_to_mecatol_rex_scores();
    add_forward_space_dock_preferred_position_scores();
    add_forward_space_dock_alternate_position_scores();
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
    for (std::map<Position, Tile>::iterator tile = tiles_.begin(); tile != tiles_.end(); ++tile) {
      if (tile->second.is_planetary_anomaly_wormhole_empty()) {
        const double score{Systems.find({tile->second.system_id()})->score() / tile->second.nearest_players().size()};
        for (const uint8_t player : tile->second.nearest_players()) {
          player_scores_[player] += score;
        }
      }
    }
  }

  /// \brief If a player does not have a clear pathway to Mecatol Rex, the score is penalized.
  void add_pathway_to_mecatol_rex_scores() noexcept {
    for (const std::pair<uint8_t, std::set<Pathway>>& player : PlayerPathwaysToMecatolRex<layout>) {
      double best_pathway_score{std::numeric_limits<double>::lowest()};
      for (const Pathway& pathway : player.second) {
        double pathway_score{0.0};
        std::size_t position_counter{0};
        for (const Position& position : pathway) {
          ++position_counter;
          const std::map<Position, Tile>::const_iterator tile{tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
          if (system->contains(Anomaly::Supernova)) {
            if (tile->second.distance_to_mecatol_rex() == 1) {
              pathway_score += -10.0;
            } else {
              pathway_score += -15.0;
            }
          }
          if (system->contains(Anomaly::AsteroidField)) {
            if (tile->second.distance_to_mecatol_rex() == 1) {
              pathway_score += -2.0;
            } else {
              pathway_score += -4.0;
            }
          }
          if (system->contains(Anomaly::Nebula)) {
            if (tile->second.distance_to_mecatol_rex() == 1) {
              pathway_score += 0.0;
            } else {
              pathway_score += -5.0;
            }
          }
          if (system->contains(Anomaly::GravityRift)) {
            if (tile->second.distance_to_mecatol_rex() == 1) {
              pathway_score += -5.0;
            } else {
              pathway_score += -15.0;
            }
          }
        }
        if (pathway_score > best_pathway_score) {
          best_pathway_score = pathway_score;
        }
      }
      player_scores_[player.first] += best_pathway_score;
    }
  }

  void add_forward_space_dock_preferred_position_scores() noexcept {
    for (const std::pair<uint8_t, std::set<Position>>& player : PlayerForwardSpaceDockPreferredPositions<layout>) {
      double best_preferred_position_score{std::numeric_limits<double>::lowest()};
      for (const Position& position : player.second) {
        const std::map<Position, Tile>::const_iterator tile{tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
        double preferred_position_score{0.0};
        if (system->number_of_planets() > 0 && !system->contains(Anomaly::GravityRift)) {
          preferred_position_score = 2.0 * system->space_dock_score();
          if (system->contains(Anomaly::Nebula)) {
            preferred_position_score *= 0.5;
          }
        }
        if (preferred_position_score > best_preferred_position_score) {
          best_preferred_position_score = preferred_position_score;
        }
      }
      player_scores_[player.first] += best_preferred_position_score;
    }
  }

  void add_forward_space_dock_alternate_position_scores() noexcept {
    for (const std::pair<uint8_t, std::set<Position>>& player : PlayerForwardSpaceDockAlternatePositions<layout>) {
      double best_alternate_position_score{std::numeric_limits<double>::lowest()};
      for (const Position& position : player.second) {
        const std::map<Position, Tile>::const_iterator tile{tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
        double alternate_position_score{0.0};
        if (system->number_of_planets() > 0 && !system->contains(Anomaly::GravityRift)) {
          alternate_position_score = system->space_dock_score();
          if (system->contains(Anomaly::Nebula)) {
            alternate_position_score *= 0.5;
          }
        }
        if (alternate_position_score > best_alternate_position_score) {
          best_alternate_position_score = alternate_position_score;
        }
      }
      player_scores_[player.first] += best_alternate_position_score;
    }
  }

  /// \brief If a player's lateral starboard systems protect his/her home system, the score is increased (more than port).
  void add_lateral_starboard_system_scores() noexcept {
    for (const std::pair<uint8_t, std::set<Position>>& player : PlayerLateralStarboardPositions<layout>) {
      for (const Position& position : player.second) {
        const std::map<Position, Tile>::const_iterator tile{tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
        if (system->contains(Anomaly::AsteroidField)) {
          player_scores_[player.first] += 1.5;
        }
        if (system->contains(Anomaly::GravityRift)) {
          player_scores_[player.first] -= 3.0;
        }
        if (system->contains(Anomaly::Nebula)) {
          player_scores_[player.first] += 3.0;
        }
        if (system->contains(Anomaly::Supernova)) {
          player_scores_[player.first] += 4.5;
        }
        if (system->contains_one_or_more_wormholes()) {
          player_scores_[player.first] += -2.0;
        }
      }
    }
  }

  /// \brief If a player's lateral port systems protect his/her home system, the score is increased (but not as much as starboard).
  void add_lateral_port_system_scores() noexcept {
    for (const std::pair<uint8_t, std::set<Position>>& player : PlayerLateralPortPositions<layout>) {
      for (const Position& position : player.second) {
        const std::map<Position, Tile>::const_iterator tile{tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
        if (system->contains(Anomaly::AsteroidField)) {
          player_scores_[player.first] += 1.0;
        }
        if (system->contains(Anomaly::GravityRift)) {
          player_scores_[player.first] -= 2.0;
        }
        if (system->contains(Anomaly::Nebula)) {
          player_scores_[player.first] += 2.0;
        }
        if (system->contains(Anomaly::Supernova)) {
          player_scores_[player.first] += 3.0;
        }
        if (system->contains_one_or_more_wormholes()) {
          player_scores_[player.first] += -2.0;
        }
      }
    }
  }

  void messages_final(const Chronometre& chronometre) const noexcept {
    message("Player scores: " + print_player_scores());
    message("Player score imbalance: " + score_imbalance_to_string(score_imbalance()));
    message("Visualization: " + print_visualization_link());
    message("Tabletop Simulator string: " + print_system_ids());
    message("Runtime: " + chronometre.print());
    message("End of " + ProgramName + ".");
    message(Separator);
  }

  bool contains_adjacent_anomalies_or_wormholes_within_inner_layers() const noexcept {
    std::unordered_set<Position> checked;
    for (std::map<Position, Tile>::const_iterator tile = tiles_.cbegin(); tile != tiles_.cend(); ++tile) {
      if (tile->second.is_planetary_anomaly_wormhole_empty() && checked.find(tile->first) == checked.cend()) {
        // This tile is of the relevant category and has not yet been checked.
        checked.insert(tile->first);
        const std::unordered_set<System>::const_iterator system{Systems.find({tile->second.system_id()})};
        const bool contains_anomaly{system->contains_one_or_more_anomalies()};
        const bool contains_alpha_wormhole{system->contains(Wormhole::Alpha)};
        const bool contains_beta_wormhole{system->contains(Wormhole::Beta)};
        if (tile->second.distance_to_mecatol_rex() < maximum_distance_to_mecatol_rex_ && (contains_anomaly || contains_alpha_wormhole || contains_beta_wormhole)) {
          // This tile is not on the outermost layer and contains one or more anomalies or wormholes.
          const std::set<Position> neighbors{tile->second.position_and_hyperlane_neighbors()};
          for (const Position& position : neighbors) {
            const std::map<Position, Tile>::const_iterator found_neighbor{tiles_.find(position)};
            if (found_neighbor != tiles_.cend()) {
              // This neighboring tile exists on the board.
              if (found_neighbor->second.is_planetary_anomaly_wormhole_empty() && checked.find(found_neighbor->first) == checked.cend()) {
                // This neighboring tile is of the relevant category and has not yet been checked.
                const std::string neighbor_system_id{tiles_.find(position)->second.system_id()};
                const std::unordered_set<System>::const_iterator neighbor_system{Systems.find({neighbor_system_id})};
                const bool neighbor_contains_anomaly{neighbor_system->contains_one_or_more_anomalies()};
                const bool neighbor_contains_alpha_wormhole{neighbor_system->contains(Wormhole::Alpha)};
                const bool neighbor_contains_beta_wormhole{neighbor_system->contains(Wormhole::Beta)};
                if (
                  (contains_anomaly && neighbor_contains_anomaly)
                  || (contains_alpha_wormhole && neighbor_contains_alpha_wormhole)
                  || (contains_beta_wormhole && neighbor_contains_beta_wormhole)
                ) {
                  return true;
                }
              }
            }
          }
        }
      }
    }
    return false;
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
    for (std::map<Position, Tile>::const_iterator tile = tiles_.cbegin(); tile != tiles_.cend(); ++tile) {
      if (!text.empty()) {
        text += " ";
      }
      text += tile->second.system_id();
    }
    return text;
  }

  std::string print_visualization_link() const noexcept {
    std::string text{"https://keeganw.github.io/ti4/?settings=&tiles=18"};
    for (std::map<Position, Tile>::const_iterator tile = tiles_.cbegin(); tile != tiles_.cend(); ++tile) {
      text += "," + tile->second.system_id();
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
