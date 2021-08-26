#pragma once

#include "DistanceFromPlayerHome.hpp"
#include "Layouts.hpp"
#include "Pathway.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief All the tiles on the board.
template <Layout layout> const std::set<Tile> LayoutTiles;

/// \brief Arrangement of tiles that form a board.
class Tiles {

public:

  Tiles() noexcept {}

  Tiles(const std::set<Tile>& tiles) noexcept {
    initialize_tiles(tiles);
    initialize_mecatol_rex_position();
    initialize_players_home_positions();
    initialize_distances_from_mecatol_rex();
    initialize_distances_from_player_homes();
    initialize_equidistant_positions();
    initialize_in_slice_positions();
    initialize_lateral_positions();
  }

  const std::set<Position>& equidistant_positions() const noexcept {
    return equidistant_positions_;
  }

  const uint8_t number_of_equidistant_positions() const noexcept {
    return equidistant_positions_.size();
  }

  std::set<Position> in_slice_positions(const uint8_t player) const noexcept {
    const std::pair<std::multimap<uint8_t, Position>::const_iterator, std::multimap<uint8_t, Position>::const_iterator> range{
      players_to_in_slice_positions_.equal_range(player)
    };
    std::set<Position> positions;
    for (
      std::multimap<uint8_t, Position>::const_iterator player_and_in_slice_position = range.first;
      player_and_in_slice_position != range.second;
      ++player_and_in_slice_position
    ) {
      positions.insert(player_and_in_slice_position->second);
    }
    return positions;
  }

  uint8_t number_of_in_slice_positions(const uint8_t player) const noexcept {
    const std::pair<std::multimap<uint8_t, Position>::const_iterator, std::multimap<uint8_t, Position>::const_iterator> range{
      players_to_in_slice_positions_.equal_range(player)
    };
    uint8_t number{0};
    for (
      std::multimap<uint8_t, Position>::const_iterator player_and_in_slice_position = range.first;
      player_and_in_slice_position != range.second;
      ++player_and_in_slice_position
    ) {
      ++number;
    }
    return number;
  }

  uint8_t number_of_in_slice_positions() const noexcept {
    return players_to_in_slice_positions_.size();
  }

private:

  std::set<Position> sorted_positions_;

  std::unordered_map<Position, Tile> positions_to_tiles_;

  Position mecatol_rex_position_;

  std::map<uint8_t, Position> players_to_home_positions_;

  std::unordered_map<Position, uint8_t> positions_to_distances_from_mecatol_rex_;

  std::unordered_multimap<Position, DistanceFromPlayerHome> positions_to_distances_from_player_homes_;

  std::set<Position> equidistant_positions_;

  std::multimap<uint8_t, Position> players_to_in_slice_positions_;

  std::multimap<uint8_t, Position> players_to_lateral_positions_;

  // TODO: Pathways to Mecatol Rex.

  // TODO: Preferred and alternate space dock positions.

  void initialize_tiles(const std::set<Tile>& tiles) noexcept {
    for (const Tile& tile : tiles) {
      sorted_positions_.insert(tile.position());
      positions_to_tiles_.insert({tile.position(), tile});
    }
  }

