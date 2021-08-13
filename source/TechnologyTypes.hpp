#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class TechnologyType : uint8_t {
  Propulsion,
  Biotic,
  Cybernetic,
  Warfare
};

template <> const std::map<TechnologyType, std::string> labels<TechnologyType>{
  {TechnologyType::Propulsion, "Propulsion"},
  {TechnologyType::Biotic, "Biotic"},
  {TechnologyType::Cybernetic, "Cybernetic"},
  {TechnologyType::Warfare, "Warfare"}
};

template <> const std::map<TechnologyType, std::string> abbreviations<TechnologyType>{
  {TechnologyType::Propulsion, "B"},
  {TechnologyType::Biotic, "G"},
  {TechnologyType::Cybernetic, "Y"},
  {TechnologyType::Warfare, "R"}
};

template <> const std::unordered_map<std::string, TechnologyType> spellings<TechnologyType>{
  {"propulsion", TechnologyType::Propulsion},
  {"blue", TechnologyType::Propulsion},
  {"biotic", TechnologyType::Biotic},
  {"green", TechnologyType::Biotic},
  {"cybernetic", TechnologyType::Cybernetic},
  {"yellow", TechnologyType::Cybernetic},
  {"warfare", TechnologyType::Warfare},
  {"red", TechnologyType::Warfare}
};

} // namespace ti4cartographer
