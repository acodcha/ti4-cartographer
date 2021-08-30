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
    const GameVersion game_version,
    const Layout layout,
    const Aggression aggression,
    const uint64_t maximum_number_of_iterations
  ) noexcept :
    BoardInitializer(layout),
    selected_system_ids_(game_version, layout, aggression, static_cast<uint8_t>(this->equidistant_positions_.size()))
  {
    initialize_player_scores();
    assign_system_ids_to_tiles_simple();
    calculate_player_scores();
    iterate(maximum_number_of_iterations);
  }

private:

  SelectedSystemIds selected_system_ids_;

  std::map<Player, float> player_scores_;

  void initialize_player_scores() noexcept {
    for (const Player player : this->players_) {
      player_scores_.insert({player, 0.0});
    }
  }

  void iterate(const uint64_t maximum_number_of_iterations) {





  }

  void assign_system_ids_to_tiles_simple() {
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (std::unordered_map<Position, Tile>::iterator position_and_tile = positions_to_tiles_.begin(); position_and_tile != positions_to_tiles_.end(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
        if (position_and_tile->second.is_equidistant()) {
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

  void calculate_player_scores() noexcept {
    reset_scores();
    add_base_system_scores();
    add_lateral_system_scores();
    add_pathway_to_mecatol_rex_scores();
    add_space_dock_preferred_position_scores();
    add_space_dock_alternate_position_scores();
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
        const std::unordered_map<Position, std::set<Player>>::const_iterator position_to_relevant_players{this->positions_to_relevant_players_.find(position_and_tile->first)};
        if (position_to_relevant_players != this->positions_to_relevant_players_.cend()) {
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
    for (const std::pair<Player, Position>& player_and_position : this->players_to_lateral_positions_) {
      const std::unordered_map<Position, Tile>::const_iterator position_and_tile{this->positions_to_tiles_.find(player_and_position.second)};
      const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
      if (system->contains(Anomaly::AsteroidField)) {
        player_scores_[player_and_position.first] += 1.0;
      }
      if (system->contains(Anomaly::GravityRift)) {
        player_scores_[player_and_position.first] -= 2.0;
      }
      if (system->contains(Anomaly::Nebula)) {
        player_scores_[player_and_position.first] += 2.0;
      }
      if (system->contains(Anomaly::Supernova)) {
        player_scores_[player_and_position.first] += 3.0;
      }
      if (system->contains_one_or_more_wormholes()) {
        player_scores_[player_and_position.first] += -2.0;
      }
    }
  }

  /// \brief If a player does not have a clear pathway to Mecatol Rex, the score is penalized.
  void add_pathway_to_mecatol_rex_scores() noexcept {





  }

  void add_space_dock_preferred_position_scores() noexcept {





  }

  void add_space_dock_alternate_position_scores() noexcept {





  }

}; // class Board

} // namespace TI4Cartographer
