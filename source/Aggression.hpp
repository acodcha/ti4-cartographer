#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Aggression : uint8_t { Low, Moderate, High };

template<> const std::unordered_map<Aggression, std::string> labels<Aggression>{
    {Aggression::Low,      "Low"     },
    {Aggression::Moderate, "Moderate"},
    {Aggression::High,     "High"    },
};

template<>
const std::unordered_map<std::string, Aggression> spellings<Aggression>{
    {"low",      Aggression::Low     },
    {"moderate", Aggression::Moderate},
    {"high",     Aggression::High    },
};

}  // namespace TI4Cartographer
