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
    const uint64_t maximum_number_of_attempts,
    const uint64_t maximum_number_of_iterations
  ) noexcept :
    BoardInitializer(layout)
  {
    initialize_player_scores();
    attempt(game_version, layout, aggression, maximum_number_of_attempts, maximum_number_of_iterations);
    verbose_message("Player scores: " + print_player_scores());
    verbose_message("Score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio()));
    verbose_message("Visualization: " + print_visualization_link());
    verbose_message("Tabletop Simulator string: " + print_tabletop_simulator_string());
    quiet_message(print_tabletop_simulator_string());
    verbose_message("Runtime: " + chronometre.print());
  }

private:

  SelectedSystemIds selected_system_ids_;

  std::map<Player, float> player_scores_;

  float score_imbalance_ratio_{0.0};

  void initialize_player_scores() noexcept {
    for (const Player player : players_) {
      player_scores_.insert({player, 0.0});
    }
  }

  void attempt(
    const GameVersion game_version,
    const Layout layout,
    const Aggression aggression,
    const uint64_t maximum_number_of_attempts,
    const uint64_t maximum_number_of_iterations
  ) noexcept {
    uint64_t number_of_attempts{0};
    for (uint64_t counter = 0; counter < maximum_number_of_attempts; ++counter) {
      ++number_of_attempts;
      const float score_imbalance_ratio_tolerance{InitialScoreImbalanceRatioTolerance * std::pow(1.2f, static_cast<float>(counter))};
      verbose_message("Start of board generation attempt #" + std::to_string(number_of_attempts) + ": target score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio_tolerance));
      initialize_selected_system_ids(game_version, layout, aggression);
      iterate(maximum_number_of_iterations, score_imbalance_ratio_tolerance);
      verbose_message("End of board generation attempt #" + std::to_string(number_of_attempts) + ".");
      if (score_imbalance_ratio_ <= score_imbalance_ratio_tolerance) {
        break;
      }
    }
  }

  void initialize_selected_system_ids(const GameVersion game_version, const Layout layout, const Aggression aggression) noexcept {
    selected_system_ids_ = {game_version, layout, aggression, static_cast<uint8_t>(equidistant_positions_.size())};
  }

  void iterate(const uint64_t maximum_number_of_iterations, const float score_imbalance_ratio_tolerance) {
    std::unordered_map<Position, Tile> best_positions_to_tiles{positions_to_tiles_};
    std::map<Player, float> best_player_scores{player_scores_};
    float best_score_imbalance_ratio{std::numeric_limits<float>::max()};
    uint64_t number_of_iterations{0};
    uint64_t number_of_valid_boards{0};
    bool success{false};
    for (uint64_t counter = 0; counter < maximum_number_of_iterations; ++counter) {
      ++number_of_iterations;
      selected_system_ids_.shuffle();
      assign_system_ids_to_tiles_simple();
      if (!contains_adjacent_anomalies_or_wormholes()) {
        ++number_of_valid_boards;
        calculate_player_scores();
        score_imbalance_ratio_ = score_imbalance_ratio();
        if (score_imbalance_ratio_ < best_score_imbalance_ratio) {
          best_positions_to_tiles = positions_to_tiles_;
          best_player_scores = player_scores_;
          best_score_imbalance_ratio = score_imbalance_ratio_;
          verbose_message("Iteration " + std::to_string(number_of_iterations) + ": Score imbalance: " + score_imbalance_ratio_to_string(score_imbalance_ratio_));
          if (score_imbalance_ratio_ <= score_imbalance_ratio_tolerance) {
            success = true;
            break;
          }
        }
      }
    }
    positions_to_tiles_ = best_positions_to_tiles;
    player_scores_ = best_player_scores;
    score_imbalance_ratio_ = best_score_imbalance_ratio;
    if (success) {
      verbose_message("Found an optimal game board after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
    } else {
      verbose_message("No optimal game board could be found after " + std::to_string(number_of_iterations) + " iterations which generated " + std::to_string(number_of_valid_boards) + " valid game boards.");
    }
  }

  /// \brief After doing this, need to check for adjacent anomalies or wormholes.
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

  /// \brief Guarantees no adjacent anomalies or wormholes.
  void assign_system_ids_to_tiles_smart() {
    std::unordered_set<uint8_t> equidistant_system_indices_used;
    std::unordered_set<uint8_t> in_slice_system_indices_used;
    uint8_t equidistant_system_ids_index{0};
    uint8_t in_slice_system_ids_index{0};
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_map<Position, std::set<Position>>::const_iterator position_and_neighbors{neighbors_.find(position_and_tile.first)};
        if (is_equidistant(position_and_tile.first)) {





        } else if (is_in_a_slice(position_and_tile.first)) {





        }
      }
    }
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
  }

  void reset_scores() noexcept {
    for (std::map<Player, float>::iterator player_score = player_scores_.begin(); player_score != player_scores_.end(); ++player_score) {
      player_score->second = 0.0;
    }
  }

  /// \brief If a system is in a player's slice, that player gains its score. If a system is equidistant, each relevant player gets an equal fraction of its score.
  void add_base_system_scores() noexcept {
    for (const std::pair<Position, Tile>& position_and_tile : positions_to_tiles_) {
      if (position_and_tile.second.is_planetary_anomaly_wormhole_or_empty()) {
        const std::unordered_map<Position, std::set<Player>>::const_iterator position_to_relevant_players{positions_to_relevant_players_.find(position_and_tile.first)};
        if (position_to_relevant_players != positions_to_relevant_players_.cend()) {
          const float score{Systems.find({position_and_tile.second.system_id()})->score()};
          const uint8_t number_of_relevant_players{static_cast<uint8_t>(position_to_relevant_players->second.size())};
          const float score_per_player{score / number_of_relevant_players};
          for (const Player& player : position_to_relevant_players->second) {
            player_scores_[player] += score_per_player;
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
        if (system->contains(Anomaly::AsteroidField)) {
          // An asteroid field in a lateral system is beneficial.
          player_scores_[player_and_lateral_positions.first] += -2.0f * Score::AsteroidField;
        }
        if (system->contains(Anomaly::GravityRift)) {
          // A gravity rift in a lateral system is very dangerous.
          player_scores_[player_and_lateral_positions.first] += 7.0f * Score::GravityRift;
        }
        if (system->contains(Anomaly::Nebula)) {
          // A nebula in a lateral system is beneficial.
          player_scores_[player_and_lateral_positions.first] += -2.0f * Score::Nebula;
        }
        if (system->contains(Anomaly::Supernova)) {
          // A nebula in a lateral system is beneficial.
          player_scores_[player_and_lateral_positions.first] += -2.0f * Score::Supernova;
        }
        if (system->contains_one_or_more_wormholes()) {
          // A gravity rift in a lateral system is somewhat dangerous.
          player_scores_[player_and_lateral_positions.first] += -1.0f * Score::Wormhole;
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
              // A supernova anywhere along the pathway to Mecatol Rex is quite bad.
              pathway_score += 11.0f * Score::Supernova;
            }
            if (system->contains(Anomaly::AsteroidField)) {
              // An asteroid field along the pathway to Mecatol Rex is bad but manageable.
              pathway_score += 3.0f * Score::AsteroidField;
            }
            if (system->contains(Anomaly::Nebula)) {
              if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second <= Distance{1}) {
                // A nebula adjacent to Mecatol Rex is somewhat annoying but manageable.
                pathway_score += 3.0f * Score::Nebula;
              } else {
                // A nebula elsewhere along the pathway to Mecatol Rex is quite bad.
                pathway_score += 7.0f * Score::Nebula;
              }
            }
            if (system->contains(Anomaly::GravityRift)) {
              if (positions_to_distances_from_mecatol_rex_.find(position_and_tile->first)->second <= Distance{1}) {
                // A gravity rift adjacent to Mecatol Rex is annoying.
                pathway_score += 11.0f * Score::GravityRift;
              } else {
                // A gravity rift elsewhere on the pathway to Mecatol Rex is quite bad.
                pathway_score += 23.0f * Score::GravityRift;
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
          const float preferred_position_score{system->space_dock_score()};
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
          const float alternate_position_score{0.5f * system->space_dock_score()};
          if (alternate_position_score > best_alternate_position_score) {
            best_alternate_position_score = alternate_position_score;
          }
        }
        player_scores_[player_and_alternate_position.first] += best_alternate_position_score;
      }
    }
  }

  /// \brief Each player ideally wants 5+ planets and 4+ planets of the same trait in their slice. Adjust the score accordingly.
  void add_number_of_planets_scores() noexcept {
    std::map<Player, float> players_to_number_of_planets;
    std::map<Player, std::map<PlanetTrait, float>> players_to_planet_traits_to_number_of_planets;
    for (const Player& player : players_) {
      players_to_number_of_planets.insert({player, 0.0f});
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
            if (planet.trait().has_value()) {
              for (const Player& player : position_and_relevant_players.second) {
                players_to_planet_traits_to_number_of_planets[player][planet.trait().value()] += one_over_relevant_players;
              }
            }
          }
        }
      }
    }
    for (const std::pair<Player, float>& player_and_number_of_planets : players_to_number_of_planets) {
      const float number_of_planets_minus_5{player_and_number_of_planets.second - 5.0f};
      player_scores_[player_and_number_of_planets.first] += 0.068f * std::pow(number_of_planets_minus_5, 3) + 1.34f * number_of_planets_minus_5;
    }
    for (const std::pair<Player, std::map<PlanetTrait, float>>& player_and_planet_traits_to_number_of_planets : players_to_planet_traits_to_number_of_planets) {
      for (const std::pair<PlanetTrait, float>& planet_trait_to_number_of_planets : player_and_planet_traits_to_number_of_planets.second) {
        const float number_of_planets_minus_4{planet_trait_to_number_of_planets.second - 4.0f};
        player_scores_[player_and_planet_traits_to_number_of_planets.first] += 0.036f * std::pow(number_of_planets_minus_4, 3) + -0.285f * std::pow(number_of_planets_minus_4, 2) + 0.798f * number_of_planets_minus_4 + 2.02;
      }
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
