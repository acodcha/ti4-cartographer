#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class BoardLayout : uint8_t {
  Regular,
  Large,
  Small
};

template <> const std::unordered_map<BoardLayout, std::string> labels<BoardLayout>{
  {BoardLayout::Regular, "Regular"},
  {BoardLayout::Large, "Large"},
  {BoardLayout::Small, "Small"}
};

template <> const std::unordered_map<std::string, BoardLayout> spellings<BoardLayout>{
  {"regular", BoardLayout::Regular},
  {"large", BoardLayout::Large},
  {"small", BoardLayout::Small}
};

} // namespace ti4cartographer
