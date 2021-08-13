#pragma once

#include "Base.hpp"

namespace ti4cartographer {

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

} // namespace ti4cartographer
