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
    initialize_pathways_to_mecatol_rex();
    initialize_space_dock_positions();
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

  /// \brief Collection of tiles that form the board, indexed by their positions.
  std::unordered_map<Position, Tile> positions_to_tiles_;

  Position mecatol_rex_position_;

  std::map<uint8_t, Position> players_to_home_positions_;

  std::unordered_map<Position, uint8_t> positions_to_distances_from_mecatol_rex_;

  std::unordered_multimap<Position, DistanceFromPlayerHome> positions_to_distances_from_player_homes_;

  /// \brief Group of positions that are equidistant to 2 or more players' homes.
  std::set<Position> equidistant_positions_;

  /// \brief Group of in-slice positions for each player, i.e. positions that are nearer to that player's home than other players' homes.
  std::multimap<uint8_t, Position> players_to_in_slice_positions_;

  /// \brief Group of lateral positions for each player, i.e. positions that are not nearer to Mecatol Rex than each player's home.
  std::multimap<uint8_t, Position> players_to_lateral_positions_;

  /// \brief Pathways to Mecatol Rex may include equidistant positions and always end with the Mecatol Rex position itself.
  std::multimap<uint8_t, Pathway> players_to_pathways_to_mecatol_rex_;

  std::multimap<uint8_t, Position> players_to_preferred_space_dock_positions_;

  std::multimap<uint8_t, Position> players_to_alternate_space_dock_positions_;

  void initialize_tiles(const std::set<Tile>& tiles) noexcept {
    for (const Tile& tile : tiles) {
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
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
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

  /// \brief In-slice positions are nearer to a given player's home than to all other players' homes.
  void initialize_in_slice_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (
        position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()
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
      for (const Position& neighbor_of_home : positions_to_tiles_.find(player_and_home_position.second)->second.position_and_hyperlane_neighbors()) {
        // This position is a neighbor of this player's home, but it may or may not exist on the board.
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor_of_home)};
        const std::unordered_map<Position, uint8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor_of_home)};
        if (
          neighbor_position_and_tile != positions_to_tiles_.cend()
          && neighbor_position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()
          && neighbor_position_and_distance != positions_to_distances_from_mecatol_rex_.cend()
          && neighbor_position_and_distance->second >= home_distance_to_mecatol_rex
        ) {
          // This position exists on the board, is of the correct system category, and is at an equal or greater distance from Mecatol Rex than this player's home.
          // Therefore, this position is a lateral position for this player.
          players_to_lateral_positions_.insert({player_and_home_position.first, neighbor_of_home});
        }
      }
    }
  }

  void initialize_pathways_to_mecatol_rex() noexcept {
    for (const std::pair<uint8_t, Position>& player_and_home_position : players_to_home_positions_) {
      const uint8_t home_distance_to_mecatol_rex{positions_to_distances_from_mecatol_rex_.find(player_and_home_position.second)->second};
      std::set<Pathway> pathways;
      for (const Position& neighbor_of_home : positions_to_tiles_.find(player_and_home_position.second)->second.position_and_hyperlane_neighbors()) {
        // This position is a neighbor of this player's home, but it may or may not exist on the board.
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor_of_home)};
        const std::unordered_map<Position, uint8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor_of_home)};
        if (
          neighbor_position_and_tile != positions_to_tiles_.cend()
          && !neighbor_position_and_tile->second.is_hyperlane()
          && neighbor_position_and_distance != positions_to_distances_from_mecatol_rex_.cend()
          && neighbor_position_and_distance->second < home_distance_to_mecatol_rex
        ) {
          // This position exists on the board, is of the correct system category, and is nearer to Mecatol Rex than this player's home.
          // Therefore, this position is a starting point for a pathway to Mecatol Rex.
          pathways.emplace(neighbor_position_and_tile->first);
        }
      }
      // At this point, we have at least 1 position that serves as a start for the pathways to Mecatol Rex.
      // For each pathway, grow it procedurally by moving nearer to Mecatol Rex.
      // Some pathways can fork into multiple pathways.
      while (!pathways.empty() && !all_reach_mecatol_rex(pathways)) {
        std::set<Pathway> updated_pathways;
        for (const Pathway& pathway : pathways) {
          const std::set<Position> next_positions{neighbors_nearer_to_mecatol_rex(pathway.back())};
          for (const Position& next_position : next_positions) {
            Pathway updated_pathway{pathway};
            updated_pathway.push_back(next_position);
            updated_pathways.insert(updated_pathway);
          }
        }
        pathways = updated_pathways;
      }
      // At this point, the pathways to Mecatol Rex have all been assembled.
      // However, due to hyperlanes, some pathways to Mecatol Rex may be longer than others.
      // Keep only the shortest pathways.
      uint8_t shortest_pathway_distance_to_mecatol_rex{std::numeric_limits<uint8_t>::max()};
      for (const Pathway& pathway : pathways) {
        if (pathway.size() < shortest_pathway_distance_to_mecatol_rex) {
          shortest_pathway_distance_to_mecatol_rex = pathway.size();
        }
      }
      for (const Pathway& pathway : pathways) {
        if (pathway.size() == shortest_pathway_distance_to_mecatol_rex) {
          players_to_pathways_to_mecatol_rex_.insert({player_and_home_position.first, pathway});
        }
      }
    }
  }

  void initialize_space_dock_positions() noexcept {
    // TODO: Initialize the preferred and alternate space dock positions using the pathways to Mecatol Rex.
    // The preferred and alternate space dock positions are selected from the pathways to Mecatol Rex.
    // However, the preferred and alternate space dock positions must be in-slice positions rather than equidistant positions.
    // By definitions, for a given player, the pathways to Mecatol Rex all have the same length.
    // Remember that the last position in the pathway is the Mecatol Rex position itself.
    // If 2 or more positions are tied for preferred space dock position, choose the one with the largest minimum distance from other players' homes.
    // Do the same for the alternate positions.
    // If the pathways to Mecatol Rex have length 1, the player's home is adjacent to Mecatol Rex, so there are no preferred or alternate positions.
    // If the pathways to Mecatol Rex have length 2, there is only a preferred position, and no alternate position.
    // If the pathways to Mecatol Rex have length 3, the preferred position is the first one, and the alternate is the second one.
    // If the pathways to Mecatol Rex have length 4, the preferred position is the second (middle) one, and the alternates are the first and third ones.
    // Do not bother with cases where the pathways to Mecatol Rex are longer than 4.





  }

  /// \brief Returns a map of all non-hyperlane tiles present on the board along with their distance to a given target position.
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
          // The current position exists, is of the correct system category, and has not yet been visited.
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

  /// \brief Returns the set of planetary/anomaly/wormhole/empty neighbors that are nearer to Mecatol Rex than a given reference position.
  /// \details If given a position adjacent to Mecatol Rex as a reference, this returns the Mecatol Rex position itself.
  std::set<Position> neighbors_nearer_to_mecatol_rex(const Position& reference) const noexcept {
    std::set<Position> neighbors_nearer_to_mecatol_rex_;
    const std::unordered_map<Position, Tile>::const_iterator reference_position_and_tile{positions_to_tiles_.find(reference)};
    const std::unordered_map<Position, uint8_t>::const_iterator reference_position_and_distance{positions_to_distances_from_mecatol_rex_.find(reference)};
    if (
      reference_position_and_tile != positions_to_tiles_.cend()
      && !reference_position_and_tile->second.is_hyperlane()
      && reference_position_and_distance != positions_to_distances_from_mecatol_rex_.cend()
    ) {
      // The reference exists on the board and is of the correct system category.
      const std::set<Position> neighbors{reference_position_and_tile->second.position_and_hyperlane_neighbors()};
      for (const Position& neighbor : neighbors) {
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor)};
        const std::unordered_map<Position, uint8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor)};
        if (
          neighbor_position_and_tile != positions_to_tiles_.cend()
          && !neighbor_position_and_tile->second.is_hyperlane()
          && neighbor_position_and_distance != positions_to_distances_from_mecatol_rex_.cend()
          && neighbor_position_and_distance->second < reference_position_and_distance->second
        ) {
          // This neighbor exists on the board, is of the correct system category, and is nearer to Mecatol Rex than the reference.
          neighbors_nearer_to_mecatol_rex_.insert(neighbor_position_and_tile->first);
        }
      }
    }
    return neighbors_nearer_to_mecatol_rex_;
  }

  /// \brief Helper function used during the initialization of the pathways to Mecatol Rex.
  bool all_reach_mecatol_rex(const std::set<Pathway>& pathways) const noexcept {
    for (const Pathway& pathway : pathways) {
      if (pathway.empty() || pathway.back() != mecatol_rex_position_) {
        return false;
      }
    }
    return true;
  }

}; // class Tiles

uint8_t number_of_in_slice_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_in_a_slice() && tile.is_planetary_anomaly_wormhole_or_empty()) {
      ++number;
    }
  }
  return number;
}

uint8_t number_of_equidistant_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_equidistant() && tile.is_planetary_anomaly_wormhole_or_empty()) {
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
