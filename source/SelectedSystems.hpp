#pragma once

#include "Systems.hpp"

namespace ti4cartographer {


class SelectedSystems {

public:

  SelectedSystems() noexcept {}

  SelectedSystems(const GameVersion game_version, const uint8_t number_of_planetary_systems, const uint8_t number_of_anomaly_wormhole_empty_systems) noexcept {
    initialize_planetary_systems(game_version, number_of_planetary_systems);
    initialize_wormhole_anomaly_empty_systems(game_version, number_of_anomaly_wormhole_empty_systems);
    std::shuffle(ids_.begin(), ids_.end(), RandomEngine);
  }

  const std::vector<uint8_t>& ids() const noexcept {
    return ids_;
  }

  std::string print() const noexcept {
    std::string text{"System IDs:"};
    for (const uint8_t id : ids_) {
      text += " " + std::to_string(id);
    }
    return text;
  }

protected:

  std::vector<uint8_t> ids_;

  void initialize_planetary_systems(const GameVersion game_version, const uint8_t number_of_planetary_systems) noexcept {
    std::vector<uint8_t> all;
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
    if (all.size() < number_of_planetary_systems) {
      error("The requested number of planetary systems for the game board exceeds the actual number of planetary systems that exist in the game.");
    }
    std::shuffle(all.begin(), all.end(), RandomEngine);
    for (std::size_t i = 0; i < number_of_planetary_systems; ++i) {
      ids_.push_back(all[i]);
    }
  }

  void initialize_wormhole_anomaly_empty_systems(const GameVersion game_version, const uint8_t number_of_anomaly_wormhole_empty_systems) noexcept {
    std::vector<uint8_t> all;
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
