#pragma once

#include "Aggressions.hpp"
#include "BoardInitializer.hpp"
#include "Chronometre.hpp"
#include "SelectedSystemIds.hpp"

namespace TI4Cartographer {

/// \brief Arrangement of tiles that form a board.
class Board : public BoardInitializer {

public:

  Board(
    const Chronometre& chronometre,
    const GameVersion game_version,
    const Layout layout,
    const Aggression aggression,
    const uint64_t maximum_number_of_iterations
  ) noexcept :
    BoardInitializer(layout),
    selected_system_ids_(game_version, layout, aggression, static_cast<uint8_t>(equidistant_positions_.size()))
  {
    initialize_player_scores();
    iterate(maximum_number_of_iterations);
    verbose_message("Player scores: " + print_player_scores());
    verbose_message("Player score imbalance: " + score_imbalance_to_string(score_imbalance()));
    verbose_message("Visualization: " + print_visualization_link());
    verbose_message("Tabletop Simulator string: " + print_tabletop_simulator_string());
    quiet_message(print_tabletop_simulator_string());
    verbose_message("Runtime: " + chronometre.print());
  }

private:

  SelectedSystemIds selected_system_ids_;

  std::map<Player, float> player_scores_;

  void initialize_player_scores() noexcept {
    for (const Player player : players_) {
      player_scores_.insert({player, 0.0});
    }
  }

