#pragma once

#include "System.hpp"

namespace TI4Cartographer {

const std::unordered_set<System> Systems{
  { 19, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Wellon", 1, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 20, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Vefut II", 2, 2, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { 21, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Thibah", 1, 1, {TechnologyType::Propulsion}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 22, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Tar'mann", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 23, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Saudor", 2, 2, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 24, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Mehar Xull", 1, 3, {TechnologyType::Warfare}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { 25, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Quann", 2, 1, {}, {PlanetTrait::Cultural}, {}}},
    {}, {Wormhole::Beta}
  },
  { 26, GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Lodor", 3, 1, {}, {PlanetTrait::Cultural}, {}}},
    {}, {Wormhole::Alpha}
  },
  { 27, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"New Albion", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}},
      {"Starpoint", 3, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 28, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Tequ'ran", 2, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Torkan", 0, 3, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { 29, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Qucen'n", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Rarron", 0, 3, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { 30, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Mellon", 0, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Zohbat", 3, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 31, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Lazar", 1, 0, {TechnologyType::Cybernetic}, {PlanetTrait::Industrial}, {}},
      {"Sakulag", 2, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 32, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Dal Bootha", 0, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Xxehan", 1, 1, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { 33, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Corneeq", 1, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Resculon", 2, 0, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { 34, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Centauri", 1, 3, {}, {PlanetTrait::Cultural}, {}},
      {"Gral", 1, 1, {TechnologyType::Propulsion}, {PlanetTrait::Industrial}, {}}
    }, {}, {}
  },
  { 35, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Bereg", 3, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Lirta IV", 2, 3, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 36, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Arnor", 2, 1, {}, {PlanetTrait::Industrial}, {}},
      {"Lor", 1, 2, {}, {PlanetTrait::Industrial}, {}}
    }, {}, {}
  },
  { 37, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Arinam", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Meer", 0, 4, {TechnologyType::Warfare}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 38, GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Abyz", 3, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Fria", 2, 0, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { 39, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {Wormhole::Alpha}
  },
  { 40, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {Wormhole::Beta}
  },
  { 41, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::GravityRift}, {}
  },
  { 42, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Nebula}, {}
  },
  { 43, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Supernova}, {}
  },
  { 44, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {}
  },
  { 45, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {}
  },
  { 46, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 47, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 48, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 49, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 50, GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 59, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Archon Vail", 1, 3, {TechnologyType::Propulsion}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { 60, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Perimeter", 2, 1, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 61, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Ang", 2, 0, {TechnologyType::Warfare}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 62, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Sem-Lore", 3, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { 63, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Vorhal", 0, 2, {TechnologyType::Biotic}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { 64, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Atlas", 3, 1, {}, {PlanetTrait::Hazardous}, {}}},
    {}, {Wormhole::Beta}
  },
  { 65, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Primor", 2, 1, {}, {PlanetTrait::Cultural}, {LegendaryPlanet::Primor}}},
    {}, {}
  },
  { 66, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Hope's End", 3, 0, {}, {PlanetTrait::Hazardous}, {LegendaryPlanet::HopesEnd}}},
    {}, {}
  },
  { 67, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {{"Cormund", 2, 0, {}, {PlanetTrait::Hazardous}, {}}},
    {Anomaly::GravityRift}, {}
  },
  { 68, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {{"Everra", 3, 1, {}, {PlanetTrait::Cultural}, {}}},
    {Anomaly::Nebula}, {}
  },
  { 69, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Accoen", 2, 3, {}, {PlanetTrait::Industrial}, {}},
      {"Jeol Ir", 2, 3, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 70, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Kraag", 2, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Siig", 0, 2, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { 71, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Ba'kal", 3, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Alio Prima", 1, 1, {}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { 72, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Lisis", 2, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Velnor", 2, 1, {TechnologyType::Warfare}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 73, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Cealdri", 0, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Cultural}, {}},
      {"Xanhact", 0, 1, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { 74, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Vega Major", 2, 1, {}, {PlanetTrait::Cultural}, {}},
      {"Vega Minor", 1, 2, {TechnologyType::Propulsion}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { 75, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Abaddon", 1, 0, {}, {PlanetTrait::Cultural}, {}},
      {"Ashtroth", 2, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Loki", 1, 2, {}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { 76, GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Rigel I", 0, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Rigel II", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Rigel III", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { 77, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 78, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { 79, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {Wormhole::Alpha}
  },
  { 80, GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Supernova}, {}
  }
};

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

} // namespace TI4Cartographer
