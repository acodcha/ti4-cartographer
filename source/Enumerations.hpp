#pragma once

#include "String.hpp"

namespace TI4MapGenerator {

template <typename Enumeration> const std::map<Enumeration, std::string> labels;

template <typename Enumeration> std::string label(const Enumeration& type) noexcept {
  const typename std::map<Enumeration, std::string>::const_iterator found{labels<Enumeration>.find(type)};
  if (found != labels<Enumeration>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> std::string label(const std::optional<Enumeration>& type) noexcept {
  if (type.has_value()) {
    return label(type.value());
  } else {
    return {};
  }
}

template <typename Enumeration> const std::map<Enumeration, std::string> abbreviations;

template <typename Enumeration> std::string abbreviation(const Enumeration& type) noexcept {
  const typename std::map<Enumeration, std::string>::const_iterator found{abbreviations<Enumeration>.find(type)};
  if (found != abbreviations<Enumeration>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> std::string abbreviation(const std::optional<Enumeration>& type) noexcept {
  if (type.has_value()) {
    return abbreviation(type.value());
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

enum class LegendaryPlanet : uint8_t {
  HopesEnd,
  Mallice,
  Mirage,
  Primor
};

template <> const std::map<LegendaryPlanet, std::string> labels<LegendaryPlanet>{
  {LegendaryPlanet::HopesEnd, "Hope's End"},
  {LegendaryPlanet::Mallice, "Mallice"},
  {LegendaryPlanet::Mirage, "Mirage"},
  {LegendaryPlanet::Primor, "Primor"}
};

template <> const std::unordered_map<std::string, LegendaryPlanet> spellings<LegendaryPlanet>{
  {"hopesend", LegendaryPlanet::HopesEnd},
  {"mallice", LegendaryPlanet::Mallice},
  {"mirage", LegendaryPlanet::Mirage},
  {"primor", LegendaryPlanet::Primor}
};

enum class AnomalyType : uint8_t {
  AsteroidField,
  GravityRift,
  Nebula,
  Supernova
};

template <> const std::map<AnomalyType, std::string> labels<AnomalyType>{
  {AnomalyType::AsteroidField, "Asteroid Field"},
  {AnomalyType::GravityRift, "Gravity Rift"},
  {AnomalyType::Nebula, "Nebula"},
  {AnomalyType::Supernova, "Supernova"}
};

template <> const std::unordered_map<std::string, AnomalyType> spellings<AnomalyType>{
  {"asteroidfield", AnomalyType::AsteroidField},
  {"gravityrift", AnomalyType::GravityRift},
  {"nebula", AnomalyType::Nebula},
  {"supernova", AnomalyType::Supernova}
};

enum class WormholeType : uint8_t {
  Alpha,
  Beta,
  Gamma,
  Delta
};

template <> const std::map<WormholeType, std::string> labels<WormholeType>{
  {WormholeType::Alpha, "Alpha Wormhole"},
  {WormholeType::Beta, "Beta Wormhole"},
  {WormholeType::Gamma, "Gamma Wormhole"},
  {WormholeType::Delta, "Delta Wormhole"}
};

template <> const std::unordered_map<std::string, WormholeType> spellings<WormholeType>{
  {"alpha", WormholeType::Alpha},
  {"alphawormhole", WormholeType::Alpha},
  {"beta", WormholeType::Beta},
  {"betawormhole", WormholeType::Beta},
  {"gamma", WormholeType::Gamma},
  {"gammawormhole", WormholeType::Gamma},
  {"delta", WormholeType::Delta},
  {"deltawormhole", WormholeType::Delta}
};

} // namespace TI4MapGenerator
