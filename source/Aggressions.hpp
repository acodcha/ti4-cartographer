#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Aggression : uint8_t {
  Low,
  Medium,
  High
};

template <> const std::unordered_map<Aggression, std::string> labels<Aggression>{
  {Aggression::Low, "Low"},
  {Aggression::Medium, "Medium"},
  {Aggression::High, "High"}
};

template <> const std::unordered_map<std::string, Aggression> spellings<Aggression>{
  {"low", Aggression::Low},
  {"medium", Aggression::Medium},
  {"high", Aggression::High}
};

} // namespace TI4Cartographer
