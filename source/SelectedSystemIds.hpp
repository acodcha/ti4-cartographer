#pragma once

#include "BoardLayouts.hpp"
#include "Systems.hpp"

namespace ti4cartographer {

/// \brief Group of randomly-selected system IDs for the game board.
class SelectedSystemIds {

public:

  SelectedSystemIds() noexcept {}

  SelectedSystemIds(const GameVersion game_version, const BoardLayout board_layout) noexcept {
    initialize_planetary_systems(game_version, board_layout);
    initialize_wormhole_anomaly_empty_systems(game_version, board_layout);
    std::shuffle(ids_.begin(), ids_.end(), RandomEngine);
  }

  std::string print() const noexcept {
    std::string text{"System IDs:"};
    for (const std::string id : ids_) {
      text += " " + id;
    }
    return text;
  }

  struct const_iterator : public std::vector<std::string>::const_iterator {
    const_iterator(const std::vector<std::string>::const_iterator i) noexcept : std::vector<std::string>::const_iterator(i) {}
  };

  std::size_t size() const noexcept {
    return ids_.size();
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(ids_.cbegin());
  }

  const_iterator begin() const noexcept {
   return cbegin();
  }

  const_iterator cend() const noexcept {
   return const_iterator(ids_.cend());
  }

  const_iterator end() const noexcept {
   return cend();
  }

protected:

  std::vector<std::string> ids_;

  void initialize_planetary_systems(const GameVersion game_version, const BoardLayout board_layout) noexcept {
    std::vector<std::string> all;
    switch (game_version) {
      case GameVersion::BaseGame:
        for (const System& system : Systems) {
          if (system.game_version() == GameVersion::BaseGame && system.category() == SystemCategory::Planetary) {
            all.push_back(system.id());
          }
        }
        break;
      case GameVersion::ProphecyOfKingsExpansion:
        for (const System& system : Systems) {
          if (system.category() == SystemCategory::Planetary) {
            all.push_back(system.id());
          }
        }
        break;
    }
    const uint8_t number_of_planetary_systems{static_cast<uint8_t>(number_of_planetary_systems_per_player(board_layout) * number_of_players(board_layout))};
    if (all.size() < number_of_planetary_systems) {
      error("The requested number of planetary systems for the game board exceeds the actual number of planetary systems that exist in the game.");
    }
    std::shuffle(all.begin(), all.end(), RandomEngine);
    for (std::size_t i = 0; i < number_of_planetary_systems; ++i) {
      ids_.push_back(all[i]);
    }
  }

  void initialize_wormhole_anomaly_empty_systems(const GameVersion game_version, const BoardLayout board_layout) noexcept {
    std::vector<std::string> all;
    switch (game_version) {
      case GameVersion::BaseGame:
        for (const System& system : Systems) {
          if (system.game_version() == GameVersion::BaseGame && system.category() == SystemCategory::AnomalyWormholeEmpty) {
            all.push_back(system.id());
          }
        }
        break;
      case GameVersion::ProphecyOfKingsExpansion:
        for (const System& system : Systems) {
          if (system.category() == SystemCategory::AnomalyWormholeEmpty) {
            all.push_back(system.id());
          }
        }
        break;
    }
    const uint8_t number_of_anomaly_wormhole_empty_systems{static_cast<uint8_t>(number_of_anomaly_wormhole_empty_systems_per_player(board_layout) * number_of_players(board_layout))};
    if (all.size() < number_of_anomaly_wormhole_empty_systems) {
      error("The requested number of anomaly/wormhole/empty systems for the game board exceeds the actual number of anomaly/wormhole/empty systems that exist in the game.");
    }
    std::shuffle(all.begin(), all.end(), RandomEngine);
    for (std::size_t i = 0; i < number_of_anomaly_wormhole_empty_systems; ++i) {
      ids_.push_back(all[i]);
    }
  }

}; // class SelectedSystemIds

} // namespace ti4cartographer
