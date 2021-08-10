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

enum class BoardLayout : uint8_t {
  Standard
};

template <> const std::map<BoardLayout, std::string> labels<BoardLayout>{
  {BoardLayout::Standard, "Standard"}
};

template <> const std::unordered_map<std::string, BoardLayout> spellings<BoardLayout>{
  {"standard", BoardLayout::Standard}
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

enum class SystemCategory : uint8_t {
  Planetary,
  AnomalyWormholeEmpty,
  Home,
  MecatolRex,
  WormholeNexus,
  CreussGate
};

template <> const std::map<SystemCategory, std::string> labels<SystemCategory>{
  {SystemCategory::Planetary, "Planetary System"},
  {SystemCategory::AnomalyWormholeEmpty, "Anomaly/Wormhole/Empty System"},
  {SystemCategory::Home, "Home System"},
  {SystemCategory::MecatolRex, "Mecatol Rex System"},
  {SystemCategory::WormholeNexus, "Wormhole Nexus System"},
  {SystemCategory::CreussGate, "Creuss Gate System"}
};

template <> const std::unordered_map<std::string, SystemCategory> spellings<SystemCategory>{
  {"planetary", SystemCategory::Planetary},
  {"planetarysystem", SystemCategory::Planetary},
  {"anomalywormholeempty", SystemCategory::AnomalyWormholeEmpty},
  {"anomalywormholeemptysystem", SystemCategory::AnomalyWormholeEmpty},
  {"home", SystemCategory::Home},
  {"homesystem", SystemCategory::Home},
  {"mecatolrex", SystemCategory::MecatolRex},
  {"mecatolrexsystem", SystemCategory::MecatolRex},
  {"wormholenexus", SystemCategory::WormholeNexus},
  {"wormholenexussystem", SystemCategory::WormholeNexus},
  {"creussgate", SystemCategory::CreussGate},
  {"creussgatesystem", SystemCategory::CreussGate}
};

enum class Anomaly : uint8_t {
  AsteroidField,
  GravityRift,
  Nebula,
  Supernova
};

template <> const std::map<Anomaly, std::string> labels<Anomaly>{
  {Anomaly::AsteroidField, "Asteroid Field"},
  {Anomaly::GravityRift, "Gravity Rift"},
  {Anomaly::Nebula, "Nebula"},
  {Anomaly::Supernova, "Supernova"}
};

template <> const std::unordered_map<std::string, Anomaly> spellings<Anomaly>{
  {"asteroidfield", Anomaly::AsteroidField},
  {"gravityrift", Anomaly::GravityRift},
  {"nebula", Anomaly::Nebula},
  {"supernova", Anomaly::Supernova}
};

enum class Wormhole : uint8_t {
  Alpha,
  Beta,
  Gamma,
  Delta
};

template <> const std::map<Wormhole, std::string> labels<Wormhole>{
  {Wormhole::Alpha, "Alpha Wormhole"},
  {Wormhole::Beta, "Beta Wormhole"},
  {Wormhole::Gamma, "Gamma Wormhole"},
  {Wormhole::Delta, "Delta Wormhole"}
};

template <> const std::unordered_map<std::string, Wormhole> spellings<Wormhole>{
  {"alpha", Wormhole::Alpha},
  {"alphawormhole", Wormhole::Alpha},
  {"beta", Wormhole::Beta},
  {"betawormhole", Wormhole::Beta},
  {"gamma", Wormhole::Gamma},
  {"gammawormhole", Wormhole::Gamma},
  {"delta", Wormhole::Delta},
  {"deltawormhole", Wormhole::Delta}
};

enum class SystemPlacementType : uint8_t {
  Equidistant,
  ForwardFar,
  ForwardNear,
  LateralClockwise,
  LateralCounterClockwise
};

template <> const std::map<SystemPlacementType, std::string> labels<SystemPlacementType>{
  {SystemPlacementType::Equidistant, "Equidistant"},
  {SystemPlacementType::ForwardFar, "Forward Far"},
  {SystemPlacementType::ForwardNear, "Forward Near"},
  {SystemPlacementType::LateralClockwise, "Lateral Clockwise"},
  {SystemPlacementType::LateralCounterClockwise, "Lateral Counter-Clockwise"}
};

template <> const std::unordered_map<std::string, SystemPlacementType> spellings<SystemPlacementType>{
  {"equidistant", SystemPlacementType::Equidistant},
  {"forwardfar", SystemPlacementType::ForwardFar},
  {"forwardnear", SystemPlacementType::ForwardNear},
  {"lateralclockwise", SystemPlacementType::LateralClockwise},
  {"lateralcounterclockwise", SystemPlacementType::LateralCounterClockwise}
};

} // namespace TI4MapGenerator
