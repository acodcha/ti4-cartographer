#pragma once

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
    const Aggression aggression
  ) noexcept :
    BoardInitializer(layout)
  {
    initialize_player_scores();
    attempt(game_version, layout, aggression);
    verbose_message("Player scores: " + print_player_scores());
    verbose_message("Score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio()));
    verbose_message("Visualization: " + print_visualization_link());
    verbose_message("Tabletop Simulator string: " + print_tabletop_simulator_string());
    quiet_message(print_tabletop_simulator_string());
    verbose_message("Runtime: " + chronometre.print());
  }

private:

  static constexpr const uint8_t maximum_number_of_attempts_{20};

  static constexpr const uint64_t maximum_number_of_iterations_per_attempt_{1000000};

  static constexpr const float initial_score_imbalance_ratio_tolerance_{0.05};

  static constexpr const float score_imbalance_ratio_tolerance_growth_factor_{1.3};

  SelectedSystemIds selected_system_ids_;

  std::map<Player, float> player_scores_;

  float score_imbalance_ratio_{0.0};

  void initialize_player_scores() noexcept {
    for (const Player player : players_) {
      player_scores_.insert({player, 0.0});
    }
  }

  void attempt(const GameVersion game_version, const Layout layout, const Aggression aggression) noexcept {
    uint8_t number_of_attempts{0};
    std::unordered_map<Position, Tile> best_positions_to_tiles{positions_to_tiles_};
    std::map<Player, float> best_player_scores{player_scores_};
    float best_score_imbalance_ratio{std::numeric_limits<float>::max()};
    for (uint8_t counter = 0; counter < maximum_number_of_attempts_; ++counter) {
      ++number_of_attempts;
      const float score_imbalance_ratio_tolerance{initial_score_imbalance_ratio_tolerance_ * std::pow(score_imbalance_ratio_tolerance_growth_factor_, static_cast<float>(counter))};
      verbose_message("Start of board generation attempt #" + std::to_string(number_of_attempts) + ": target score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio_tolerance));
      if (best_score_imbalance_ratio <= score_imbalance_ratio_tolerance) {
        verbose_message("Using a previously-found optimal game board because its score imbalance is now below the target score imbalance.");
        break;
      }
      initialize_selected_system_ids(game_version, layout, aggression);
      iterate(score_imbalance_ratio_tolerance, best_positions_to_tiles, best_player_scores, best_score_imbalance_ratio);
      verbose_message("End of board generation attempt #" + std::to_string(number_of_attempts) + ".");
      if (score_imbalance_ratio_ <= score_imbalance_ratio_tolerance) {
        break;
      }
    }
    positions_to_tiles_ = best_positions_to_tiles;
    player_scores_ = best_player_scores;
    score_imbalance_ratio_ = best_score_imbalance_ratio;
  }

  void initialize_selected_system_ids(const GameVersion game_version, const Layout layout, const Aggression aggression) noexcept {
    selected_system_ids_ = {game_version, layout, aggression, static_cast<uint8_t>(equidistant_positions_.size())};
    // Check that the number of selected systems matches the number of planetary/anomaly/wormhole/empty tiles.
    uint8_t number_of_planetary_anomaly_wormhole_empty_tiles{0};
    uint8_t number_of_equidistant_positions{0};
    uint8_t number_of_in_slice_positions{0};
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
        ++number_of_planetary_anomaly_wormhole_empty_tiles;
      }
      if (in_slice_positions_to_players_.find(position_and_tile.first) != in_slice_positions_to_players_.cend()) {
        ++number_of_in_slice_positions;
      }
      else if (equidistant_positions_.find(position_and_tile.first) != equidistant_positions_.cend()) {
        ++number_of_equidistant_positions;
      }
    }
    if (number_of_planetary_anomaly_wormhole_empty_tiles != static_cast<uint8_t>(selected_system_ids_.equidistant().size() + selected_system_ids_.in_slice().size())) {
      error("There is a discrepancy between the number of selected systems and the number of tiles for this board layout.");
    }
    if (number_of_equidistant_positions != static_cast<uint8_t>(selected_system_ids_.equidistant().size())) {
      error("There is a discrepancy between the number of selected equidistant systems and the number of equidistant tiles for this board layout.");
    }
    if (number_of_in_slice_positions != static_cast<uint8_t>(selected_system_ids_.in_slice().size())) {
      error("There is a discrepancy between the number of selected in-slice systems and the number of in-slice tiles for this board layout.");
    }
  }

  void iterate(
    const float score_imbalance_ratio_tolerance,
    std::unordered_map<Position, Tile>& best_positions_to_tiles,
    std::map<Player, float>& best_player_scores,
    float& best_score_imbalance_ratio
  ) {
    uint64_t number_of_iterations{0};
    uint64_t number_of_valid_boards{0};
    bool success{false};
    // The first iteration of the first attempt is always recorded as a "best" iteration.
    if (best_score_imbalance_ratio == std::numeric_limits<float>::max()) {
      ++number_of_iterations;
      const bool board_is_valid = assign_system_ids_to_tiles();
      if (board_is_valid) {
        ++number_of_valid_boards;
      }
      calculate_player_scores();
      score_imbalance_ratio_ = score_imbalance_ratio();
      success = update_best_board_and_return_success(score_imbalance_ratio_tolerance, best_positions_to_tiles, best_player_scores, best_score_imbalance_ratio, number_of_iterations);
    }
    // Iterate.
    if (!success) {
      for (uint64_t counter = number_of_iterations; counter < maximum_number_of_iterations_per_attempt_; ++counter) {
        ++number_of_iterations;
        selected_system_ids_.shuffle();
        const bool board_is_valid = assign_system_ids_to_tiles();
        if (board_is_valid) {
          ++number_of_valid_boards;
          calculate_player_scores();
          score_imbalance_ratio_ = score_imbalance_ratio();
          if (score_imbalance_ratio_ < best_score_imbalance_ratio) {
            success = update_best_board_and_return_success(score_imbalance_ratio_tolerance, best_positions_to_tiles, best_player_scores, best_score_imbalance_ratio, number_of_iterations);
            if (success) {
              break;
            }
          }
        }
      }
    }
    // Message after iterations are complete.
    if (success) {
      verbose_message("Found an optimal game board after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
    } else {
      verbose_message("No optimal game board with a score imbalance of " + score_imbalance_ratio_to_string(score_imbalance_ratio_tolerance) + " or less could be found after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
    }
  }

  bool update_best_board_and_return_success(
    const float score_imbalance_ratio_tolerance,
    std::unordered_map<Position, Tile>& best_positions_to_tiles,
    std::map<Player, float>& best_player_scores,
    float& best_score_imbalance_ratio,
    const uint64_t number_of_iterations
  ) noexcept {
    best_positions_to_tiles = positions_to_tiles_;
    best_player_scores = player_scores_;
    best_score_imbalance_ratio = score_imbalance_ratio_;
    verbose_message("Iteration " + std::to_string(number_of_iterations) + ": Score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio_));
    if (score_imbalance_ratio_ <= score_imbalance_ratio_tolerance) {
      return true;
    } else {
      return false;
    }
  }

  /// \brief Assigns system IDs in a simple manner. Returns true if the board is valid and false otherwise. Most boards are invalid with this method.
  bool assign_system_ids_to_tiles() {
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
    return iteration_is_valid();
  }

  struct NeighborsContents {
    NeighborsContents(const std::set<Position>& neighbor_positions, const std::unordered_map<Position, Tile>& positions_to_tiles) noexcept {
      for (const Position& neighbor_position : neighbor_positions) {
        const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles.find(neighbor_position)};
        if (neighbor_position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
          const std::unordered_set<System>::const_iterator neighbor_system{Systems.find({neighbor_position_and_tile->second.system_id()})};
          if (!one_or_more_anomalies && neighbor_system->contains_one_or_more_anomalies()) {
            one_or_more_anomalies = true;
          }
          if (!one_or_more_alpha_wormholes && neighbor_system->contains(Wormhole::Alpha)) {
            one_or_more_alpha_wormholes = true;
          }
          if (!one_or_more_beta_wormholes && neighbor_system->contains(Wormhole::Beta)) {
            one_or_more_beta_wormholes = true;
          }
        }
      }
    }
    bool one_or_more_anomalies{false};
    bool one_or_more_alpha_wormholes{false};
    bool one_or_more_beta_wormholes{false};
  };

  bool iteration_is_valid() const noexcept {
    return !contains_adjacent_anomalies_or_wormholes() && pathways_to_mecatol_rex_are_clear() && players_do_not_have_too_many_wormholes_adjacent_to_their_homes() && players_have_enough_planets() && players_have_enough_useful_resources_and_useful_influence();
  }

  /// \brief As per the game rules, adjacent systems cannot contain anomalies or wormholes of the same type.
  bool contains_adjacent_anomalies_or_wormholes() const noexcept {
    std::unordered_set<Position> checked;
    for (std::unordered_map<Position, Tile>::const_iterator position_and_tile = positions_to_tiles_.cbegin(); position_and_tile != positions_to_tiles_.cend(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty() && checked.find(position_and_tile->first) == checked.cend()) {
        // This tile is of the relevant category and has not yet been checked.
        checked.insert(position_and_tile->first);
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        const bool contains_anomaly{system->contains_one_or_more_anomalies()};
        const bool contains_alpha_wormhole{system->contains(Wormhole::Alpha)};
        const bool contains_beta_wormhole{system->contains(Wormhole::Beta)};
        if (contains_anomaly || contains_alpha_wormhole || contains_beta_wormhole) {
          // This tile contains one or more anomalies or wormholes.
          const std::unordered_map<Position, std::set<Position>>::const_iterator position_and_neighbors{neighbors_.find(position_and_tile->first)};
          if (position_and_neighbors != neighbors_.cend()) {
            for (const Position& neighbor_position : position_and_neighbors->second) {
              const std::unordered_map<Position, Tile>::const_iterator neighbor_position_and_tile{positions_to_tiles_.find(neighbor_position)};
              if (
                neighbor_position_and_tile != positions_to_tiles_.cend()
                && neighbor_position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()
                && checked.find(neighbor_position) == checked.cend()
              ) {
                // This neighbor is of the relevant category and has not yet been checked.
                const std::unordered_set<System>::const_iterator neighbor_system{Systems.find({neighbor_position_and_tile->second.system_id()})};
                if (
                  (contains_anomaly && neighbor_system->contains_one_or_more_anomalies())
                  || (contains_alpha_wormhole && neighbor_system->contains(Wormhole::Alpha))
                  || (contains_beta_wormhole && neighbor_system->contains(Wormhole::Beta))
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

  /// \brief Require that each player have at least one pathway to Mecatol Rex that is devoid of supernovas. A supernova along the pathway to Mecatol Rex lengthens the pathway, making it undesirable.
  bool pathways_to_mecatol_rex_are_clear() const noexcept {
    bool each_player_has_at_least_one_usable_pathway{true};
    for (const std::pair<Player, std::vector<Pathway>>& player_and_mecatol_rex_pathways : players_to_mecatol_rex_pathways_) {
      if (!player_and_mecatol_rex_pathways.second.empty()) {
        bool player_has_no_usable_pathways{true};
        for (const Pathway& pathway : player_and_mecatol_rex_pathways.second) {
          bool pathway_is_usable{true};
          for (const Position& position : pathway) {
            const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
            const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
            if (system->contains(Anomaly::Supernova)) {
              pathway_is_usable = false;
              break;
            }
          }
          if (pathway_is_usable) {
            player_has_no_usable_pathways = false;
            break;
          }
        }
        if (player_has_no_usable_pathways) {
          each_player_has_at_least_one_usable_pathway = false;
          break;
        }
      }
    }
    return each_player_has_at_least_one_usable_pathway;
  }

 bool players_do_not_have_too_many_wormholes_adjacent_to_their_homes() const noexcept {
    std::map<Player, int8_t> players_to_number_of_wormholes_adjacent_to_home;
    for (const Player& player : players_) {
      players_to_number_of_wormholes_adjacent_to_home.emplace(player, 0);
    }
    for (const std::pair<Player, std::set<Position>>& player_and_forward_positions : players_to_forward_positions_) {
      for (const Position& position : player_and_forward_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (system->contains_one_or_more_wormholes()) {
          ++(players_to_number_of_wormholes_adjacent_to_home[player_and_forward_positions.first]);
        }
      }
    }
    for (const std::pair<Player, std::set<Position>>& player_and_lateral_positions : players_to_lateral_positions_) {
      for (const Position& position : player_and_lateral_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (system->contains_one_or_more_wormholes()) {
          ++(players_to_number_of_wormholes_adjacent_to_home[player_and_lateral_positions.first]);
        }
      }
    }
    for (const std::pair<Player, int8_t>& player_and_number_of_wormholes_adjacent_to_home : players_to_number_of_wormholes_adjacent_to_home) {
      if (player_and_number_of_wormholes_adjacent_to_home.second > 1) {
        return false;
      }
    }
    return true;
 }

  /// \brief Equidistant systems are less valuable due to the greater difficulty of holding them.
  float number_of_relevant_players_factor(const std::size_t number_of_relevant_players) const noexcept {
    if (number_of_relevant_players == 1) {
      return 1.0f;
    } else if (number_of_relevant_players == 2) {
      return 0.9f / static_cast<float>(number_of_relevant_players);
    } else {
      return 0.8f / static_cast<float>(number_of_relevant_players);
    }
  }

  /// \brief On a regular board, there is an average of 1.01 planets per system. Each player must have a minimum number of planets per system, including in-slice and equidistant positions.
  bool players_have_enough_planets() const noexcept {
    std::map<Player, float> players_to_effective_number_of_systems;
    std::map<Player, float> players_to_effective_number_of_planets;
    for (const Player player : players_) {
      players_to_effective_number_of_systems.emplace(player, 0.0f);
      players_to_effective_number_of_planets.emplace(player, 0.0f);
    }
    for (const std::pair<Position, std::set<Player>>& position_and_relevant_players : positions_to_relevant_players_) {
      const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position_and_relevant_players.first)};
      const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
      // Exclude the Mecatol Rex system, hyperlanes, and other irrelevant system categories.
      if (system->category() == SystemCategory::Planetary || system->category() == SystemCategory::AnomalyWormholeEmpty) {
        const float factor{number_of_relevant_players_factor(position_and_relevant_players.second.size())};
        for (const Player player : position_and_relevant_players.second) {
          players_to_effective_number_of_systems[player] += factor;
          players_to_effective_number_of_planets[player] += static_cast<float>(system->planets().size()) * factor;
        }
      }
    }
    for (const Player player : players_) {
      const float effective_planets_to_positions_ratio{players_to_effective_number_of_planets[player] / players_to_effective_number_of_systems[player]};
      if (effective_planets_to_positions_ratio < 0.76f) {
        return false;
      }
    }
    return true;
  }

  /// \brief On a regular board, there is an average of 1.03 useful resources per system and 1.15 useful influence per system. Each player must have a minimum amount of useful resources per system and useful influence per system, including in-slice and equidistant positions.
  bool players_have_enough_useful_resources_and_useful_influence() const noexcept {
    std::map<Player, float> players_to_number_of_systems;
    std::map<Player, float> players_to_useful_resources;
    std::map<Player, float> players_to_useful_influence;
    for (const Player& player : players_) {
      players_to_number_of_systems.emplace(player, 0.0f);
      players_to_useful_resources.emplace(player, 0.0f);
      players_to_useful_influence.emplace(player, 0.0f);
    }
    for (const std::pair<Position, std::set<Player>>& position_and_relevant_players : positions_to_relevant_players_) {
      const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position_and_relevant_players.first)};
      const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
      // Exclude the Mecatol Rex system, hyperlanes, and other irrelevant system categories.
      if (system->category() == SystemCategory::Planetary || system->category() == SystemCategory::AnomalyWormholeEmpty) {
        const float factor{number_of_relevant_players_factor(position_and_relevant_players.second.size())};
        for (const Player& player : position_and_relevant_players.second) {
          players_to_number_of_systems[player] += factor;
          for (const Planet& planet : system->planets()) {
            players_to_useful_resources[player] += planet.useful_resources() * factor;
            players_to_useful_influence[player] += planet.useful_influence() * factor;
          }
        }
      }
    }
    for (const Player player : players_) {
      const float useful_resources_per_system{players_to_useful_resources[player] / players_to_number_of_systems[player]};
      if (useful_resources_per_system < 0.52f) {
        return false;
      }
      const float useful_influence_per_system{players_to_useful_influence[player] / players_to_number_of_systems[player]};
      if (useful_influence_per_system < 0.58f) {
        return false;
      }
    }
    return true;
  }

  void calculate_player_scores() noexcept {
    reset_scores();
    add_base_system_scores();
    add_preferred_expansion_position_scores();
    add_alternate_expansion_position_scores();
    add_mecatol_rex_pathway_scores();
    add_number_of_systems_containing_planets_adjacent_to_home_scores();
  }

  void reset_scores() noexcept {
    for (std::map<Player, float>::iterator player_score = player_scores_.begin(); player_score != player_scores_.end(); ++player_score) {
      player_score->second = 0.0;
    }
  }

  /// \brief Systems that are further away from your home system are worth less.
  float distance_factor(const Distance& distance) const noexcept {
    if (distance <= Distance{1}) {
      return 1.0f;
    } else if (distance == Distance{2}) {
      return 0.9f;
    } else if (distance == Distance{3}) {
      return 0.8f;
    } else {
      return 0.7f;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets a fraction of its score.
  void add_base_system_scores() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      const std::unordered_map<Position, std::map<Player, Distance>>::const_iterator position_and_players_home_distances{positions_to_players_home_distances_.find(position_and_tile.first)};
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty() && position_and_players_home_distances != positions_to_players_home_distances_.cend()) {
        const std::unordered_map<Position, std::set<Player>>::const_iterator position_to_relevant_players{positions_to_relevant_players_.find(position_and_tile.first)};
        if (position_to_relevant_players != positions_to_relevant_players_.cend()) {
          const float score_per_player{Systems.find({position_and_tile.second.system_id()})->score() * number_of_relevant_players_factor(position_to_relevant_players->second.size())};
          for (const Player& player : position_to_relevant_players->second) {
            const std::map<Player, Distance>::const_iterator player_and_distance{position_and_players_home_distances->second.find(player)};
            if (player_and_distance != position_and_players_home_distances->second.cend()) {
              player_scores_[player] += score_per_player * distance_factor(player_and_distance->second);
            }
          }
        }
      }
    }
  }

  /// \brief If a player can construct a space dock on either their preferred or laternate expansion positions, the score is increased.
  void add_expansion_position_scores() noexcept {
    std::map<Player, float> players_and_best_expansion_scores;
    for (const Player& player : players_) {
      players_and_best_expansion_scores.emplace(player, 0.0f);
    }
    for (const std::pair<Player, std::set<Position>>& player_and_preferred_expansion_positions : players_to_preferred_expansion_positions_) {
      for (const Position& position : player_and_preferred_expansion_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        const float preferred_expansion_position_score{system->expansion_score()};
        if (preferred_expansion_position_score > players_and_best_expansion_scores[player_and_preferred_expansion_positions.first]) {
          players_and_best_expansion_scores[player_and_preferred_expansion_positions.first] = preferred_expansion_position_score;
        }
      }
    }
    for (const std::pair<Player, std::set<Position>>& player_and_alternate_expansion_positions : players_to_alternate_expansion_positions_) {
      for (const Position& position : player_and_alternate_expansion_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        const float alternate_expansion_position_score{0.5f * system->expansion_score()};
        if (alternate_expansion_position_score > players_and_best_expansion_scores[player_and_alternate_expansion_positions.first]) {
          players_and_best_expansion_scores[player_and_alternate_expansion_positions.first] = alternate_expansion_position_score;
        }
      }
    }
    for (const std::pair<Player, float>& player_and_best_expansion_score : players_and_best_expansion_scores) {
      player_scores_[player_and_best_expansion_score.first] += player_and_best_expansion_score.second;
    }
  }

  /// \brief If a player can construct a space dock on their preferred expansion positions, the score is increased.
  void add_preferred_expansion_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_preferred_expansion_positions : players_to_preferred_expansion_positions_) {
      if (!player_and_preferred_expansion_positions.second.empty()) {
        float average_preferred_expansion_position_score{0.0f};
        for (const Position& position : player_and_preferred_expansion_positions.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          const float preferred_expansion_position_score{system->expansion_score()};
          average_preferred_expansion_position_score += preferred_expansion_position_score;
        }
        average_preferred_expansion_position_score /= static_cast<float>(player_and_preferred_expansion_positions.second.size());
        player_scores_[player_and_preferred_expansion_positions.first] += average_preferred_expansion_position_score;
      }
    }
  }

  /// \brief If a player can construct a space dock on their alternate expansion positions, the score is increased.
  void add_alternate_expansion_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_alternate_expansion_positions : players_to_alternate_expansion_positions_) {
      if (!player_and_alternate_expansion_positions.second.empty()) {
        float average_alternate_expansion_position_score{0.0f};
        for (const Position& position : player_and_alternate_expansion_positions.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          const float alternate_expansion_position_score{0.5f * system->expansion_score()};
          average_alternate_expansion_position_score += alternate_expansion_position_score;
        }
        average_alternate_expansion_position_score /= static_cast<float>(player_and_alternate_expansion_positions.second.size());
        player_scores_[player_and_alternate_expansion_positions.first] += average_alternate_expansion_position_score;
      }
    }
  }

  /// \brief If a player does not have a clear pathway to Mecatol Rex, the score is penalized.
  void add_mecatol_rex_pathway_scores() noexcept {
    for (const std::pair<Player, std::vector<Pathway>>& player_and_mecatol_rex_pathways : players_to_mecatol_rex_pathways_) {
      if (!player_and_mecatol_rex_pathways.second.empty()) {
        float best_pathway_score{std::numeric_limits<float>::lowest()};
        for (const Pathway& pathway : player_and_mecatol_rex_pathways.second) {
          float pathway_score{0.0f};
          for (const Position& position : pathway) {
            const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
            const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
            if (system->contains(Anomaly::GravityRift)) {
              // A gravity rift along the pathway to Mecatol Rex is undesirable.
              pathway_score += -3.0f;
            }
            if (system->contains(Anomaly::Nebula)) {
              // A nebula along the pathway to Mecatol Rex is undesirable.
              pathway_score += -3.0f;
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

  void add_number_of_systems_containing_planets_adjacent_to_home_scores() noexcept {
    // Check the forward systems and the lateral systems.
    // Ideally, a player wants two systems that each contain one or more planets adjacent to their home.
    for (const Player& player : players_) {
      uint8_t number_of_systems_containing_planets{0};
      const std::map<Player, std::set<Position>>::const_iterator player_and_forward_positions{players_to_forward_positions_.find(player)};
      if (player_and_forward_positions != players_to_forward_positions_.cend()) {
        for (const Position& position : player_and_forward_positions->second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          if (!system->planets().empty()) {
            ++number_of_systems_containing_planets;
          }
        }
      }
      const std::map<Player, std::set<Position>>::const_iterator player_and_lateral_positions{players_to_lateral_positions_.find(player)};
      if (player_and_lateral_positions != players_to_lateral_positions_.cend()) {
        for (const Position& position : player_and_lateral_positions->second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          if (!system->planets().empty()) {
            ++number_of_systems_containing_planets;
          }
        }
      }
      player_scores_[player] += 2.0f * (static_cast<float>(number_of_systems_containing_planets) - 2.0f);
    }
  }

  float score_imbalance_ratio() const noexcept {
    float maximum_score{std::numeric_limits<float>::lowest()};
    float average_score{0.0f};
    float minimum_score{std::numeric_limits<float>::max()};
    for (const std::pair<Player, float> player_score : player_scores_) {
      if (player_score.second > maximum_score) {
        maximum_score = player_score.second;
      }
      average_score += player_score.second;
      if (player_score.second < minimum_score) {
        minimum_score = player_score.second;
      }
    }
    average_score /= player_scores_.size();
    return std::max(average_score - minimum_score, maximum_score - average_score) / average_score;
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
    const std::set<Tile> ordered_tiles_{ordered_tiles()};
    std::string text;
    for (const Tile& tile : ordered_tiles_) {
      if (tile.system_id() != MecatolRexSystemId) {
        if (!text.empty()) {
          // Tabletop Simulator uses a space as separator.
          text += " ";
        }
        const std::unordered_set<System>::const_iterator system{Systems.find({tile.system_id()})};
        if (system != Systems.cend() && system->category() == SystemCategory::Hyperlane) {
          // Tabletop Simulator and the visualizer use different naming conventions for the orientation of the hyperlane tiles.
          // In Tabletop Simulator, the orientation directly follows the base name, for example: 85A0.
          // In the visualizer, there is a hyphen between the base name and the orientation, for example: 85A-0.
          // A hyphen is included in the system IDs by default, so remove it when printing the Tabletop Simultor string.
          text += remove_character(tile.system_id(), '-');
        } else {
          text += tile.system_id();
        }
      }
    }
    return text;
  }

  std::string print_visualization_link() const noexcept {
    const std::set<Tile> ordered_tiles_{ordered_tiles()};
    const std::string prefix{"https://keeganw.github.io/ti4/?settings=T" + std::to_string(players_.size()) + "0000&tiles="};
    std::string text;
    for (const Tile& tile : ordered_tiles_) {
      if (!text.empty()) {
        // The visualizer uses a comma as separator.
        text += ",";
      }
      text += tile.system_id();
    }
    return prefix + text;
  }

  std::set<Tile> ordered_tiles() const noexcept {
    std::set<Tile> ordered_tiles_;
    for (int8_t layer = 0; layer <= maximum_layer_; ++layer) {
      const int8_t maximum_azimuth_{maximum_azimuth(layer)};
      for (int8_t azimuth = 0; azimuth <= maximum_azimuth_; ++azimuth) {
        const Position position{layer, azimuth};
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        if (position_and_tile != positions_to_tiles_.cend()) {
          ordered_tiles_.insert(position_and_tile->second);
        } else {
          // In this case, this is a skipped tile.
          ordered_tiles_.insert({position, "-1"});
        }
      }
    }
    return ordered_tiles_;
  }

}; // class Board

} // namespace TI4Cartographer
