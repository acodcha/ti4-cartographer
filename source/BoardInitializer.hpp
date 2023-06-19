#pragma once

#include "Pathway.hpp"
#include "Tiles.hpp"

namespace TI4Cartographer {

/// \brief Initializer for the Board class.
class BoardInitializer {
public:
  BoardInitializer(const Layout layout) noexcept {
    initialize_tiles(layout);
    initialize_neighbors();
    initialize_mecatol_rex_position();
    initialize_players(layout);
    initialize_players_home_positions();
    initialize_distances_from_mecatol_rex();
    initialize_distances_from_players_homes();
    initialize_relevant_players_and_equidistant_and_in_slice_positions();
    initialize_forward_and_lateral_positions();
    initialize_mecatol_rex_pathways();
    initialize_preferred_expansion_and_alternate_expansion_positions();
  }

protected:
  /// \brief Collection of tiles that form the board, indexed by their
  /// positions.
  std::unordered_map<Position, Tile> positions_to_tiles_;

  int8_t maximum_layer_{0};

  /// \brief Each position's neighbors. Each of these neighbors exists on this
  /// game board.
  std::unordered_map<Position, std::set<Position>> neighbors_;

  /// \brief Position of the Mecatol Rex system.
  Position mecatol_rex_position_;

  /// \brief List of all players.
  std::set<Player> players_;

  /// \brief Positions of the home system of each player.
  std::map<Player, Position> players_to_home_positions_;

  /// \brief Each position's distance to the Mecatol Rex system.
  std::unordered_map<Position, Distance>
      positions_to_distances_from_mecatol_rex_;

  /// \brief MMaximum distance from the Mecatol Rex system on this game board.
  Distance maximum_distance_from_mecatol_rex_{0};

  /// \brief Each position's distance to each player's home system (or Creuss
  /// Gate system, if applicable).
  std::unordered_map<Position, std::map<Player, Distance>>
      positions_to_players_home_distances_;

  /// \brief A position's relevant players are players who have this position in
  /// their slice or as an equidistant position.
  std::unordered_map<Position, std::set<Player>> positions_to_relevant_players_;

  /// \brief Positions that are equidistant to 2 or more players' homes.
  std::set<Position> equidistant_positions_;

  /// \brief Positions that are in a player's slice.
  std::unordered_map<Position, Player> in_slice_positions_to_players_;

  /// \brief Each player's slice.
  std::map<Player, std::set<Position>> players_to_in_slice_positions_;

  /// \brief Each player's equidistant positions.
  std::map<Player, std::set<Position>> players_to_equidistant_positions_;

  /// \brief Group of forward positions for each player, i.e. home-adjacent
  /// positions that are nearer to Mecatol Rex than each player's home.
  std::map<Player, std::set<Position>> players_to_forward_positions_;

  /// \brief Group of lateral positions for each player, i.e. home-adjacent
  /// positions that are not nearer to Mecatol Rex than each player's home.
  std::map<Player, std::set<Position>> players_to_lateral_positions_;

  /// \brief Pathways to Mecatol Rex may include equidistant positions and
  /// always end with the Mecatol Rex position itself.
  std::map<Player, std::vector<Pathway>> players_to_mecatol_rex_pathways_;

  /// \brief Preferred expansion positions are positions where a player would
  /// ideally want to construct their second space dock and use as a forward
  /// base.
  std::map<Player, std::set<Position>> players_to_preferred_expansion_positions_;

  /// \brief Alternate expansion positions are positiosn where a player would
  /// ideally want to construct their third space dock and use as a forward
  /// base.
  std::map<Player, std::set<Position>> players_to_alternate_expansion_positions_;

  bool is_equidistant(const Position& position) const noexcept {
    return equidistant_positions_.find(position)
           != equidistant_positions_.cend();
  }

