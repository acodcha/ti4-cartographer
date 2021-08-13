#pragma once

#include "Base.hpp"

namespace ti4cartographer {

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

} // namespace ti4cartographer
