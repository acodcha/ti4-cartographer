#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class GameVersion : uint8_t { BaseGame, ProphecyOfKingsExpansion };

template<>
const std::unordered_map<GameVersion, std::string> labels<GameVersion>{
  {GameVersion::BaseGame,                 "Base Game"                  },
  {GameVersion::ProphecyOfKingsExpansion, "Prophecy of Kings Expansion"}
};

template<>
const std::unordered_map<std::string, GameVersion> spellings<GameVersion>{
  {"basegame",                 GameVersion::BaseGame                },
  {"base",                     GameVersion::BaseGame                },
  {"prophecyofkingsexpansion", GameVersion::ProphecyOfKingsExpansion},
  {"prophecyofkings",          GameVersion::ProphecyOfKingsExpansion},
  {"expansion",                GameVersion::ProphecyOfKingsExpansion},
  {"pok",                      GameVersion::ProphecyOfKingsExpansion}
};

}  // namespace TI4Cartographer
