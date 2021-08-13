#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class SystemCategory : uint8_t {
  Planetary,
  AnomalyWormholeEmpty,
  Home,
  MecatolRex,
  WormholeNexus,
  CreussGate
};

template <> const std::unordered_map<SystemCategory, std::string> labels<SystemCategory>{
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

} // namespace ti4cartographer
