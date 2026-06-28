#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class GameVersion : uint8_t {
  BaseGame,
  ProphecyOfKingsExpansion,
  ThundersEdgeExpansion,
  ProphecyOfKingsAndThundersEdgeExpansions,
};

template <>
const std::unordered_map<GameVersion, std::string> labels<GameVersion>{
    {GameVersion::BaseGame,                                 "Base Game"                  },
    {GameVersion::ProphecyOfKingsExpansion,                 "Prophecy of Kings expansion"},
    {GameVersion::ThundersEdgeExpansion,                    "Thunder's Edge expansion"   },
    {GameVersion::ProphecyOfKingsAndThundersEdgeExpansions,
     "Prophecy of Kings and Thunder's Edge expansions"                                   },
};

template <>
const std::unordered_map<std::string, GameVersion> spellings<GameVersion>{
    {"basegame",                 GameVersion::BaseGame                                },
    {"base",                     GameVersion::BaseGame                                },
    {"prophecyofkingsexpansion", GameVersion::ProphecyOfKingsExpansion                },
    {"prophecyofkings",          GameVersion::ProphecyOfKingsExpansion                },
    {"pok",                      GameVersion::ProphecyOfKingsExpansion                },
    {"thundersedgeexpansion",    GameVersion::ThundersEdgeExpansion                   },
    {"thundersedge",             GameVersion::ThundersEdgeExpansion                   },
    {"te",                       GameVersion::ThundersEdgeExpansion                   },
    {"all",                      GameVersion::ProphecyOfKingsAndThundersEdgeExpansions},
};

}  // namespace TI4Cartographer