  bool is_in_a_slice(const Position& position) const noexcept {
    return in_slice_positions_to_players_.find(position)
           != in_slice_positions_to_players_.cend();
  }

private:
  void initialize_tiles(const Layout layout) noexcept {
    for (const Tile& tile : tiles(layout)) {
      positions_to_tiles_.insert({tile.position(), tile});
      if (tile.position().layer() > maximum_layer_) {
        maximum_layer_ = tile.position().layer();
      }
    }
  }

  void initialize_neighbors() noexcept {
    for (const std::pair<const Position, Tile>& position_and_tile :
         positions_to_tiles_) {
      if (!position_and_tile.second.is_hyperlane()) {
        std::set<Position> neighbors;
        for (const Position& neighbor_position :
             position_and_tile.first.possible_neighbors()) {
          const std::unordered_map<Position, Tile>::const_iterator
              neighbor_position_and_tile{
                  positions_to_tiles_.find(neighbor_position)};
          if (neighbor_position_and_tile != positions_to_tiles_.cend()
              && !neighbor_position_and_tile->second.is_hyperlane()) {
            neighbors.insert(neighbor_position);
          }
        }
        for (const Position& neighbor_position :
             position_and_tile.second.hyperlane_neighbors()) {
          const std::unordered_map<Position, Tile>::const_iterator
              neighbor_position_and_tile{
                  positions_to_tiles_.find(neighbor_position)};
          if (neighbor_position_and_tile != positions_to_tiles_.cend()
              && !neighbor_position_and_tile->second.is_hyperlane()) {
            neighbors.insert(neighbor_position);
          }
        }
        neighbors_.emplace(position_and_tile.first, neighbors);
      }
    }
    // Check that all neighbors are symmetric.
    for (const std::pair<const Position, std::set<Position>>&
             position_and_neighbors : neighbors_) {
      for (const Position& neighbor : position_and_neighbors.second) {
        const std::unordered_map<Position, std::set<Position>>::const_iterator
            neighbor_and_neighbors{neighbors_.find(neighbor)};
        if (neighbor_and_neighbors->second.find(position_and_neighbors.first)
            == neighbor_and_neighbors->second.cend()) {
          error(
              "The tiles of this board layout have asymmetric neighbors. There "
              "is likely a problem with the definition of hyperlane "
              "neighbors.");
        }
      }
    }
  }

  void initialize_mecatol_rex_position() noexcept {
    for (const std::pair<const Position, Tile>& position_and_tile :
         positions_to_tiles_) {
      if (position_and_tile.second.system_id() == MecatolRexSystemId) {
        mecatol_rex_position_ = position_and_tile.first;
      }
    }
    verbose_message("Mecatol Rex position: " + mecatol_rex_position_.print());
  }

  void initialize_players(const Layout layout) noexcept {
    const std::set<Player> players_from_layout{
        players(number_of_players(layout))};
    // Check that the set of tiles contains all the player homes.
    std::set<Player> players_from_tiles;
    for (const std::pair<const Position, Tile>& position_and_tile :
         positions_to_tiles_) {
      if (position_and_tile.second.home_player().has_value()) {
        players_from_tiles.insert(
            position_and_tile.second.home_player().value());
      }
    }
    if (players_from_layout != players_from_tiles) {
      error(
          "Some player homes are missing from the tiles for this board "
          "layout.");
    }
    players_ = players_from_layout;
  }

  void initialize_players_home_positions() noexcept {
    for (const std::pair<const Position, Tile>& position_and_tile :
         positions_to_tiles_) {
      if (position_and_tile.second.home_player().has_value()) {
        players_to_home_positions_.emplace(
            position_and_tile.second.home_player().value(),
            position_and_tile.first);
      }
    }
    verbose_message("Home positions:");
    for (const std::pair<const Player, Position>& player_and_home_position :
         players_to_home_positions_) {
      verbose_message("- " + label(player_and_home_position.first) + ": "
                      + player_and_home_position.second.print());
    }
  }

