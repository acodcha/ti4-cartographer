#pragma once

#include "DistanceFromPlayerHome.hpp"
#include "Pathway.hpp"
#include "Tiles6Players.hpp"

namespace TI4Cartographer {

/// \brief Initializer for the Board class.
template <Layout layout> class BoardInitializer {

public:

  BoardInitializer() noexcept {
    initialize_tiles();
    initialize_mecatol_rex_position();
    initialize_players();
    initialize_players_home_positions();
    initialize_distances_from_mecatol_rex();
    initialize_distances_from_player_homes();
    initialize_equidistant_positions();
    initialize_in_slice_positions();
    initialize_lateral_positions();
    initialize_pathways_to_mecatol_rex();
    initialize_space_dock_positions();
  }

protected:

  /// \brief Collection of tiles that form the board, indexed by their positions.
  std::unordered_map<Position, Tile> positions_to_tiles_;

  Position mecatol_rex_position_;

  std::set<Player> players_;

  std::map<Player, Position> players_to_home_positions_;

  std::unordered_map<Position, int8_t> positions_to_distances_from_mecatol_rex_;

  std::unordered_multimap<Position, DistanceFromPlayerHome> positions_to_distances_from_player_homes_;

  /// \brief Group of positions that are equidistant to 2 or more players' homes.
  std::set<Position> equidistant_positions_;

  /// \brief Group of in-slice positions for each player, i.e. positions that are nearer to that player's home than other players' homes.
  std::multimap<Player, Position> players_to_in_slice_positions_;

  /// \brief Group of lateral positions for each player, i.e. positions that are not nearer to Mecatol Rex than each player's home.
  std::multimap<Player, Position> players_to_lateral_positions_;

  /// \brief Pathways to Mecatol Rex may include equidistant positions and always end with the Mecatol Rex position itself.
  std::multimap<Player, Pathway> players_to_pathways_to_mecatol_rex_;

  std::multimap<Player, Position> players_to_preferred_space_dock_positions_;

  std::multimap<Player, Position> players_to_alternate_space_dock_positions_;

private:

  void initialize_tiles() noexcept {
    for (const Tile& tile : Tiles<layout>) {
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

  void initialize_players() noexcept {
    players_ = players(number_of_players(layout));
  }

  void initialize_players_home_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.home_player().has_value()) {
        players_.insert(position_and_tile.second.home_player().value());
        players_to_home_positions_.insert({position_and_tile.second.home_player().value(), position_and_tile.first});
      }
    }
  }

  void initialize_distances_from_mecatol_rex() noexcept {
    positions_to_distances_from_mecatol_rex_ = positions_and_distances_from_target(mecatol_rex_position_);
  }

  void initialize_distances_from_player_homes() noexcept {
    for (const std::pair<Player, Position>& player_and_home_position : players_to_home_positions_) {
      for (const std::pair<Position, int8_t>& position_and_distance_from_target : positions_and_distances_from_target(player_and_home_position.second)) {
        positions_to_distances_from_player_homes_.insert({position_and_distance_from_target.first, {player_and_home_position.first, position_and_distance_from_target.second}});
      }
    }
  }

