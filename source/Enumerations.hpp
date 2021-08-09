#pragma once

#include "String.hpp"

namespace TI4MapGenerator {

template <typename Type> const std::map<Type, std::string> labels;

template <typename Type> std::string label(const Type type) noexcept {
  const typename std::map<Type, std::string>::const_iterator found{labels<Type>.find(type)};
  if (found != labels<Type>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> const std::unordered_map<std::string, Enumeration> spellings;

template <typename Enumeration> std::optional<Enumeration> type(const std::string& spelling) noexcept {
  const std::string new_spelling{lowercase(remove_non_alphanumeric_characters(spelling))};
  const typename std::unordered_map<std::string, Enumeration>::const_iterator enumeration{spellings<Enumeration>.find(new_spelling)};
  if (enumeration != spellings<Enumeration>.cend()) {
    return {enumeration->second};
  } else {
    const std::optional<Enumeration> no_data;
    return no_data;
  }
}

enum class GameVersion : uint8_t {
  BaseGame,
  ProphecyOfKingsExpansion
};

template <> const std::map<GameVersion, std::string> labels<GameVersion>{
  {GameVersion::BaseGame, "Base Game"},
  {GameVersion::ProphecyOfKingsExpansion, "Prophecy of Kings Expansion"}
};

template <> const std::unordered_map<std::string, GameVersion> spellings<GameVersion>{
  {"basegame", GameVersion::BaseGame},
  {"base", GameVersion::BaseGame},
  {"prophecyofkingsexpansion", GameVersion::ProphecyOfKingsExpansion},
  {"prophecyofkings", GameVersion::ProphecyOfKingsExpansion},
  {"expansion", GameVersion::ProphecyOfKingsExpansion},
  {"pok", GameVersion::ProphecyOfKingsExpansion}
};

enum class MapLayout : uint8_t {
  Standard
};

template <> const std::map<MapLayout, std::string> labels<MapLayout>{
  {MapLayout::Standard, "Standard"}
};

template <> const std::unordered_map<std::string, MapLayout> spellings<MapLayout>{
  {"standard", MapLayout::Standard}
};

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

template <> const std::unordered_map<std::string, PlanetTrait> spellings<PlanetTrait>{
  {"cultural", PlanetTrait::Cultural},
  {"hazardous", PlanetTrait::Hazardous},
  {"industrial", PlanetTrait::Industrial}
};

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

enum class LegendaryPlanetType : uint8_t {
  HopesEnd,
  Mallice,
  Mirage,
  Primor
};

template <> const std::map<LegendaryPlanetType, std::string> labels<LegendaryPlanetType>{
  {LegendaryPlanetType::HopesEnd, "HopesEnd"},
  {LegendaryPlanetType::Mallice, "Mallice"},
  {LegendaryPlanetType::Mirage, "Mirage"},
  {LegendaryPlanetType::Primor, "Primor"}
};

template <> const std::unordered_map<std::string, LegendaryPlanetType> spellings<LegendaryPlanetType>{
  {"hopesend", LegendaryPlanetType::HopesEnd},
  {"mallice", LegendaryPlanetType::Mallice},
  {"mirage", LegendaryPlanetType::Mirage},
  {"primor", LegendaryPlanetType::Primor}
};

} // namespace TI4MapGenerator