  void initialize_distances_from_mecatol_rex() noexcept {
    positions_to_distances_from_mecatol_rex_ =
        positions_and_distances_from_target(mecatol_rex_position_);
    for (const std::pair<const Position, Distance>&
             position_and_distance_from_mecatol_rex :
         positions_to_distances_from_mecatol_rex_) {
      if (position_and_distance_from_mecatol_rex.second
          > maximum_distance_from_mecatol_rex_) {
        maximum_distance_from_mecatol_rex_ =
            position_and_distance_from_mecatol_rex.second;
      }
    }
  }

  void initialize_distances_from_players_homes() noexcept {
    for (const std::pair<const Player, Position>& player_and_home_position :
         players_to_home_positions_) {
      const Player player{player_and_home_position.first};
      const Position home_position{player_and_home_position.second};
      for (const std::pair<const Position, Distance>&
               position_and_distance_from_target :
           positions_and_distances_from_target(home_position)) {
        const Position position{position_and_distance_from_target.first};
        const Distance distance{position_and_distance_from_target.second};
        const std::pair<const Player, const Distance> player_and_distance{
            player, distance};
        const std::unordered_multimap<Position, std::map<Player, Distance>>::
            iterator position_to_players_home_distances{
                positions_to_players_home_distances_.find(position)};
        if (position_to_players_home_distances
            != positions_to_players_home_distances_.end()) {
          position_to_players_home_distances->second.emplace(player, distance);
        } else {
          const std::map<Player, Distance> player_and_distance_map{
              player_and_distance};
          positions_to_players_home_distances_.emplace(
              position, player_and_distance_map);
        }
      }
    }
  }

  void
  initialize_relevant_players_and_equidistant_and_in_slice_positions() noexcept {
    for (const std::pair<const Position, Tile>& position_and_tile :
         positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_map<Position, std::map<Player, Distance>>::
            const_iterator position_and_players_home_distances{
                positions_to_players_home_distances_.find(
                    position_and_tile.first)};
        // Compute the minimum distance.
        Distance minimum_distance{std::numeric_limits<Distance>::max()};
        for (const std::pair<const Player, Distance>& player_and_distance :
             position_and_players_home_distances->second) {
          if (player_and_distance.second < minimum_distance) {
            minimum_distance = player_and_distance.second;
          }
        }
        // Find the relevant players.
        std::set<Player> relevant_players;
        for (const std::pair<const Player, Distance>& player_and_distance :
             position_and_players_home_distances->second) {
          if (player_and_distance.second == minimum_distance) {
            relevant_players.insert(player_and_distance.first);
          }
        }
        // Initialize the relevant players.
        positions_to_relevant_players_.emplace(
            position_and_tile.first, relevant_players);
        // Initialize the equidistant positions.
        if (relevant_players.size() > 1) {
          // This is an equidistant position.
          equidistant_positions_.insert(position_and_tile.first);
          for (const Player player : relevant_players) {
            const std::map<Player, std::set<Position>>::iterator found{
                players_to_equidistant_positions_.find(player)};
            if (found != players_to_equidistant_positions_.end()) {
              found->second.insert(position_and_tile.first);
            } else {
              players_to_equidistant_positions_.insert(
                  {player, {position_and_tile.first}});
            }
          }
        } else if (relevant_players.size() == 1) {
          // This is an in-slice position.
          const Player first_relevant_player{*(relevant_players.begin())};
          in_slice_positions_to_players_.emplace(
              position_and_tile.first, first_relevant_player);
          const std::map<Player, std::set<Position>>::iterator
              player_and_in_slice_positions{
                  players_to_in_slice_positions_.find(first_relevant_player)};
          if (player_and_in_slice_positions
              != players_to_in_slice_positions_.cend()) {
            player_and_in_slice_positions->second.insert(
                position_and_tile.first);
          } else {
            players_to_in_slice_positions_.insert(
                {first_relevant_player, {position_and_tile.first}});
          }
        }
      }
    }
    verbose_message("Equidistant positions:");
    for (const Position& position : equidistant_positions_) {
      verbose_message("- " + position.print());
    }
    verbose_message("In-slice positions:");
    for (
        const std::pair<const Player, std::set<Position>>& player_and_positions :
        players_to_in_slice_positions_) {
      verbose_message("- " + label(player_and_positions.first) + ": "
                      + print_set(player_and_positions.second));
    }
  }

