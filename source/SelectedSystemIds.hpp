#pragma once

#include "Aggressions.hpp"
#include "Layouts.hpp"
#include "SelectedEquidistantSystemIds.hpp"
#include "SelectedInSliceSystemIds.hpp"
#include "Systems.hpp"

namespace TI4Cartographer {

/// \brief Randomly-selected system IDs for the game board.
class SelectedSystemIds {

public:

  SelectedSystemIds() noexcept {}

  SelectedSystemIds(
    const GameVersion game_version,
    const Layout layout,
    const Aggression aggression,
    const uint8_t number_of_equidistant_systems
  ) {
    initialize(game_version, layout, aggression, number_of_equidistant_systems);
    verbose_message("Equidistant system IDs: " + equidistant_.print_brief());
    verbose_message("In-slice system IDs: " + in_slice_.print_brief());
    verbose_message("Equidistant systems:");
    verbose_message(equidistant_.print_details());
    verbose_message("In-slice systems:");
    verbose_message(in_slice_.print_details());
  }

  void shuffle() noexcept {
    equidistant_.shuffle();
    in_slice_.shuffle();
  }

  const SelectedEquidistantSystemIds& equidistant() const noexcept {
    return equidistant_;
  }

  const SelectedInSliceSystemIds& in_slice() const noexcept {
    return in_slice_;
  }

protected:

  SelectedEquidistantSystemIds equidistant_;

  SelectedInSliceSystemIds in_slice_;

  void initialize(const GameVersion game_version, const Layout layout, const Aggression aggression, const uint8_t number_of_equidistant_systems) {
    std::vector<SystemIdAndScore> selected_sorted_system_ids_and_scores;
    for (const std::string& system_id : shuffled_selected_system_ids(SystemCategory::Planetary, game_version, layout)) {
      selected_sorted_system_ids_and_scores.push_back({system_id, Systems.find({system_id})->score()});
    }
    for (const std::string& system_id : shuffled_selected_system_ids(SystemCategory::AnomalyWormholeEmpty, game_version, layout)) {
      selected_sorted_system_ids_and_scores.push_back({system_id, Systems.find({system_id})->score()});
    }
    std::sort(selected_sorted_system_ids_and_scores.begin(), selected_sorted_system_ids_and_scores.end(), SystemIdAndScore::sort_by_descending_score());
    const uint8_t number_of_systems{static_cast<uint8_t>(selected_sorted_system_ids_and_scores.size())};
    const uint8_t start_index_{start_index(aggression, number_of_systems, number_of_equidistant_systems)};
    for (uint8_t index = 0; index < number_of_systems; ++index) {
      if (index >= start_index_ && index < start_index_ + number_of_equidistant_systems) {
        equidistant_.push_back(selected_sorted_system_ids_and_scores[index].id());
      } else {
        in_slice_.push_back(selected_sorted_system_ids_and_scores[index].id());
      }
    }
  }

  std::vector<std::string> shuffled_selected_system_ids(const SystemCategory system_category, const GameVersion game_version, const Layout layout) const {
    std::vector<std::string> all_relevant_system_ids_;
    switch (game_version) {
      case GameVersion::BaseGame:
        for (const System& system : Systems) {
          if (system.game_version() == GameVersion::BaseGame && system.category() == system_category) {
            all_relevant_system_ids_.push_back(system.id());
          }
        }
        break;
      case GameVersion::ProphecyOfKingsExpansion:
        for (const System& system : Systems) {
          if (system.category() == system_category) {
            all_relevant_system_ids_.push_back(system.id());
          }
        }
        break;
    }
    std::shuffle(all_relevant_system_ids_.begin(), all_relevant_system_ids_.end(), RandomEngine);
    const uint8_t number_of_systems_needed{static_cast<uint8_t>(number_of_systems_per_player(system_category, layout) * number_of_players(layout))};
    if (all_relevant_system_ids_.size() < number_of_systems_needed) {
      error("This game board needs " + std::to_string(number_of_systems_needed) + " " + label(system_category) + " systems, but there aree only " + std::to_string(all_relevant_system_ids_.size()) + " " + label(system_category) + " systems that exist in the game.");
      return {};
    } else {
      std::vector<std::string> selected_relevant_system_ids;
      for (std::size_t index = 0; index < number_of_systems_needed; ++index) {
        selected_relevant_system_ids.push_back(all_relevant_system_ids_[index]);
      }
      return selected_relevant_system_ids;
    }
  }

  uint8_t start_index(const Aggression aggression, const uint8_t number_of_systems, const uint8_t number_of_equidistant_systems) const noexcept {
    switch (aggression) {
      case Aggression::VeryLow:
        return number_of_systems - number_of_equidistant_systems;
        break;
      case Aggression::Low:
        return static_cast<uint8_t>(std::floor(number_of_systems * 0.7 - number_of_equidistant_systems * 0.5));
        break;
      case Aggression::Medium:
        return static_cast<uint8_t>(std::round(number_of_systems * 0.5 - number_of_equidistant_systems * 0.5));
        break;
      case Aggression::High:
        return static_cast<uint8_t>(std::ceil(number_of_systems * 0.3 - number_of_equidistant_systems * 0.5));
        break;
      case Aggression::VeryHigh:
        return 0;
        break;
    }
    return 0;
  }

}; // class SelectedSystemIds

} // namespace TI4Cartographer
