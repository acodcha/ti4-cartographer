#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class LegendaryPlanet : uint8_t { HopesEnd, Mallice, Mirage, Primor };

template<>
const std::unordered_map<LegendaryPlanet, std::string> labels<LegendaryPlanet>{
  {LegendaryPlanet::HopesEnd, "Hope's End"},
  {LegendaryPlanet::Mallice,  "Mallice"   },
  {LegendaryPlanet::Mirage,   "Mirage"    },
  {LegendaryPlanet::Primor,   "Primor"    },
};

template<> const std::unordered_map<std::string, LegendaryPlanet>
  spellings<LegendaryPlanet>{
    {"hopesend", LegendaryPlanet::HopesEnd},
    {"mallice",  LegendaryPlanet::Mallice },
    {"mirage",   LegendaryPlanet::Mirage  },
    {"primor",   LegendaryPlanet::Primor  },
};

}  // namespace TI4Cartographer