  void initialize_forward_and_lateral_positions() noexcept {
    for (const std::pair<const Player, Position>& player_and_home_position :
         players_to_home_positions_) {
      const std::unordered_map<Position, Distance>::const_iterator
          home_and_distance_to_mecatol_rex{
              positions_to_distances_from_mecatol_rex_.find(
                  player_and_home_position.second)};
      const std::unordered_map<Position, std::set<Position>>::const_iterator
          home_position_and_neighbors{
              neighbors_.find(player_and_home_position.second)};
      if (home_and_distance_to_mecatol_rex
              != positions_to_distances_from_mecatol_rex_.cend()
          && home_position_and_neighbors != neighbors_.cend()) {
        std::set<Position> forward_positions;
        std::set<Position> lateral_positions;
        for (const Position& neighbor_of_home :
             home_position_and_neighbors->second) {
          // This position is a neighbor of this player's home.
          const std::unordered_map<Position, Tile>::const_iterator
              neighbor_position_and_tile{
                  positions_to_tiles_.find(neighbor_of_home)};
          const std::unordered_map<Position, Distance>::const_iterator
              neighbor_position_and_distance{
                  positions_to_distances_from_mecatol_rex_.find(
                      neighbor_of_home)};
          if (neighbor_position_and_tile != positions_to_tiles_.cend()
              && !neighbor_position_and_tile->second.is_hyperlane()
              && neighbor_position_and_distance
                     != positions_to_distances_from_mecatol_rex_.cend()) {
            // This position is of the correct system category.
            if (neighbor_position_and_distance->second
                < home_and_distance_to_mecatol_rex->second) {
              // This position is nearer to Mecatol Rex than this player's home.
              // Therefore, this position is a forward position for this player.
              forward_positions.insert(neighbor_of_home);
            } else {
              // This position is at an equal or greater distance from Mecatol
              // Rex than this player's home. Therefore, this position is a
              // lateral position for this player.
              lateral_positions.insert(neighbor_of_home);
            }
          }
        }
        players_to_forward_positions_.emplace(
            player_and_home_position.first, forward_positions);
        players_to_lateral_positions_.emplace(
            player_and_home_position.first, lateral_positions);
      }
    }
    verbose_message("Forward positions:");
    for (
        const std::pair<const Player, std::set<Position>>& player_and_positions :
        players_to_forward_positions_) {
      verbose_message("- " + label(player_and_positions.first) + ": "
                      + print_set(player_and_positions.second));
    }
    verbose_message("Lateral positions:");
    for (
        const std::pair<const Player, std::set<Position>>& player_and_positions :
        players_to_lateral_positions_) {
      verbose_message("- " + label(player_and_positions.first) + ": "
                      + print_set(player_and_positions.second));
    }
  }