  void initialize_mecatol_rex_position() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.system_id() == MecatolRexSystemId) {
        mecatol_rex_position_ = position_and_tile.first;
      }
    }
  }

  void initialize_players_home_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.home_player().has_value()) {
        players_to_home_positions_.insert({position_and_tile.second.home_player().value(), position_and_tile.first});
      }
    }
  }

  void initialize_distances_from_mecatol_rex() noexcept {
    positions_to_distances_from_mecatol_rex_ = positions_and_distances_from_target(mecatol_rex_position_);
  }

  void initialize_distances_from_player_homes() noexcept {
    for (const std::pair<uint8_t, Position>& player_and_home_position : players_to_home_positions_) {
      for (const std::pair<Position, uint8_t>& position_and_distance_from_target : positions_and_distances_from_target(player_and_home_position.second)) {
        positions_to_distances_from_player_homes_.insert({position_and_distance_from_target.first, {player_and_home_position.first, position_and_distance_from_target.second}});
      }
    }
  }

  /// \brief If at least two players' homes are the same distance from a given position, then that position is an equidistant position.
  void initialize_equidistant_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_empty()) {
        const std::pair<std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator, std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator> range{positions_to_distances_from_player_homes_.equal_range(position_and_tile.first)};
        std::set<uint8_t> distances_from_homes;
        for (std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator position_and_distance = range.first; position_and_distance != range.second; ++position_and_distance) {
          const std::set<uint8_t>::const_iterator found{distances_from_homes.find(position_and_distance->second.distance_from_home())};
          if (found != distances_from_homes.cend()) {
            // This distance-from-home for this player is the same as at least one other player, so this position is an equidistant position.
            // We can move on to the next position.
            equidistant_positions_.insert(position_and_tile.first);
            break;
          } else {
            distances_from_homes.insert(position_and_distance->second.distance_from_home());
          }
        }
      }
    }
  }

  /// \brief In-slice positions are closer to a given player's home than to all other players' homes.
  void initialize_in_slice_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (
        position_and_tile.second.is_planetary_anomaly_wormhole_empty()
        && equidistant_positions_.find(position_and_tile.first) == equidistant_positions_.cend()
      ) {
        // In this case, this position is not an equidistant position, so it must be an in-slice position.
        // Find the player whose slice this position lies in.
        const std::pair<std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator, std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator> range{positions_to_distances_from_player_homes_.equal_range(position_and_tile.first)};
        uint8_t minimum_distance_from_home{std::numeric_limits<uint8_t>::max()};
        uint8_t player{0};
        for (std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator position_and_distance = range.first; position_and_distance != range.second; ++position_and_distance) {
          if (position_and_distance->second.distance_from_home() < minimum_distance_from_home) {
            minimum_distance_from_home = position_and_distance->second.distance_from_home();
            player = position_and_distance->second.player();;
          }
        }
        players_to_in_slice_positions_.insert({player, position_and_tile.first});
      }
    }
  }

  void initialize_lateral_positions() noexcept {
    for (const std::pair<uint8_t, Position>& player_and_home_position : players_to_home_positions_) {
      const uint8_t home_distance_to_mecatol_rex{positions_to_distances_from_mecatol_rex_.find(player_and_home_position.second)->second};
      for (const Position& position : positions_to_tiles_.find(player_and_home_position.second)->second.position_and_hyperlane_neighbors()) {
        // This position is a neighbor of this player's home, but it may or  may not exist on the board.
        const std::unordered_map<Position, uint8_t>::const_iterator found{positions_to_distances_from_mecatol_rex_.find(position)};
        if (found != positions_to_distances_from_mecatol_rex_.cend()) {
          // This position exists on the board.
          if (found->second >= home_distance_to_mecatol_rex) {
            // This position is at an equal or greater distance to Mecatol Rex than this player's home.
            // Therefore, this position is a lateral position for this player.
            players_to_lateral_positions_.insert({player_and_home_position.first, position});
          }
        }
      }
    }
  }

  std::unordered_map<Position, uint8_t> positions_and_distances_from_target(const Position& target_position) const noexcept {
    std::unordered_map<Position, uint8_t> position_to_distance_from_target;
    uint8_t distance_from_target_position{0};
    std::unordered_set<Position> visited;
    std::unordered_set<Position> current_neighbors{target_position};
    std::unordered_set<Position> next_neighbors;
    while (!current_neighbors.empty() || !next_neighbors.empty()) {
      for (const Position& current_position : current_neighbors) {
        const std::unordered_map<Position, Tile>::const_iterator current_position_and_tile{positions_to_tiles_.find(current_position)};
        if (
          current_position_and_tile != positions_to_tiles_.cend()
          && !current_position_and_tile->second.is_hyperlane()
          && visited.find(current_position) == visited.cend()
        ) {
          // The current position exists and has not yet been visited.
          visited.insert(current_position);
          position_to_distance_from_target.insert({current_position, distance_from_target_position});
          const std::set<Position> next_positions{current_position_and_tile->second.position_and_hyperlane_neighbors()};
          for (const Position& next_position : next_positions) {
            const std::unordered_map<Position, Tile>::const_iterator next_position_and_tile{positions_to_tiles_.find(next_position)};
            if (
              next_position_and_tile != positions_to_tiles_.cend()
              && !next_position_and_tile->second.is_hyperlane()
              && visited.find(next_position) == visited.cend()
            ) {
              // The next position exists and has not been visited.
              next_neighbors.insert(next_position);
            }
          }
        }
      }
      ++distance_from_target_position;
      current_neighbors.clear();
      current_neighbors = next_neighbors;
      next_neighbors.clear();
    }
    return position_to_distance_from_target;
  }

}; // class Tiles

uint8_t number_of_in_slice_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_in_a_slice() && tile.is_planetary_anomaly_wormhole_empty()) {
      ++number;
    }
  }
  return number;
}

uint8_t number_of_equidistant_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_equidistant() && tile.is_planetary_anomaly_wormhole_empty()) {
      ++number;
    }
  }
  return number;
}

/// \brief Each player has one or more pathways to Mecatol Rex.
template <Layout layout> const std::map<uint8_t, std::set<Pathway>> PlayerPathwaysToMecatolRex;

template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockPreferredPositions;

template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockAlternatePositions;

/// \brief Each player has one or more tile positions that are 1 lateral to starboard of his/her home system.
template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerLateralStarboardPositions;

/// \brief Each player has one or more tile positions that are 1 lateral to port of his/her home system.
template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerLateralPortPositions;

} // namespace TI4Cartographer
