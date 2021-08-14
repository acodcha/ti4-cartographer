#pragma once

#include "Instructions.hpp"
#include "Systems.hpp"

namespace ti4cartographer {

class SelectedSystems {

public:

  SelectedSystems() noexcept {}

  SelectedSystems(const Instructions& instructions) noexcept {
    initialize_planetary_systems(instructions);
    initialize_wormhole_anomaly_empty_systems(instructions);
    std::shuffle(ids_.begin(), ids_.end(), RandomEngine);
  }

  const std::vector<std::string>& ids() const noexcept {
    return ids_;
  }

  std::string print() const noexcept {
    std::string text{"System IDs:"};
    for (const std::string id : ids_) {
      text += " " + id;
    }
    return text;
  }

protected:

  std::vector<std::string> ids_;

  void initialize_planetary_systems(const Instructions& instructions) noexcept {
    std::vector<std::string> all;
    switch (instructions.game_version()) {
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
    const uint8_t number_of_planetary_systems{static_cast<uint8_t>(number_of_planetary_systems_per_player(instructions.board_layout()) * number_of_players(instructions.board_layout()))};
    if (all.size() < number_of_planetary_systems) {
      error("The requested number of planetary systems for the game board exceeds the actual number of planetary systems that exist in the game.");
    }
    std::shuffle(all.begin(), all.end(), RandomEngine);
    for (std::size_t i = 0; i < number_of_planetary_systems; ++i) {
      ids_.push_back(all[i]);
    }
  }

  void initialize_wormhole_anomaly_empty_systems(const Instructions& instructions) noexcept {
    std::vector<std::string> all;
    switch (instructions.game_version()) {
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
    const uint8_t number_of_anomaly_wormhole_empty_systems{static_cast<uint8_t>(number_of_anomaly_wormhole_empty_systems_per_player(instructions.board_layout()) * number_of_players(instructions.board_layout()))};
    if (all.size() < number_of_anomaly_wormhole_empty_systems) {
      error("The requested number of anomaly/wormhole/empty systems for the game board exceeds the actual number of anomaly/wormhole/empty systems that exist in the game.");
    }
    std::shuffle(all.begin(), all.end(), RandomEngine);
    for (std::size_t i = 0; i < number_of_anomaly_wormhole_empty_systems; ++i) {
      ids_.push_back(all[i]);
    }
  }

}; // class SelectedSystems

} // namespace ti4cartographer