  void initialize_mecatol_rex_pathways() noexcept {
    for (const Player& player : players_) {
      const std::map<Player, std::set<Position>>::const_iterator
          player_and_forward_positions{
              players_to_forward_positions_.find(player)};
      if (player_and_forward_positions
          != players_to_forward_positions_.cend()) {
        std::vector<Pathway> pathways;
        for (const Position& forward_position :
             player_and_forward_positions->second) {
          const std::unordered_map<Position, Tile>::const_iterator
              forward_position_and_tile{
                  positions_to_tiles_.find(forward_position)};
          if (forward_position_and_tile != positions_to_tiles_.cend()
              && !forward_position_and_tile->second.is_hyperlane()) {
            // This position is of the correct system category and is nearer to
            // Mecatol Rex than this player's home. Therefore, this position is
            // a starting point for a pathway to Mecatol Rex.
            Pathway pathway;
            pathway.push_back(forward_position_and_tile->first);
            pathways.push_back(pathway);
          }
        }
        // At this point, we likely have at least 1 position that serves as a
        // start for the pathways to Mecatol Rex. For each pathway, grow it
        // procedurally by moving nearer to Mecatol Rex. Some pathways can fork
        // into multiple pathways.
        while (!pathways.empty() && !all_reach_mecatol_rex(pathways)) {
          std::vector<Pathway> updated_pathways;
          for (const Pathway& pathway : pathways) {
            const std::set<Position> next_positions{
                neighbors_nearer_to_mecatol_rex(pathway.back())};
            for (const Position& next_position : next_positions) {
              Pathway updated_pathway{pathway};
              updated_pathway.push_back(next_position);
              updated_pathways.push_back(updated_pathway);
            }
          }
          pathways = updated_pathways;
        }
        // At this point, the pathways to Mecatol Rex have all been assembled.
        // However, due to hyperlanes, some pathways to Mecatol Rex may be
        // longer than others. Keep only the shortest pathways.
        Distance shortest_pathway_distance_to_mecatol_rex{
            std::numeric_limits<Distance>::max()};
        for (const Pathway& pathway : pathways) {
          if (pathway.distance() < shortest_pathway_distance_to_mecatol_rex) {
            shortest_pathway_distance_to_mecatol_rex = pathway.distance();
          }
        }
        std::vector<Pathway> shortest_pathways;
        for (const Pathway& pathway : pathways) {
          if (pathway.distance() == shortest_pathway_distance_to_mecatol_rex) {
            shortest_pathways.push_back(pathway);
          }
        }
        players_to_mecatol_rex_pathways_.emplace(player, shortest_pathways);
      }
    }
    verbose_message("Pathways to Mecatol Rex:");
    for (const std::pair<const Player, std::vector<Pathway>>&
             player_and_pathways : players_to_mecatol_rex_pathways_) {
      verbose_message("- " + label(player_and_pathways.first) + ": "
                      + print_vector(player_and_pathways.second));
    }
  }

