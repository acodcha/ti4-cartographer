#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class SystemCategory : uint8_t {
  Planetary,
  AnomalyWormholeEmpty,
  Home,
  MecatolRex,
  WormholeNexus,
  CreussGate,
  CrimsonRebellionGate,
  Hyperlane,
  Fracture,
};

template <>
const std::unordered_map<SystemCategory, std::string> labels<SystemCategory>{
    {SystemCategory::Planetary,            "Planetary System"             },
    {SystemCategory::AnomalyWormholeEmpty, "Anomaly/Wormhole/Empty System"},
    {SystemCategory::Home,                 "Home System"                  },
    {SystemCategory::MecatolRex,           "Mecatol Rex System"           },
    {SystemCategory::WormholeNexus,        "Wormhole Nexus System"        },
    {SystemCategory::CreussGate,           "Creuss Gate System"           },
    {SystemCategory::CrimsonRebellionGate, "Crimson Rebellion Gate System"},
    {SystemCategory::Hyperlane,            "Hyperlane Tile"               },
    {SystemCategory::Fracture,             "Fracture"                     },
};

template <>
const std::unordered_map<std::string, SystemCategory> spellings<SystemCategory>{
    {"planetary",                  SystemCategory::Planetary           },
    {"planetarysystem",            SystemCategory::Planetary           },
    {"anomalywormholeempty",       SystemCategory::AnomalyWormholeEmpty},
    {"anomalywormholeemptysystem", SystemCategory::AnomalyWormholeEmpty},
    {"home",                       SystemCategory::Home                },
    {"homesystem",                 SystemCategory::Home                },
    {"mecatolrex",                 SystemCategory::MecatolRex          },
    {"mecatolrexsystem",           SystemCategory::MecatolRex          },
    {"wormholenexus",              SystemCategory::WormholeNexus       },
    {"wormholenexussystem",        SystemCategory::WormholeNexus       },
    {"creussgate",                 SystemCategory::CreussGate          },
    {"creussgatesystem",           SystemCategory::CreussGate          },
    {"crimsonrebelliongate",       SystemCategory::CrimsonRebellionGate},
    {"crimsonrebelliongatesystem", SystemCategory::CrimsonRebellionGate},
    {"hyperlane",                  SystemCategory::Hyperlane           },
    {"hyperlanetile",              SystemCategory::Hyperlane           },
    {"fracture",                   SystemCategory::Fracture            },
    {"fracturetile",               SystemCategory::Fracture            },
    {"fracturesystem",             SystemCategory::Fracture            },
};

}  // namespace TI4Cartographer
