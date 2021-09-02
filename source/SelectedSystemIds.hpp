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

  void initialize(
    const GameVersion game_version,
    const Layout layout,
    const Aggression aggression,
    const uint8_t number_of_equidistant_systems
  ) {
    const std::vector<SystemIdAndScore> selected_sorted_system_ids_and_scores_{selected_sorted_system_ids_and_scores(game_version, layout)};
    const uint8_t number_of_systems{static_cast<uint8_t>(selected_sorted_system_ids_and_scores_.size())};
    // Randomly choose the equidistant systems from among the possible ones.
    const std::vector<uint8_t> shuffled_possible_equidistant_indices_{shuffled_possible_equidistant_indices(aggression, number_of_systems, number_of_equidistant_systems)};
    std::unordered_set<uint8_t> equidistant_indices;
    for (uint8_t counter = 0; counter < number_of_equidistant_systems; ++counter) {
      const uint8_t index{shuffled_possible_equidistant_indices_[counter]};
      equidistant_indices.insert(index);
      equidistant_.push_back(selected_sorted_system_ids_and_scores_[index].id());
    }
    // The remaining indices are the in-slice ones.
    for (uint8_t index = 0; index < number_of_systems; ++index) {
      if (equidistant_indices.find(index) == equidistant_indices.cend()) {
        in_slice_.push_back(selected_sorted_system_ids_and_scores_[index].id());
      }
    }
  }

  std::vector<SystemIdAndScore> selected_sorted_system_ids_and_scores(const GameVersion game_version, const Layout layout) const noexcept {
    std::vector<SystemIdAndScore> selected_sorted_system_ids_and_scores_;
    for (const std::string& system_id : shuffled_selected_system_ids(SystemCategory::Planetary, game_version, layout)) {
      selected_sorted_system_ids_and_scores_.push_back({system_id, Systems.find({system_id})->score()});
    }
    for (const std::string& system_id : shuffled_selected_system_ids(SystemCategory::AnomalyWormholeEmpty, game_version, layout)) {
      selected_sorted_system_ids_and_scores_.push_back({system_id, Systems.find({system_id})->score()});
    }
    std::sort(selected_sorted_system_ids_and_scores_.begin(), selected_sorted_system_ids_and_scores_.end(), SystemIdAndScore::sort_by_descending_score());
    return selected_sorted_system_ids_and_scores_;
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
    const uint8_t number_of_systems_needed{number_of_systems(system_category, layout)};
    if (all_relevant_system_ids_.size() < number_of_systems_needed) {
      error("This game board needs " + std::to_string(number_of_systems_needed) + " " + label(system_category) + " systems, but there are only " + std::to_string(all_relevant_system_ids_.size()) + " " + label(system_category) + " systems that exist in total.");
      return {};
    } else {
      std::vector<std::string> selected_relevant_system_ids;
      for (std::size_t index = 0; index < number_of_systems_needed; ++index) {
        selected_relevant_system_ids.push_back(all_relevant_system_ids_[index]);
      }
      return selected_relevant_system_ids;
    }
  }

  std::vector<uint8_t> shuffled_possible_equidistant_indices(const Aggression aggression, const uint8_t number_of_systems, const uint8_t number_of_equidistant_systems) const noexcept {
    std::pair<uint8_t, uint8_t> start_and_end_indices;
    switch (aggression) {
      case Aggression::Low:
        start_and_end_indices = start_and_end_indices_low_agggression(number_of_systems, number_of_equidistant_systems);
        break;
      case Aggression::Moderate:
        start_and_end_indices = start_and_end_indices_moderate_agggression(number_of_systems, number_of_equidistant_systems);
        break;
      case Aggression::High:
        start_and_end_indices = start_and_end_indices_high_agggression(number_of_systems, number_of_equidistant_systems);
        break;
    }
    std::vector<uint8_t> possible_equidistant_indices_;
    for (uint8_t index = start_and_end_indices.first; index < start_and_end_indices.second; ++index) {
      possible_equidistant_indices_.push_back(index);
    }
    std::shuffle(possible_equidistant_indices_.begin(), possible_equidistant_indices_.end(), RandomEngine);
    return possible_equidistant_indices_;
  }

  /// \brief The end index is one past the end, as in the standard containers.
  std::pair<uint8_t, uint8_t> start_and_end_indices_low_agggression(const uint8_t number_of_systems, const uint8_t number_of_equidistant_systems) const noexcept {
    const uint8_t start_index_1{static_cast<uint8_t>(number_of_systems - number_of_systems / 3)};
    const uint8_t end_index{static_cast<uint8_t>(number_of_systems)};
    if (end_index - start_index_1 >= number_of_equidistant_systems) {
      return {start_index_1, end_index};
    } else {
      const uint8_t start_index_2{static_cast<uint8_t>(number_of_systems - number_of_equidistant_systems)};
      return {std::min(start_index_1, start_index_2), end_index};
    }
  }

  /// \brief The end index is one past the end, as in the standard containers.
  std::pair<uint8_t, uint8_t> start_and_end_indices_moderate_agggression(const uint8_t number_of_systems, const uint8_t number_of_equidistant_systems) const noexcept {
    const uint8_t start_index_1{static_cast<uint8_t>(number_of_systems / 3)};
    const uint8_t end_index_1{static_cast<uint8_t>(number_of_systems - number_of_systems / 3)};
    if (end_index_1 - start_index_1 >= number_of_equidistant_systems) {
      return {start_index_1, end_index_1};
    } else {
      const uint8_t start_index_2{static_cast<uint8_t>(std::floor(0.5f * (number_of_systems - number_of_equidistant_systems)))};
      const uint8_t end_index_2{static_cast<uint8_t>(std::ceil(0.5f * (number_of_systems + number_of_equidistant_systems)))};
      return {start_index_2, end_index_2};
    }
  }

  /// \brief The end index is one past the end, as in the standard containers.
  std::pair<uint8_t, uint8_t> start_and_end_indices_high_agggression(const uint8_t number_of_systems, const uint8_t number_of_equidistant_systems) const noexcept {
    const uint8_t start_index{0};
    const uint8_t end_index_1{static_cast<uint8_t>(number_of_systems / 3)};
    if (end_index_1 - start_index >= number_of_equidistant_systems) {
      return {start_index, end_index_1};
    } else {
      const uint8_t end_index_2{static_cast<uint8_t>(number_of_equidistant_systems)};
      return {start_index, end_index_2};
    }
  }

}; // class SelectedSystemIds

} // namespace TI4Cartographer
