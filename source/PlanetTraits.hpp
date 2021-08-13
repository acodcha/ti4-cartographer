#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class PlanetTrait : uint8_t {
  Cultural,
  Industrial,
  Hazardous
};

template <> const std::map<PlanetTrait, std::string> labels<PlanetTrait>{
  {PlanetTrait::Cultural, "Cultural"},
  {PlanetTrait::Hazardous, "Hazardous"},
  {PlanetTrait::Industrial, "Industrial"},
};

template <> const std::map<PlanetTrait, std::string> abbreviations<PlanetTrait>{
  {PlanetTrait::Cultural, "Cul"},
  {PlanetTrait::Hazardous, "Haz"},
  {PlanetTrait::Industrial, "Ind"}
};

template <> const std::unordered_map<std::string, PlanetTrait> spellings<PlanetTrait>{
  {"cultural", PlanetTrait::Cultural},
  {"hazardous", PlanetTrait::Hazardous},
  {"industrial", PlanetTrait::Industrial}
};

} // namespace ti4cartographer
