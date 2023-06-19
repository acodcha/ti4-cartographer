#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Wormhole : uint8_t {
  Alpha,
  Beta,
  Gamma,
  Delta,
};

template<> const std::unordered_map<Wormhole, std::string> labels<Wormhole>{
  {Wormhole::Alpha, "Alpha Wormhole"},
  {Wormhole::Beta,  "Beta Wormhole" },
  {Wormhole::Gamma, "Gamma Wormhole"},
  {Wormhole::Delta, "Delta Wormhole"},
};

template<> const std::unordered_map<std::string, Wormhole> spellings<Wormhole>{
  {"alpha",         Wormhole::Alpha},
  {"alphawormhole", Wormhole::Alpha},
  {"beta",          Wormhole::Beta },
  {"betawormhole",  Wormhole::Beta },
  {"gamma",         Wormhole::Gamma},
  {"gammawormhole", Wormhole::Gamma},
  {"delta",         Wormhole::Delta},
  {"deltawormhole", Wormhole::Delta},
};

// Wormholes are generally beneficial because they provide additional movement
// options and lead to the Wormhole Nexus.
constexpr const float WormholeScore{1.0f};

}  // namespace TI4Cartographer
