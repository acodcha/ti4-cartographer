#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Anomaly : uint8_t {
  AsteroidField,
  GravityRift,
  Nebula,
  Supernova
};

template <> const std::unordered_map<Anomaly, std::string> labels<Anomaly>{
  {Anomaly::AsteroidField, "Asteroid Field"},
  {Anomaly::GravityRift, "Gravity Rift"},
  {Anomaly::Nebula, "Nebula"},
  {Anomaly::Supernova, "Supernova"}
};

template <> const std::unordered_map<std::string, Anomaly> spellings<Anomaly>{
  {"asteroidfield", Anomaly::AsteroidField},
  {"gravityrift", Anomaly::GravityRift},
  {"nebula", Anomaly::Nebula},
  {"supernova", Anomaly::Supernova}
};

double score(const Anomaly anomaly) noexcept {
  switch (anomaly) {
    case Anomaly::AsteroidField:
      // If you have Antimass Deflectors researched, this is effectively an empty system.
      // If you do not, this is worse because it prevents movement and therefore reduces your options.
      // The Clan of Saar strongly prefers these due to their faction technology.
      return -0.25;
      break;
    case Anomaly::GravityRift:
      // Gives extra movement and therefore extra options, but might destroy your ships. Generally beneficial.
      return 0.5;
      break;
    case Anomaly::Nebula:
      // Better defense, but slows movement. Net neutral.
      // The Empyrean strongly prefers these due to their faction ability.
      return 0.0;
      break;
    case Anomaly::Supernova:
      // Prevents movement and therefore reduces your options. Generally bad.
      // The Embers of Muaat strongly prefer these due to their faction ability and technology.
      return -0.5;
      break;
  }
}

} // namespace TI4Cartographer