  void
  initialize_preferred_expansion_and_alternate_expansion_positions() noexcept {
    // The preferred and alternate expansions positions are selected from the
    // pathways to Mecatol Rex. However, the preferred and alternate expansion
    // positions must be in-slice positions rather than equidistant positions.
    // By definitions, for a given player, the pathways to Mecatol Rex all have
    // the same length. Remember that the last position in the pathway is the
    // Mecatol Rex position itself. If 2 or more positions are tied for
    // preferred expansion position, choose the one with the largest distance
    // from other players' homes. The same applies to the alternate positions.
    for (const Player player : players_) {
      const std::map<Player, std::vector<Pathway>>::const_iterator
          player_and_pathways_to_mecatol_rex{
              players_to_mecatol_rex_pathways_.find(player)};
      if (player_and_pathways_to_mecatol_rex
              != players_to_mecatol_rex_pathways_.cend()
          && !player_and_pathways_to_mecatol_rex->second.empty()) {
        const Distance pathway_distance{
            player_and_pathways_to_mecatol_rex->second.begin()->distance()};
        // If the pathways to Mecatol Rex have length 1, the player's home is
        // adjacent to Mecatol Rex, so there are no preferred or alternate
        // positions.
        if (pathway_distance == 2) {
          // If the pathways to Mecatol Rex have length 2, there is only a
          // preferred position per pathway, and no alternate position. This
          // distance is relevant to the 3-player small board layout.
          const std::set<Position> preferred_expansion_positions{
              optimal_positions(player, 0)};
          players_to_preferred_expansion_positions_.emplace(
              player, preferred_expansion_positions);
        } else if (pathway_distance == 3) {
          // If the pathways to Mecatol Rex have length 3, the preferred
          // position is the first one, and the alternate is the second one.
          // This distance is relevant to most board layouts up to 6 players, as
          // well as the 7- and 8-player regular board layouts.
          const std::set<Position> preferred_expansion_positions{
              optimal_positions(player, 0)};
          players_to_preferred_expansion_positions_.emplace(
              player, preferred_expansion_positions);
          const std::set<Position> alternate_expansion_positions{
              optimal_positions(player, 1)};
          players_to_alternate_expansion_positions_.emplace(
              player, alternate_expansion_positions);
        } else if (pathway_distance == 4) {
          // If the pathways to Mecatol Rex have length 4, the preferred
          // position is the second (middle) one, and the alternate is the first
          // one. This distance is relevant to the 7- and 8-player large board
          // layouts.
          const std::set<Position> preferred_expansion_positions{
              optimal_positions(player, 1)};
          players_to_preferred_expansion_positions_.emplace(
              player, preferred_expansion_positions);
          const std::set<Position> alternate_expansion_positions{
              optimal_positions(player, 0)};
          players_to_alternate_expansion_positions_.emplace(
              player, alternate_expansion_positions);
        } else if (pathway_distance == 5) {
          // If the pathways to Mecatol Rex have length 5, the preferred
          // position is the second one, and the alternate is the third one.
          // This distance does not exist on any of the board layouts but is
          // included for completeness.
          const std::set<Position> preferred_expansion_positions{
              optimal_positions(player, 1)};
          players_to_preferred_expansion_positions_.emplace(
              player, preferred_expansion_positions);
          const std::set<Position> alternate_expansion_positions{
              optimal_positions(player, 2)};
          players_to_alternate_expansion_positions_.emplace(
              player, alternate_expansion_positions);
        }
        // Do not bother with cases where the pathways to Mecatol Rex are
        // longer.
      }
    }
    verbose_message("Preferred positions:");
    for (const std::pair<const Player, std::set<Position>>&
             player_and_preferred_expansion_positions :
         players_to_preferred_expansion_positions_) {
      verbose_message(
          "- " + label(player_and_preferred_expansion_positions.first) + ": "
          + print_set(player_and_preferred_expansion_positions.second));
    }
    verbose_message("Alternate positions:");
    for (const std::pair<const Player, std::set<Position>>&
             player_and_alternate_expansion_positions :
         players_to_alternate_expansion_positions_) {
      verbose_message(
          "- " + label(player_and_alternate_expansion_positions.first) + ": "
          + print_set(player_and_alternate_expansion_positions.second));
    }
  }

