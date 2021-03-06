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

namespace {

const std::map<Anomaly, float> anomaly_scores{
  // If you have Antimass Deflectors researched, this is effectively an empty system.
  // If you do not, this is worse because it prevents movement and therefore reduces your options. Generally bad.
  // The Clan of Saar strongly prefers these due to their faction technology.
  {Anomaly::AsteroidField, -0.75f},
  // Gives extra movement and therefore extra options, but destroys 30% of your ships. Situationally useful, but dangerous.
  {Anomaly::GravityRift, -0.25f},
  // Better defense, but greatly impairs movement. Generally bad.
  // The Empyrean strongly prefers these due to their faction ability.
  {Anomaly::Nebula, -0.5f},
  // Prevents movement and therefore reduces your options. Generally bad.
  // The Embers of Muaat strongly prefer these due to their faction ability and technology.
  {Anomaly::Supernova, -1.0f}
};

} // namespace

float score(const Anomaly anomaly) noexcept {
  return anomaly_scores.find(anomaly)->second;
}

} // namespace TI4Cartographer
