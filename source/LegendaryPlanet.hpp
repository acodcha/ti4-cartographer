#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class LegendaryPlanet : uint8_t {
  HopesEnd,
  Mallice,
  Mirage,
  Primor,
  ThundersEdge,
  Faunus,
  Garbozia,
  Emelpar,
  Tempesta,
  MecatolRex,
  Industrex,
  Styx,
};

template <>
const std::unordered_map<LegendaryPlanet, std::string> labels<LegendaryPlanet>{
    {LegendaryPlanet::HopesEnd,     "Hope's End"    },
    {LegendaryPlanet::Mallice,      "Mallice"       },
    {LegendaryPlanet::Mirage,       "Mirage"        },
    {LegendaryPlanet::Primor,       "Primor"        },
    {LegendaryPlanet::ThundersEdge, "Thunder's Edge"},
    {LegendaryPlanet::Faunus,       "Faunus"        },
    {LegendaryPlanet::Garbozia,     "Garbozia"      },
    {LegendaryPlanet::Emelpar,      "Emelpar"       },
    {LegendaryPlanet::Tempesta,     "Tempesta"      },
    {LegendaryPlanet::MecatolRex,   "Mecatol Rex"   },
    {LegendaryPlanet::Industrex,    "Industrex"     },
    {LegendaryPlanet::Styx,         "Styx"          },
};

template <>
const std::unordered_map<std::string, LegendaryPlanet>
    spellings<LegendaryPlanet>{
        {"hopesend",     LegendaryPlanet::HopesEnd    },
        {"mallice",      LegendaryPlanet::Mallice     },
        {"mirage",       LegendaryPlanet::Mirage      },
        {"primor",       LegendaryPlanet::Primor      },
        {"thundersedge", LegendaryPlanet::ThundersEdge},
        {"faunus",       LegendaryPlanet::Faunus      },
        {"garbozia",     LegendaryPlanet::Garbozia    },
        {"emelpar",      LegendaryPlanet::Emelpar     },
        {"tempesta",     LegendaryPlanet::Tempesta    },
        {"mecatolrex",   LegendaryPlanet::MecatolRex  },
        {"industrex",    LegendaryPlanet::Industrex   },
        {"styx",         LegendaryPlanet::Styx        },
};

}  // namespace TI4Cartographer