  /// \brief Returns a map of all non-hyperlane tiles present on the board along
  /// with their distance to a given target position.
  std::unordered_map<Position, Distance> positions_and_distances_from_target(
      const Position& target_position) const noexcept {
    std::unordered_map<Position, Distance> position_to_distance_from_target;
    Distance distance_from_target_position{0};
    std::unordered_set<Position> visited;
    std::unordered_set<Position> current_neighbors{target_position};
    std::unordered_set<Position> next_neighbors;
    while (!current_neighbors.empty() || !next_neighbors.empty()) {
      for (const Position& current_position : current_neighbors) {
        const std::unordered_map<Position, Tile>::const_iterator
            current_position_and_tile{
                positions_to_tiles_.find(current_position)};
        if (current_position_and_tile != positions_to_tiles_.cend()
            && !current_position_and_tile->second.is_hyperlane()
            && visited.find(current_position) == visited.cend()) {
          // The current position exists, is of the correct system category, and
          // has not yet been visited.
          visited.insert(current_position);
          position_to_distance_from_target.emplace(
              current_position, distance_from_target_position);
          const std::unordered_map<Position, std::set<Position>>::const_iterator
              position_and_neighbors{
                  neighbors_.find(current_position_and_tile->first)};
          if (position_and_neighbors != neighbors_.cend()) {
            for (const Position& next_position :
                 position_and_neighbors->second) {
              const std::unordered_map<Position, Tile>::const_iterator
                  next_position_and_tile{
                      positions_to_tiles_.find(next_position)};
              if (next_position_and_tile != positions_to_tiles_.cend()
                  && !next_position_and_tile->second.is_hyperlane()
                  && visited.find(next_position) == visited.cend()) {
                // The next position has not been visited.
                next_neighbors.insert(next_position);
              }
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

  /// \brief Returns the set of planetary/anomaly/wormhole/empty neighbors that
  /// are nearer to Mecatol Rex than a given reference position. \details If
  /// given a position adjacent to Mecatol Rex as a reference, this returns the
  /// Mecatol Rex position itself.
  std::set<Position> neighbors_nearer_to_mecatol_rex(
      const Position& reference) const noexcept {
    std::set<Position> neighbors_nearer_to_mecatol_rex_;
    const std::unordered_map<Position, Tile>::const_iterator
        reference_position_and_tile{positions_to_tiles_.find(reference)};
    const std::unordered_map<Position, Distance>::const_iterator
        reference_position_and_distance{
            positions_to_distances_from_mecatol_rex_.find(reference)};
    if (reference_position_and_tile != positions_to_tiles_.cend()
        && !reference_position_and_tile->second.is_hyperlane()
        && reference_position_and_distance
               != positions_to_distances_from_mecatol_rex_.cend()) {
      // The reference exists on the board and is of the correct system
      // category.
      const std::unordered_map<Position, std::set<Position>>::const_iterator
          position_and_neighbors{
              neighbors_.find(reference_position_and_tile->first)};
      if (position_and_neighbors != neighbors_.cend()) {
        for (const Position& neighbor : position_and_neighbors->second) {
          const std::unordered_map<Position, Tile>::const_iterator
              neighbor_position_and_tile{positions_to_tiles_.find(neighbor)};
          const std::unordered_map<Position, Distance>::const_iterator
              neighbor_position_and_distance{
                  positions_to_distances_from_mecatol_rex_.find(neighbor)};
          if (neighbor_position_and_tile != positions_to_tiles_.cend()
              && !neighbor_position_and_tile->second.is_hyperlane()
              && neighbor_position_and_distance
                     != positions_to_distances_from_mecatol_rex_.cend()
              && neighbor_position_and_distance->second
                     < reference_position_and_distance->second) {
            // This neighbor is of the correct system category and is nearer to
            // Mecatol Rex than the reference.
            neighbors_nearer_to_mecatol_rex_.insert(
                neighbor_position_and_tile->first);
          }
        }
      }
    }
    return neighbors_nearer_to_mecatol_rex_;
  }

  /// \brief Helper function used during the initialization of the pathways to
  /// Mecatol Rex.
  bool all_reach_mecatol_rex(
      const std::vector<Pathway>& pathways) const noexcept {
    for (const Pathway& pathway : pathways) {
      if (pathway.empty() || pathway.back() != mecatol_rex_position_) {
        return false;
      }
    }
    return true;
  }

  /// \brief Helper function used during the initialization of the preferred and
  /// alternate space dock positions.
  std::set<Position> optimal_positions(
      const Player& player, const uint8_t index_along_pathway) const noexcept {
    // Obtain the pathways for this player.
    const std::map<Player, std::vector<Pathway>>::const_iterator
        player_and_pathway_to_mecatol_rex{
            players_to_mecatol_rex_pathways_.find(player)};
    // Compute the maximum-minimum distance from other players' homes for all
    // positions at the index.
    Distance maximum_distance_from_other_players_homes_{0};
    for (const Pathway& pathway : player_and_pathway_to_mecatol_rex->second) {
      const Position position{pathway[index_along_pathway]};
      // Optimal positions cannot be equidistant positions.
      if (equidistant_positions_.find(position)
          == equidistant_positions_.cend()) {
        const Distance
            minimum_distance_from_other_players_homes_for_this_pathway{
                minimum_distance_from_other_players_homes(player, position)};
        if (minimum_distance_from_other_players_homes_for_this_pathway
            > maximum_distance_from_other_players_homes_) {
          maximum_distance_from_other_players_homes_ =
              minimum_distance_from_other_players_homes_for_this_pathway;
        }
      }
    }
    // Obtain all positions at the index that correspond to this maximum
    // distance. These are the optimal positions.
    std::map<Position, uint8_t>
        optimal_positions_and_number_of_equidistant_neighbors;
    uint8_t maximum_number_of_equidistant_neighbors{0};
    for (const Pathway& pathway : player_and_pathway_to_mecatol_rex->second) {
      const Position position{pathway[index_along_pathway]};
      // Optimal positions cannot be equidistant positions.
      // However, prefer optimal positions that have many equidistant neighbors.
      if (equidistant_positions_.find(position)
          == equidistant_positions_.cend()) {
        const Distance
            minimum_distance_from_other_players_homes_for_this_pathway{
                minimum_distance_from_other_players_homes(player, position)};
        if (minimum_distance_from_other_players_homes_for_this_pathway
            == maximum_distance_from_other_players_homes_) {
          const std::unordered_map<Position, std::set<Position>>::const_iterator
              position_and_neighbors{neighbors_.find(position)};
          uint8_t number_of_equidistant_neighbors{0};
          for (const Position& neighbor : position_and_neighbors->second) {
            if (equidistant_positions_.find(neighbor)
                != equidistant_positions_.cend()) {
              ++number_of_equidistant_neighbors;
            }
          }
          if (number_of_equidistant_neighbors
              > maximum_number_of_equidistant_neighbors) {
            maximum_number_of_equidistant_neighbors =
                number_of_equidistant_neighbors;
          }
          optimal_positions_and_number_of_equidistant_neighbors.emplace(
              position, number_of_equidistant_neighbors);
        }
      }
    }
    // Keep only the optimal positions that have the most equidistant neighbors.
    std::set<Position> optimal_positions_;
    for (const std::pair<const Position, uint8_t>&
             optimal_position_and_number_of_equidistant_neighbors :
         optimal_positions_and_number_of_equidistant_neighbors) {
      if (optimal_position_and_number_of_equidistant_neighbors.second
          == maximum_number_of_equidistant_neighbors) {
        optimal_positions_.insert(
            optimal_position_and_number_of_equidistant_neighbors.first);
      }
    }
    return optimal_positions_;
  }

  /// \brief Helper function used during the initialization of the preferred and
  /// alternate space dock positions.
  Distance minimum_distance_from_other_players_homes(
      const Player player, const Position& position) const noexcept {
    Distance minimum_distance_from_other_players_homes_{
        std::numeric_limits<Distance>::max()};
    const std::unordered_map<Position, std::map<Player, Distance>>::const_iterator
        position_to_players_home_distances{
            positions_to_players_home_distances_.find(position)};
    if (position_to_players_home_distances
        != positions_to_players_home_distances_.cend()) {
      for (const std::pair<const Player, Distance>& player_and_home_distance :
           position_to_players_home_distances->second) {
        if (player != player_and_home_distance.first
            && player_and_home_distance.second
                   > minimum_distance_from_other_players_homes_) {
          minimum_distance_from_other_players_homes_ =
              player_and_home_distance.second;
        }
      }
    }
    return minimum_distance_from_other_players_homes_;
  }

  uint8_t number_of_equidistant_systems(const Pathway& pathway) const noexcept {
    uint8_t number_of_equidistant_systems_{0};
    for (const Position& position : pathway) {
      if (equidistant_positions_.find(position)
          != equidistant_positions_.cend()) {
        ++number_of_equidistant_systems_;
      }
    }
    return number_of_equidistant_systems_;
  }

};  // class BoardInitializer

}  // namespace TI4Cartographer
