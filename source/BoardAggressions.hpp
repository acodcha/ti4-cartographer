#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class BoardAggression : uint8_t {
  VeryLow,
  Low,
  Medium,
  High,
  VeryHigh
};

template <> const std::unordered_map<BoardAggression, std::string> labels<BoardAggression>{
  {BoardAggression::VeryLow, "Very Low"},
  {BoardAggression::Low, "Low"},
  {BoardAggression::Medium, "Medium"},
  {BoardAggression::High, "High"},
  {BoardAggression::VeryHigh, "Very High"}
};

template <> const std::unordered_map<std::string, BoardAggression> spellings<BoardAggression>{
  {"verylow", BoardAggression::VeryLow},
  {"low", BoardAggression::Low},
  {"medium", BoardAggression::Medium},
  {"high", BoardAggression::High},
  {"veryhigh", BoardAggression::VeryHigh}
};

} // namespace ti4cartographer
