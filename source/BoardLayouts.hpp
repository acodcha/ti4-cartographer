#pragma once

#include "Base.hpp"

namespace ti4cartographer {

enum class BoardLayout : uint8_t {
  Players2,
  Players3,
  Players4Regular,
  Players4Large,
  Players5Regular,
  Players5Small,
  Players5Large,
  Players6,
  Players7Regular,
  Players7Large,
  Players8Regular,
  Players8Large
};

template <> const std::unordered_map<BoardLayout, std::string> labels<BoardLayout>{
  {BoardLayout::Players2, "2 Players"},
  {BoardLayout::Players3, "3 Players"},
  {BoardLayout::Players4Regular, "4 Players Regular"},
  {BoardLayout::Players4Large, "4 Players Large"},
  {BoardLayout::Players5Regular, "5 Players Regular"},
  {BoardLayout::Players5Small, "5 Players Small"},
  {BoardLayout::Players5Large, "5 Players Large"},
  {BoardLayout::Players6, "6 Players"},
  {BoardLayout::Players7Regular, "7 Players Regular"},
  {BoardLayout::Players7Large, "7 Players Large"},
  {BoardLayout::Players8Regular, "8 Players Regular"},
  {BoardLayout::Players8Large, "8 Players Large"}
};

template <> const std::unordered_map<std::string, BoardLayout> spellings<BoardLayout>{
  {"2players", BoardLayout::Players2},
  {"2playersregular", BoardLayout::Players2},
  {"3players", BoardLayout::Players3},
  {"3playersregular", BoardLayout::Players3},
  {"4playersregular", BoardLayout::Players4Regular},
  {"4playerslarge", BoardLayout::Players4Large},
  {"5playersregular", BoardLayout::Players5Regular},
  {"5playerssmall", BoardLayout::Players5Small},
  {"5playerslarge", BoardLayout::Players5Large},
  {"6players", BoardLayout::Players6},
  {"6playersregular", BoardLayout::Players6},
  {"7playersregular", BoardLayout::Players7Regular},
  {"7playerslarge", BoardLayout::Players7Large},
  {"8playersregular", BoardLayout::Players8Regular},
  {"8playerslarge", BoardLayout::Players8Large}
};

std::unordered_map<BoardLayout, uint8_t> board_layouts_to_number_of_players{
  {BoardLayout::Players2, 2},
  {BoardLayout::Players3, 3},
  {BoardLayout::Players4Regular, 4},
  {BoardLayout::Players4Large, 4},
  {BoardLayout::Players5Regular, 5},
  {BoardLayout::Players5Small, 5},
  {BoardLayout::Players5Large, 5},
  {BoardLayout::Players6, 6},
  {BoardLayout::Players7Regular, 7},
  {BoardLayout::Players7Large, 7},
  {BoardLayout::Players8Regular, 8},
  {BoardLayout::Players8Large, 8}
};

uint8_t number_of_players(const BoardLayout board_layout) noexcept {
  const std::unordered_map<BoardLayout, uint8_t>::const_iterator found{board_layouts_to_number_of_players.find(board_layout)};
  if (found != board_layouts_to_number_of_players.cend()) {
    return found->second;
  }
  return 0;
}

std::unordered_multimap<uint8_t, BoardLayout> number_of_players_to_board_layouts{
  {2, BoardLayout::Players2},
  {3, BoardLayout::Players3},
  {4, BoardLayout::Players4Regular},
  {4, BoardLayout::Players4Large},
  {5, BoardLayout::Players5Regular},
  {5, BoardLayout::Players5Small},
  {5, BoardLayout::Players5Large},
  {6, BoardLayout::Players6},
  {7, BoardLayout::Players7Regular},
  {7, BoardLayout::Players7Large},
  {8, BoardLayout::Players8Regular},
  {8, BoardLayout::Players8Large}
};

std::set<BoardLayout> board_layouts(const uint8_t number_of_players) {
  const std::pair<std::unordered_multimap<uint8_t, BoardLayout>::const_iterator, std::unordered_multimap<uint8_t, BoardLayout>::const_iterator> range{number_of_players_to_board_layouts.equal_range(number_of_players)};
  std::set<BoardLayout> results;
  for (std::unordered_multimap<uint8_t, BoardLayout>::const_iterator element = range.first; element != range.second; ++element) {
    results.insert(element->second);
  }
  return results;
}

} // namespace ti4cartographer
