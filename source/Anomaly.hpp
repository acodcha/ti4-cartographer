#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Anomaly : uint8_t {
  AsteroidField,
  GravityRift,
  Nebula,
  Supernova,
};

template <>
const std::unordered_map<Anomaly, std::string> labels<Anomaly>{
    {Anomaly::AsteroidField, "Asteroid Field"},
    {Anomaly::GravityRift,   "Gravity Rift"  },
    {Anomaly::Nebula,        "Nebula"        },
    {Anomaly::Supernova,     "Supernova"     },
};

template <>
const std::unordered_map<std::string, Anomaly> spellings<Anomaly>{
    {"asteroidfield", Anomaly::AsteroidField},
    {"gravityrift",   Anomaly::GravityRift  },
    {"nebula",        Anomaly::Nebula       },
    {"supernova",     Anomaly::Supernova    },
};

namespace {

// Asteroid Field: If you have Antimass Deflectors researched, this is
// effectively an empty system; if you do not, this is worse because it prevents
// movement and therefore reduces your options. Therefore, this type of anomaly
// is generally undesirable, except for the Clan of Saar which strongly prefers
// this anomaly due to its faction technology.
//
// Gravity Rift: Gives extra movement and therefore extra options, but destroys
// 30% of your ships. Situationally useful, but dangerous.
//
// Nebula: Better defense, but greatly impairs movement, so generally
// undesirable. However, the Empyrean strongly prefers this anomaly due to its
// faction ability.
//
// Supernova: Prevents movement and therefore reduces your options, so generally
// undesirable. However, the Embers of Muaat strongly prefers this anomaly due
// to its faction ability and technology.
const std::map<Anomaly, float> anomaly_scores{
    {Anomaly::AsteroidField, -0.75f},
    {Anomaly::GravityRift,   -0.25f},
    {Anomaly::Nebula,        -0.5f },
    {Anomaly::Supernova,     -1.0f },
};

}  // namespace

float score(const Anomaly anomaly) noexcept {
  return anomaly_scores.find(anomaly)->second;
}

}  // namespace TI4Cartographer