  /// \brief If at least two players' homes are the same distance from a given position, then that position is an equidistant position.
  void initialize_equidistant_positions() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::pair<std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator, std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator> range{positions_to_distances_from_player_homes_.equal_range(position_and_tile.first)};
        std::set<int8_t> distances_from_homes;
        for (std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator position_and_distance = range.first; position_and_distance != range.second; ++position_and_distance) {
          const std::set<int8_t>::const_iterator distance_from_home{distances_from_homes.find(position_and_distance->second.distance_from_home())};
          if (distance_from_home != distances_from_homes.cend()) {
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
        int8_t minimum_distance_from_home{std::numeric_limits<int8_t>::max()};
        Player player{Player::Player1};
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
    for (const std::pair<Player, Position>& player_and_home_position : players_to_home_positions_) {
      const int8_t home_distance_to_mecatol_rex{positions_to_distances_from_mecatol_rex_.find(player_and_home_position.second)->second};
      for (const Position& neighbor_of_home : positions_to_tiles_.find(player_and_home_position.second)->second.position_and_hyperlane_neighbors()) {
        // This position is a neighbor of this player's home, but it may or may not exist on the board.
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor_of_home)};
        const std::unordered_map<Position, int8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor_of_home)};
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
    for (const std::pair<Player, Position>& player_and_home_position : players_to_home_positions_) {
      const int8_t home_distance_to_mecatol_rex{positions_to_distances_from_mecatol_rex_.find(player_and_home_position.second)->second};
      std::set<Pathway> pathways;
      for (const Position& neighbor_of_home : positions_to_tiles_.find(player_and_home_position.second)->second.position_and_hyperlane_neighbors()) {
        // This position is a neighbor of this player's home, but it may or may not exist on the board.
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor_of_home)};
        const std::unordered_map<Position, int8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor_of_home)};
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
      int8_t shortest_pathway_distance_to_mecatol_rex{std::numeric_limits<int8_t>::max()};
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
    // The preferred and alternate space dock positions are selected from the pathways to Mecatol Rex.
    // However, the preferred and alternate space dock positions must be in-slice positions rather than equidistant positions.
    // By definitions, for a given player, the pathways to Mecatol Rex all have the same length.
    // Remember that the last position in the pathway is the Mecatol Rex position itself.
    // If 2 or more positions are tied for preferred space dock position, choose the one with the largest distance from other players' homes. The same applies to the alternate positions.
    for (const Player player : players_) {
      const std::pair<std::multimap<Player, Pathway>::const_iterator, std::multimap<Player, Pathway>::const_iterator> player_and_pathways{players_to_pathways_to_mecatol_rex_.equal_range(player)};
      const int8_t pathway_distance{static_cast<int8_t>(player_and_pathways.first->second.size())};
      // If the pathways to Mecatol Rex have length 1, the player's home is adjacent to Mecatol Rex, so there are no preferred or alternate positions.
      if (pathway_distance == 2) {
        // If the pathways to Mecatol Rex have length 2, there is only a preferred position per pathway, and no alternate position.
        // This distance is relevant to the 3-player small board layout.
        const std::set<Position> preferred_space_dock_positions{optimal_positions(player, 0)};
        for (const Position& preferred_space_dock_position : preferred_space_dock_positions) {
          players_to_preferred_space_dock_positions_.insert({player, preferred_space_dock_position});
        }
      } else if (pathway_distance == 3) {
        // If the pathways to Mecatol Rex have length 3, the preferred position is the first one, and the alternate is the second one.
        // This distance is relevant to most board layouts up to 6 players, as well as the 7- and 8-player regular board layouts.
        const std::set<Position> preferred_space_dock_positions{optimal_positions(player, 0)};
        for (const Position& preferred_space_dock_position : preferred_space_dock_positions) {
          players_to_preferred_space_dock_positions_.insert({player, preferred_space_dock_position});
        }
        const std::set<Position> alternate_space_dock_positions{optimal_positions(player, 1)};
        for (const Position& alternate_space_dock_position : alternate_space_dock_positions) {
          players_to_alternate_space_dock_positions_.insert({player, alternate_space_dock_position});
        }
      } else if (pathway_distance == 4) {
        // If the pathways to Mecatol Rex have length 4, the preferred position is the second (middle) one, and the alternate is the first one.
        // This distance is relevant to the 7- and 8-player large board layouts.
        const std::set<Position> preferred_space_dock_positions{optimal_positions(player, 1)};
        for (const Position& preferred_space_dock_position : preferred_space_dock_positions) {
          players_to_preferred_space_dock_positions_.insert({player, preferred_space_dock_position});
        }
        const std::set<Position> alternate_space_dock_positions_1{optimal_positions(player, 0)};
        for (const Position& alternate_space_dock_position : alternate_space_dock_positions_1) {
          players_to_alternate_space_dock_positions_.insert({player, alternate_space_dock_position});
        }
      } else if (pathway_distance == 5) {
        // If the pathways to Mecatol Rex have length 5, the preferred position is the second one, and the alternate is the third one.
        // This distance does not exist on any of the board layouts but is included for completeness.
        const std::set<Position> preferred_space_dock_positions{optimal_positions(player, 1)};
        for (const Position& preferred_space_dock_position : preferred_space_dock_positions) {
          players_to_preferred_space_dock_positions_.insert({player, preferred_space_dock_position});
        }
        const std::set<Position> alternate_space_dock_positions_1{optimal_positions(player, 2)};
        for (const Position& alternate_space_dock_position : alternate_space_dock_positions_1) {
          players_to_alternate_space_dock_positions_.insert({player, alternate_space_dock_position});
        }
      }
      // Do not bother with cases where the pathways to Mecatol Rex are longer.
    }
  }

  /// \brief Returns a map of all non-hyperlane tiles present on the board along with their distance to a given target position.
  std::unordered_map<Position, int8_t> positions_and_distances_from_target(const Position& target_position) const noexcept {
    std::unordered_map<Position, int8_t> position_to_distance_from_target;
    int8_t distance_from_target_position{0};
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
    const std::unordered_map<Position, int8_t>::const_iterator reference_position_and_distance{positions_to_distances_from_mecatol_rex_.find(reference)};
    if (
      reference_position_and_tile != positions_to_tiles_.cend()
      && !reference_position_and_tile->second.is_hyperlane()
      && reference_position_and_distance != positions_to_distances_from_mecatol_rex_.cend()
    ) {
      // The reference exists on the board and is of the correct system category.
      const std::set<Position> neighbors{reference_position_and_tile->second.position_and_hyperlane_neighbors()};
      for (const Position& neighbor : neighbors) {
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor)};
        const std::unordered_map<Position, int8_t>::const_iterator neighbor_position_and_distance{positions_to_distances_from_mecatol_rex_.find(neighbor)};
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

  /// \brief Helper function used during the initialization of the preferred and alternate space dock positions.
  std::set<Position> optimal_positions(const Player player, const uint8_t pathway_index) const noexcept {
    // Obtain the pathways for this player.
    const std::pair<std::multimap<Player, Pathway>::const_iterator, std::multimap<Player, Pathway>::const_iterator> player_and_pathways{players_to_pathways_to_mecatol_rex_.equal_range(player)};
    // Compute the maximum-minimum distance from other players' homes for all positions at the pathway index.
    int8_t maximum_distance_from_other_players_homes_{0};
    for (
      std::multimap<Player, Pathway>::const_iterator player_and_pathway = player_and_pathways.first;
      player_and_pathway != player_and_pathways.second;
      ++player_and_pathway
    ) {
      const Position position{player_and_pathway->second[pathway_index]};
      // Optimal positions cannot be equidistant positions.
      if (equidistant_positions_.find(position) == equidistant_positions_.cend()) {
        const int8_t minimum_distance_from_other_players_homes_for_this_pathway{minimum_distance_from_other_players_homes(player, position)};
        if (minimum_distance_from_other_players_homes_for_this_pathway > maximum_distance_from_other_players_homes_) {
          maximum_distance_from_other_players_homes_ = minimum_distance_from_other_players_homes_for_this_pathway;
        }
      }
    }
    // Obtain all positions at the pathway index that correspond to this maximum distance. These are the optimal positions.
    std::set<Position> optimal_positions_;
    for (
      std::multimap<Player, Pathway>::const_iterator player_and_pathway = player_and_pathways.first;
      player_and_pathway != player_and_pathways.second;
      ++player_and_pathway
    ) {
      const Position position{player_and_pathway->second[pathway_index]};
      // Optimal positions cannot be equidistant positions.
      if (equidistant_positions_.find(position) == equidistant_positions_.cend()) {
        const int8_t minimum_distance_from_other_players_homes_for_this_pathway{minimum_distance_from_other_players_homes(player, position)};
        if (minimum_distance_from_other_players_homes_for_this_pathway == maximum_distance_from_other_players_homes_) {
          optimal_positions_.insert(position);
        }
      }
    }
    return optimal_positions_;
  }

  /// \brief Helper function used during the initialization of the preferred and alternate space dock positions.
  int8_t minimum_distance_from_other_players_homes(const Player player, const Position& position) const noexcept {
    int8_t minimum_distance_from_other_players_homes_{std::numeric_limits<int8_t>::max()};
    const std::pair<
      std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator,
      std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator
    > position_and_distances_from_player_homes{positions_to_distances_from_player_homes_.equal_range(position)};
    for (
      std::unordered_multimap<Position, DistanceFromPlayerHome>::const_iterator position_and_distance_from_player_home = position_and_distances_from_player_homes.first;
      position_and_distance_from_player_home != position_and_distances_from_player_homes.second;
      ++position_and_distance_from_player_home
    ) {
      if (
        player != position_and_distance_from_player_home->second.player()
        && position_and_distance_from_player_home->second.distance_from_home() < minimum_distance_from_other_players_homes_
      ) {
        minimum_distance_from_other_players_homes_ = position_and_distance_from_player_home->second.distance_from_home();
      }
    }
    return minimum_distance_from_other_players_homes_;
  }

}; // class BoardInitializer

} // namespace TI4Cartographer
