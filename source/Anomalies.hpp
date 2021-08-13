#pragma once

#include "Base.hpp"

namespace ti4cartographer {

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

} // namespace ti4cartographer
