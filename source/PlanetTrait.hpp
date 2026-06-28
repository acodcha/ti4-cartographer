#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class PlanetTrait : uint8_t {
  Cultural,
  Industrial,
  Hazardous,
  SpaceStation,
  Relic,
};

template <>
const std::unordered_map<PlanetTrait, std::string> labels<PlanetTrait>{
    {PlanetTrait::Cultural,     "Cultural"     },
    {PlanetTrait::Hazardous,    "Hazardous"    },
    {PlanetTrait::Industrial,   "Industrial"   },
    {PlanetTrait::SpaceStation, "Space Station"},
    {PlanetTrait::Relic,        "Relic"        },
};

template <>
const std::unordered_map<PlanetTrait, std::string> abbreviations<PlanetTrait>{
    {PlanetTrait::Cultural,     "C"},
    {PlanetTrait::Hazardous,    "H"},
    {PlanetTrait::Industrial,   "I"},
    {PlanetTrait::SpaceStation, "S"},
    {PlanetTrait::Relic,        "R"},
};

template <>
const std::unordered_map<std::string, PlanetTrait> spellings<PlanetTrait>{
    {"cultural",     PlanetTrait::Cultural    },
    {"hazardous",    PlanetTrait::Hazardous   },
    {"industrial",   PlanetTrait::Industrial  },
    {"spacestation", PlanetTrait::SpaceStation},
    {"relic",        PlanetTrait::Relic       },
};

}  // namespace TI4Cartographer