  void iterate(const uint64_t maximum_number_of_iterations) {
    std::unordered_map<Position, Tile> best_positions_to_tiles{positions_to_tiles_};
    std::map<Player, float> best_player_scores{player_scores_};
    float best_score_imbalance{std::numeric_limits<float>::max()};
    uint64_t number_of_iterations{0};
    uint64_t number_of_valid_boards{0};
    for (uint64_t counter = 0; counter < maximum_number_of_iterations; ++counter) {
      ++number_of_iterations;
      selected_system_ids_.shuffle();
      assign_system_ids_to_tiles_simple();
      if (!contains_adjacent_anomalies_or_wormholes_within_inner_layers()) {
        ++number_of_valid_boards;
        calculate_player_scores();
        const float score_imbalance_{score_imbalance()};
        if (score_imbalance_ < best_score_imbalance) {
          best_positions_to_tiles = positions_to_tiles_;
          best_player_scores = player_scores_;
          best_score_imbalance = score_imbalance_;
          verbose_message("Iteration " + std::to_string(number_of_iterations) + ": Player score imbalance: " + score_imbalance_to_string(score_imbalance_));
          if (score_imbalance_ <= ScoreImbalanceTolerance) {
            break;
          }
        }
      }
    }
    positions_to_tiles_ = best_positions_to_tiles;
    player_scores_ = best_player_scores;
    verbose_message("Found an optimal game board after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
  }

  void assign_system_ids_to_tiles_simple() {
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (std::unordered_map<Position, Tile>::iterator position_and_tile = positions_to_tiles_.begin(); position_and_tile != positions_to_tiles_.end(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
        if (equidistant_positions_.find(position_and_tile->first) != equidistant_positions_.cend()) {
          position_and_tile->second.set_system_id(selected_system_ids_.equidistant()[equidistant_system_ids_index]);
          ++equidistant_system_ids_index;
        } else {
          position_and_tile->second.set_system_id(selected_system_ids_.in_slice()[in_slice_system_ids_index]);
          ++in_slice_system_ids_index;
        }
      }
    }
  }

  void assign_system_ids_to_tiles_smart() {





  }

  bool contains_adjacent_anomalies_or_wormholes_within_inner_layers() const noexcept {
    std::unordered_set<Position> checked;
    for (std::unordered_map<Position, Tile>::const_iterator position_and_tile = positions_to_tiles_.cbegin(); position_and_tile != positions_to_tiles_.cend(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty() && checked.find(position_and_tile->first) == checked.cend()) {
        // This tile is of the relevant category and has not yet been checked.
        checked.insert(position_and_tile->first);
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        const bool contains_anomaly{system->contains_one_or_more_anomalies()};
        const bool contains_alpha_wormhole{system->contains(Wormhole::Alpha)};
        const bool contains_beta_wormhole{system->contains(Wormhole::Beta)};
        if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second < maximum_distance_from_mecatol_rex_ && (contains_anomaly || contains_alpha_wormhole || contains_beta_wormhole)) {
          // This tile is not on the outermost layer and contains one or more anomalies or wormholes.
          const std::set<Position> neighbors{position_and_tile->second.position_and_hyperlane_neighbors()};
          for (const Position& position : neighbors) {
            const std::unordered_map<Position, Tile>::const_iterator found_neighbor{positions_to_tiles_.find(position)};
            if (found_neighbor != positions_to_tiles_.cend()) {
              // This neighboring tile exists on the board.
              if (found_neighbor->second.is_planetary_anomaly_wormhole_or_empty() && checked.find(found_neighbor->first) == checked.cend()) {
                // This neighboring tile is of the relevant category and has not yet been checked.
                const std::string neighbor_system_id{positions_to_tiles_.find(position)->second.system_id()};
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

  void calculate_player_scores() noexcept {
    reset_scores();
    add_base_system_scores();
    add_lateral_system_scores();
    add_mecatol_rex_pathway_scores();
    add_preferred_position_scores();
    add_alternate_position_scores();
  }

  void reset_scores() noexcept {
    for (std::map<Player, float>::iterator player_score = player_scores_.begin(); player_score != player_scores_.end(); ++player_score) {
      player_score->second = 0.0;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets an equal fraction of its score.
  void add_base_system_scores() noexcept {
    for (std::unordered_map<Position, Tile>::iterator position_and_tile = positions_to_tiles_.begin(); position_and_tile != positions_to_tiles_.end(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_map<Position, std::set<Player>>::const_iterator position_to_relevant_players{positions_to_relevant_players_.find(position_and_tile->first)};
        if (position_to_relevant_players != positions_to_relevant_players_.cend()) {
          const float score{Systems.find({position_and_tile->second.system_id()})->score()};
          const uint8_t number_of_relevant_players{static_cast<uint8_t>(position_to_relevant_players->second.size())};
          const float score_per_player{score / number_of_relevant_players};
          for (const Player& player : position_to_relevant_players->second) {
            player_scores_[player] += score_per_player;
          }
        }
      }
    }
  }

  /// \brief If a player's lateral systems protect his/her home system, the score is increased.
  void add_lateral_system_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_lateral_positions : players_to_lateral_positions_) {
      for (const Position& position : player_and_lateral_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (system->contains(Anomaly::AsteroidField)) {
          player_scores_[player_and_lateral_positions.first] += 1.0;
        }
        if (system->contains(Anomaly::GravityRift)) {
          player_scores_[player_and_lateral_positions.first] += -3.0;
        }
        if (system->contains(Anomaly::Nebula)) {
          player_scores_[player_and_lateral_positions.first] += 2.0;
        }
        if (system->contains(Anomaly::Supernova)) {
          player_scores_[player_and_lateral_positions.first] += 3.0;
        }
        if (system->contains_one_or_more_wormholes()) {
          player_scores_[player_and_lateral_positions.first] += -2.0;
        }
      }
    }
  }

  /// \brief If a player does not have a clear pathway to Mecatol Rex, the score is penalized.
  void add_mecatol_rex_pathway_scores() noexcept {
    for (const std::pair<Player, std::set<Pathway>>& player_and_mecatol_rex_pathways : players_to_mecatol_rex_pathways_) {
      if (!player_and_mecatol_rex_pathways.second.empty()) {
        float best_pathway_score{std::numeric_limits<float>::lowest()};
        for (const Pathway& pathway : player_and_mecatol_rex_pathways.second) {
          float pathway_score{0.0};
          for (const Position& position : pathway) {
            const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
            const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
            if (system->contains(Anomaly::Supernova)) {
              pathway_score += -15.0;
            }
            if (system->contains(Anomaly::AsteroidField)) {
              pathway_score += -3.0;
            }
            if (system->contains(Anomaly::Nebula)) {
              if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second <= Distance{1}) {
                pathway_score += 0.0;
              } else {
                pathway_score += -5.0;
              }
            }
            if (system->contains(Anomaly::GravityRift)) {
              if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second <= Distance{1}) {
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
        player_scores_[player_and_mecatol_rex_pathways.first] += best_pathway_score;
      }
    }
  }

  /// \brief If a player can construct a space dock on at least one of their preferred positions, the score is increased.
  void add_preferred_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_preferred_position : players_to_preferred_positions_) {
      if (!player_and_preferred_position.second.empty()) {
        float best_preferred_position_score{std::numeric_limits<float>::lowest()};
        for (const Position& position : player_and_preferred_position.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          float preferred_position_score{0.0};
          if (system->planets().size() > 0 && !system->contains(Anomaly::GravityRift)) {
            preferred_position_score = 2.0 * system->space_dock_score();
            if (system->contains(Anomaly::Nebula)) {
              preferred_position_score *= 0.5;
            }
          }
          if (preferred_position_score > best_preferred_position_score) {
            best_preferred_position_score = preferred_position_score;
          }
        }
        player_scores_[player_and_preferred_position.first] += best_preferred_position_score;
      }
    }
  }

  /// \brief If a player can construct a space dock on at least one of their alternate positions, the score is increased.
  void add_alternate_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_alternate_position : players_to_alternate_positions_) {
      if (!player_and_alternate_position.second.empty()) {
        float best_alternate_position_score{std::numeric_limits<float>::lowest()};
        for (const Position& position : player_and_alternate_position.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          float alternate_position_score{0.0};
          if (system->planets().size() > 0 && !system->contains(Anomaly::GravityRift)) {
            alternate_position_score = system->space_dock_score();
            if (system->contains(Anomaly::Nebula)) {
              alternate_position_score *= 0.5;
            }
          }
          if (alternate_position_score > best_alternate_position_score) {
            best_alternate_position_score = alternate_position_score;
          }
        }
        player_scores_[player_and_alternate_position.first] += best_alternate_position_score;
      }
    }
  }

  float score_imbalance() const noexcept {
    float maximum_score{std::numeric_limits<float>::lowest()};
    float minimum_score{std::numeric_limits<float>::max()};
    for (const std::pair<Player, float> player_score : player_scores_) {
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
    for (const std::pair<Player, float> player_score : player_scores_) {
      if (!text.empty()) {
        text += " ";
      }
      text += score_to_string(player_score.second);
    }
    return text;
  }

  std::string print_tabletop_simulator_string() const noexcept {
    // Order the tiles by their position.
    std::set<Tile> tiles;
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      tiles.insert(position_and_tile.second);
    }
    // Print the tiles.
    std::string text;
    for (const Tile& tile : tiles) {
      if (tile.system_id() != MecatolRexSystemId) {
        if (!text.empty()) {
          text += " ";
        }
        text += tile.system_id();
      }
    }
    return text;
  }

  std::string print_visualization_link() const noexcept {
    // Order the tiles by their position.
    std::set<Tile> tiles;
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      tiles.insert(position_and_tile.second);
    }
    const std::string prefix{"https://keeganw.github.io/ti4/?settings=&tiles="};
    std::string tiles_text;
    for (const Tile& tile : tiles) {
      if (!tiles_text.empty()) {
        tiles_text += ",";
      }
      tiles_text += tile.system_id();
    }
    return prefix + tiles_text;
  }

}; // class Board

} // namespace TI4Cartographer
