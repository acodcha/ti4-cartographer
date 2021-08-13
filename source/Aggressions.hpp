#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class Aggression : uint8_t {
  VeryLow,
  Low,
  Medium,
  High,
  VeryHigh
};

template <> const std::map<Aggression, std::string> labels<Aggression>{
  {Aggression::VeryLow, "Very Low"},
  {Aggression::Low, "Low"},
  {Aggression::Medium, "Medium"},
  {Aggression::High, "High"},
  {Aggression::VeryHigh, "Very High"}
};

template <> const std::unordered_map<std::string, Aggression> spellings<Aggression>{
  {"verylow", Aggression::VeryLow},
  {"low", Aggression::Low},
  {"medium", Aggression::Medium},
  {"high", Aggression::High},
  {"veryhigh", Aggression::VeryHigh}
};

} // namespace ti4cartographer
