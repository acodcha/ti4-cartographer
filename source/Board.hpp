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

  static constexpr const uint64_t maximum_number_of_iterations_per_attempt_{500000};

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
      const bool board_is_valid = assign_system_ids_to_tiles_simple();
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
        const bool board_is_valid = assign_system_ids_to_tiles_simple();
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
  bool assign_system_ids_to_tiles_simple() {
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
    return !contains_adjacent_anomalies_or_wormholes();
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

  /// \brief Assigns system IDs in a smart manner, trying to avoid invalid boards. Returns true if the board is valid and false otherwise.
  // TODO: This is a work in progress.
  bool assign_system_ids_to_tiles_smart() {
    std::unordered_set<uint8_t> equidistant_system_indices_used;
    std::unordered_set<uint8_t> in_slice_system_indices_used;
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (std::unordered_map<Position, Tile>::iterator position_and_tile = positions_to_tiles_.begin(); position_and_tile != positions_to_tiles_.end(); ++position_and_tile) {
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_map<Position, std::set<Position>>::const_iterator position_and_neighbors{neighbors_.find(position_and_tile->first)};
        if (position_and_neighbors != neighbors_.cend()) {
          const NeighborsContents neighbors_contents{position_and_neighbors->second, positions_to_tiles_};
          if (is_equidistant(position_and_tile->first)) {
            std::unordered_set<uint8_t> equidistant_system_indices_attempted;
            while (equidistant_system_indices_attempted.size() < selected_system_ids_.equidistant().size()) {
              const std::unordered_set<System>::const_iterator system{Systems.find({selected_system_ids_.equidistant()[equidistant_system_ids_index]})};
              bool success{false};
              if (equidistant_system_indices_used.find(equidistant_system_ids_index) == equidistant_system_indices_used.cend()) {
                if (!(system->contains_one_or_more_anomalies() && neighbors_contents.one_or_more_anomalies) && !(system->contains(Wormhole::Alpha) && neighbors_contents.one_or_more_alpha_wormholes) && !(system->contains(Wormhole::Beta) && neighbors_contents.one_or_more_beta_wormholes)) {
                  success = true;
                }
              }
              if (success) {
                position_and_tile->second.set_system_id(system->id());
                equidistant_system_indices_used.insert(equidistant_system_ids_index);
              } else {
                equidistant_system_indices_attempted.insert(equidistant_system_ids_index);
              }
              if (equidistant_system_ids_index + 1u < selected_system_ids_.equidistant().size()) {
                ++equidistant_system_ids_index;
              } else {
                equidistant_system_ids_index = 0;
              }
              if (success) {
                break;
              }
            }
            if (equidistant_system_indices_attempted.size() == selected_system_ids_.equidistant().size()) {
              return false;
              break;
            }
          } else if (is_in_a_slice(position_and_tile->first)) {
            std::unordered_set<uint8_t> in_slice_system_indices_attempted;
            while (in_slice_system_indices_attempted.size() < selected_system_ids_.in_slice().size()) {
              const std::unordered_set<System>::const_iterator system{Systems.find({selected_system_ids_.equidistant()[equidistant_system_ids_index]})};
              bool success{false};
              if (in_slice_system_indices_used.find(in_slice_system_ids_index) == in_slice_system_indices_used.cend()) {
                if (!(system->contains_one_or_more_anomalies() && neighbors_contents.one_or_more_anomalies) && !(system->contains(Wormhole::Alpha) && neighbors_contents.one_or_more_alpha_wormholes) && !(system->contains(Wormhole::Beta) && neighbors_contents.one_or_more_beta_wormholes)) {
                  success = true;
                }
              }
              if (success) {
                position_and_tile->second.set_system_id(selected_system_ids_.equidistant()[in_slice_system_ids_index]);
                in_slice_system_indices_used.insert(in_slice_system_ids_index);
              } else {
                in_slice_system_indices_attempted.insert(in_slice_system_ids_index);
              }
              if (in_slice_system_ids_index + 1u < selected_system_ids_.in_slice().size()) {
                ++in_slice_system_ids_index;
              } else {
                in_slice_system_ids_index = 0;
              }
              if (success) {
                break;
              }
            }
            if (in_slice_system_indices_attempted.size() == selected_system_ids_.in_slice().size()) {
              return false;
              break;
            }
          }
        }
      }
    }
    return true;
  }

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

  void calculate_player_scores() noexcept {
    reset_scores();
    add_base_system_scores();
    add_forward_system_scores();
    add_lateral_system_scores();
    add_mecatol_rex_pathway_scores();
    add_preferred_position_scores();
    add_alternate_position_scores();
    add_number_of_planets_scores();
    add_number_of_systems_containing_planets_adjacent_to_home_scores();
  }

  void reset_scores() noexcept {
    for (std::map<Player, float>::iterator player_score = player_scores_.begin(); player_score != player_scores_.end(); ++player_score) {
      player_score->second = 0.0;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets an equal fraction of its score.
  void add_base_system_scores() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      const std::unordered_map<Position, std::map<Player, Distance>>::const_iterator position_and_players_home_distances{positions_to_players_home_distances_.find(position_and_tile.first)};
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty() && position_and_players_home_distances != positions_to_players_home_distances_.cend()) {
        const std::unordered_map<Position, std::set<Player>>::const_iterator position_to_relevant_players{positions_to_relevant_players_.find(position_and_tile.first)};
        if (position_to_relevant_players != positions_to_relevant_players_.cend()) {
          const float score{Systems.find({position_and_tile.second.system_id()})->score()};
          const uint8_t number_of_relevant_players{static_cast<uint8_t>(position_to_relevant_players->second.size())};
          const float score_per_player{score / number_of_relevant_players};
          for (const Player& player : position_to_relevant_players->second) {
            const std::map<Player, Distance>::const_iterator player_and_distance{position_and_players_home_distances->second.find(player)};
            if (player_and_distance != position_and_players_home_distances->second.cend()) {
              // Further systems are worth less: 100% if adjacent to home (at distance 1), 80% if at distance 2, and 60% if at distance 3+.
              float factor{1.0f};
              if (player_and_distance->second == Distance{0}) {
                factor = 1.0f;
              } else if (player_and_distance->second == Distance{1}) {
                factor = 1.0f;
              } else if (player_and_distance->second == Distance{2}) {
                factor = 0.8f;
              } else {
                factor = 0.6f;
              }
              player_scores_[player] += factor * score_per_player;
            }
          }
        }
      }
    }
  }

  /// \brief If a player does not have at least one good forward system, the score is penalized.
  void add_forward_system_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_forward_positions : players_to_forward_positions_) {
      bool at_least_one_good_forward_system{false};
      for (const Position& position : player_and_forward_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (!system->planets().empty() && !system->contains_one_or_more_anomalies()) {
          at_least_one_good_forward_system = true;
          break;
        }
      }
      if (!at_least_one_good_forward_system)  {
        player_scores_[player_and_forward_positions.first] += -6.0f;
      }
    }
  }

  /// \brief If a player's lateral systems protect or endanger their home system, the score is adjusted accordingly.
  void add_lateral_system_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_lateral_positions : players_to_lateral_positions_) {
      for (const Position& position : player_and_lateral_positions.second) {
        const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (system->contains(Anomaly::GravityRift)) {
          // A gravity rift in a lateral system is more dangerous than usual.
          player_scores_[player_and_lateral_positions.first] += 3.0f * score(Anomaly::GravityRift);
        }
        if (system->contains_one_or_more_wormholes()) {
          // A wormhole in a lateral system is somewhat dangerous and cancels out the benefit of the wormhole.
          player_scores_[player_and_lateral_positions.first] += -WormholeScore;
        }
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
            if (system->contains(Anomaly::Supernova)) {
              // A supernova anywhere along the pathway to Mecatol Rex is bad.
              pathway_score += -4.0f;
            }
            if (system->contains(Anomaly::AsteroidField)) {
              // An asteroid field anywhere along the pathway to Mecatol Rex is bad.
              pathway_score += -1.0f;
            }
            if (system->contains(Anomaly::Nebula)) {
              if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second <= Distance{1}) {
                // A nebula adjacent to Mecatol Rex is bad.
                pathway_score += -1.0f;
              } else {
                // A nebula elsewhere along the pathway to Mecatol Rex is bad.
                pathway_score += -2.0f;
              }
            }
            if (system->contains(Anomaly::GravityRift)) {
              // A gravity rift anywhere along the pathway to Mecatol Rex is bad.
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

  /// \brief If a player can construct a space dock on their preferred positions, the score is increased.
  void add_preferred_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_preferred_positions : players_to_preferred_positions_) {
      if (!player_and_preferred_positions.second.empty()) {
        float average_preferred_position_score{0.0f};
        for (const Position& position : player_and_preferred_positions.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          const float preferred_position_score{system->preferred_and_alternate_position_score()};
          average_preferred_position_score += preferred_position_score;
        }
        average_preferred_position_score /= static_cast<float>(player_and_preferred_positions.second.size());
        player_scores_[player_and_preferred_positions.first] += average_preferred_position_score;
      }
    }
  }

  /// \brief If a player can construct a space dock on their alternate positions, the score is increased.
  void add_alternate_position_scores() noexcept {
    for (const std::pair<Player, std::set<Position>>& player_and_alternate_positions : players_to_alternate_positions_) {
      if (!player_and_alternate_positions.second.empty()) {
        float average_alternate_position_score{0.0f};
        for (const Position& position : player_and_alternate_positions.second) {
          const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position)};
          const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
          const float alternate_position_score{0.5f * system->preferred_and_alternate_position_score()};
          average_alternate_position_score += alternate_position_score;
        }
        average_alternate_position_score /= static_cast<float>(player_and_alternate_positions.second.size());
        player_scores_[player_and_alternate_positions.first] += average_alternate_position_score;
      }
    }
  }

  /// \brief Each player ideally wants 5+ planets, 2+ technology specialties, and 4+ planets of the same trait in their slice. Adjust the score accordingly.
  void add_number_of_planets_scores() noexcept {
    std::map<Player, float> players_to_number_of_planets;
    std::map<Player, float> players_to_useful_resources;
    std::map<Player, float> players_to_useful_influence;
    std::map<Player, float> players_to_number_of_technology_specialties;
    std::map<Player, std::map<PlanetTrait, float>> players_to_planet_traits_to_number_of_planets;
    for (const Player& player : players_) {
      players_to_number_of_planets.insert({player, 0.0f});
      players_to_number_of_technology_specialties.insert({player, 0.0f});
      players_to_planet_traits_to_number_of_planets.insert({player, {{PlanetTrait::Cultural, 0.0f}, {PlanetTrait::Hazardous, 0.0f}, {PlanetTrait::Industrial, 0.0f}}});
    }
    for (const std::pair<Position, std::set<Player>>& position_and_relevant_players : positions_to_relevant_players_) {
      const std::unordered_map<Position, Tile>::const_iterator position_and_tile{positions_to_tiles_.find(position_and_relevant_players.first)};
      if (position_and_tile->second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_set<System>::const_iterator system{Systems.find({position_and_tile->second.system_id()})};
        if (!system->planets().empty()) {
          const float number_of_planets_per_relevant_player{static_cast<float>(system->planets().size()) / static_cast<float>(position_and_relevant_players.second.size())};
          for (const Player& player : position_and_relevant_players.second) {
            players_to_number_of_planets[player] += number_of_planets_per_relevant_player;
          }
          const float one_over_relevant_players{1.0f / static_cast<float>(position_and_relevant_players.second.size())};
          for (const Planet& planet : system->planets()) {
            for (const Player& player : position_and_relevant_players.second) {
              players_to_useful_resources[player] += planet.useful_resources() * one_over_relevant_players;
              players_to_useful_influence[player] += planet.useful_influence() * one_over_relevant_players;
              if (planet.technology_specialty().has_value()) {
                players_to_number_of_technology_specialties[player] += one_over_relevant_players;
              }
              if (planet.trait().has_value()) {
                players_to_planet_traits_to_number_of_planets[player][planet.trait().value()] += one_over_relevant_players;
              }
            }
          }
        }
      }
    }
    // On average, a slice contains 5.05 planets. Adjust the score if a slice contains more or fewer planets.
    for (const std::pair<Player, float>& player_and_number_of_planets : players_to_number_of_planets) {
      player_scores_[player_and_number_of_planets.first] += 2.0f * (player_and_number_of_planets.second - 5.05f);
    }
    // On average, a slice contains 5.15 useful resources. Adjust the score if a slice contains more or fewer useful resources.
    for (const std::pair<Player, float>& player_and_useful_resources : players_to_useful_resources) {
      player_scores_[player_and_useful_resources.first] += 1.0f * (player_and_useful_resources.second - 5.15f);
    }
    // On average, a slice contains 5.76 useful influence. Adjust the score if a slice contains more or fewer useful influence.
    for (const std::pair<Player, float>& player_and_useful_influence : players_to_useful_influence) {
      player_scores_[player_and_useful_influence.first] += 1.5f * (player_and_useful_influence.second - 5.76f);
    }
    // On average, a slice contains 1.32 technology specialties. Adjust the score if a slice contains more or fewer technology specialties.
    for (const std::pair<Player, float>& player_and_number_of_technology_specialties : players_to_number_of_technology_specialties) {
      player_scores_[player_and_number_of_technology_specialties.first] += 2.0f * (player_and_number_of_technology_specialties.second - 1.32f);
    }
    // Several objectives require 4 planets with the same trait. On average, a slice contains 2 planets with the same trait. Adjust the score if a slice contains more or fewer planets with the same trait.
    for (const std::pair<Player, std::map<PlanetTrait, float>>& player_and_planet_traits_to_number_of_planets : players_to_planet_traits_to_number_of_planets) {
      for (const std::pair<PlanetTrait, float>& planet_trait_to_number_of_planets : player_and_planet_traits_to_number_of_planets.second) {
        player_scores_[player_and_planet_traits_to_number_of_planets.first] += 1.0f * (planet_trait_to_number_of_planets.second - 2.0f);
      }
    }
  }

  void add_number_of_systems_containing_planets_adjacent_to_home_scores() noexcept {
    // Check the forward systems and the lateral systems.
    // Ideally, you want 2 systems that contain 1 or more planets adjacent to your home.
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
