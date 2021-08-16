#pragma once

#include "BoardLayouts.hpp"
#include "Systems.hpp"

namespace TI4Cartographer {

/// \brief Group of randomly-selected system IDs for the game board.
class SelectedSystemIds {

public:

  SelectedSystemIds() noexcept {}

  SelectedSystemIds(const GameVersion game_version, const BoardLayout board_layout) noexcept {
    initialize_systems<SystemCategory::Planetary>(game_version, board_layout);
    initialize_systems<SystemCategory::AnomalyWormholeEmpty>(game_version, board_layout);
  }

  std::string print() const noexcept {
    std::string text;
    for (const std::string id : data_) {
      if (!text.empty()) {
        text += " ";
      }
      text += id;
    }
    return text;
  }

  struct const_iterator : public std::set<std::string>::const_iterator {
    const_iterator(const std::set<std::string>::const_iterator i) noexcept : std::set<std::string>::const_iterator(i) {}
  };

  std::size_t size() const noexcept {
    return data_.size();
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(data_.cbegin());
  }

  const_iterator begin() const noexcept {
   return cbegin();
  }

  const_iterator cend() const noexcept {
   return const_iterator(data_.cend());
  }

  const_iterator end() const noexcept {
   return cend();
  }

protected:

  std::set<std::string> data_;

  template <SystemCategory system_category> void initialize_systems(const GameVersion game_version, const BoardLayout board_layout) noexcept {
    std::vector<std::string> system_ids;
    switch (game_version) {
      case GameVersion::BaseGame:
        for (const System& system : Systems) {
          if (system.game_version() == GameVersion::BaseGame && system.category() == system_category) {
            system_ids.push_back(system.id());
          }
        }
        break;
      case GameVersion::ProphecyOfKingsExpansion:
        for (const System& system : Systems) {
          if (system.category() == system_category) {
            system_ids.push_back(system.id());
          }
        }
        break;
    }
    std::shuffle(system_ids.begin(), system_ids.end(), RandomEngine);
    const uint8_t number_of_systems{static_cast<uint8_t>(number_of_systems_per_player<system_category>(board_layout) * number_of_players(board_layout))};
    if (system_ids.size() < number_of_systems) {
      error("The requested number of systems for the game board exceeds the actual number of systems that exist in the game.");
    }
    for (std::size_t i = 0; i < number_of_systems; ++i) {
      data_.insert(system_ids[i]);
    }
  }

}; // class SelectedSystemIds

} // namespace TI4Cartographer
