#pragma once

#include "SystemCategories.hpp"

namespace TI4Cartographer {

enum class Layout : uint8_t {
  Players2,
  Players3Regular,
  Players3Small,
  Players3Large,
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

template <> const std::unordered_map<Layout, std::string> labels<Layout>{
  {Layout::Players2, "2 Players"},
  {Layout::Players3Regular, "3 Players Regular"},
  {Layout::Players3Small, "3 Players Small"},
  {Layout::Players3Large, "3 Players Large"},
  {Layout::Players4Regular, "4 Players Regular"},
  {Layout::Players4Large, "4 Players Large"},
  {Layout::Players5Regular, "5 Players Regular"},
  {Layout::Players5Small, "5 Players Small"},
  {Layout::Players5Large, "5 Players Large"},
  {Layout::Players6, "6 Players"},
  {Layout::Players7Regular, "7 Players Regular"},
  {Layout::Players7Large, "7 Players Large"},
  {Layout::Players8Regular, "8 Players Regular"},
  {Layout::Players8Large, "8 Players Large"}
};

template <> const std::unordered_map<std::string, Layout> spellings<Layout>{
  {"2players", Layout::Players2},
  {"2playersregular", Layout::Players2},
  {"3playersregular", Layout::Players3Regular},
  {"3playerssmall", Layout::Players3Small},
  {"3playerslarge", Layout::Players3Large},
  {"4playersregular", Layout::Players4Regular},
  {"4playerslarge", Layout::Players4Large},
  {"5playersregular", Layout::Players5Regular},
  {"5playerssmall", Layout::Players5Small},
  {"5playerslarge", Layout::Players5Large},
  {"6players", Layout::Players6},
  {"6playersregular", Layout::Players6},
  {"7playersregular", Layout::Players7Regular},
  {"7playerslarge", Layout::Players7Large},
  {"8playersregular", Layout::Players8Regular},
  {"8playerslarge", Layout::Players8Large}
};

std::unordered_map<Layout, uint8_t> layouts_to_number_of_players{
  {Layout::Players2, 2},
  {Layout::Players3Regular, 3},
  {Layout::Players3Small, 3},
  {Layout::Players3Large, 3},
  {Layout::Players4Regular, 4},
  {Layout::Players4Large, 4},
  {Layout::Players5Regular, 5},
  {Layout::Players5Small, 5},
  {Layout::Players5Large, 5},
  {Layout::Players6, 6},
  {Layout::Players7Regular, 7},
  {Layout::Players7Large, 7},
  {Layout::Players8Regular, 8},
  {Layout::Players8Large, 8}
};

uint8_t number_of_players(const Layout layout) noexcept {
  const std::unordered_map<Layout, uint8_t>::const_iterator found{layouts_to_number_of_players.find(layout)};
  if (found != layouts_to_number_of_players.cend()) {
    return found->second;
  }
  return 0;
}

std::unordered_multimap<uint8_t, Layout> number_of_players_to_layouts{
  {2, Layout::Players2},
  {3, Layout::Players3Regular},
  {3, Layout::Players3Small},
  {3, Layout::Players3Large},
  {4, Layout::Players4Regular},
  {4, Layout::Players4Large},
  {5, Layout::Players5Regular},
  {5, Layout::Players5Small},
  {5, Layout::Players5Large},
  {6, Layout::Players6},
  {7, Layout::Players7Regular},
  {7, Layout::Players7Large},
  {8, Layout::Players8Regular},
  {8, Layout::Players8Large}
};

std::set<Layout> layouts(const uint8_t number_of_players) {
  const std::pair<std::unordered_multimap<uint8_t, Layout>::const_iterator, std::unordered_multimap<uint8_t, Layout>::const_iterator> range{number_of_players_to_layouts.equal_range(number_of_players)};
  std::set<Layout> results;
  for (std::unordered_multimap<uint8_t, Layout>::const_iterator element = range.first; element != range.second; ++element) {
    results.insert(element->second);
  }
  return results;
}

std::unordered_map<SystemCategory, std::unordered_map<Layout, uint8_t>> const system_categories_to_layouts_to_number_of_systems_per_player{
  {SystemCategory::Planetary, {
    {Layout::Players2, 4},
    {Layout::Players3Regular, 3},
    {Layout::Players3Small, 3},
    {Layout::Players3Large, 4},
    {Layout::Players4Regular, 3},
    {Layout::Players4Large, 3},
    {Layout::Players5Regular, 3},
    {Layout::Players5Small, 3},
    {Layout::Players5Large, 3},
    {Layout::Players6, 3},
    {Layout::Players7Regular, 3},
    {Layout::Players7Large, 4},
    {Layout::Players8Regular, 3},
    {Layout::Players8Large, 4}
  }},
  {SystemCategory::AnomalyWormholeEmpty, {
    {Layout::Players2, 4},
    {Layout::Players3Regular, 2},
    {Layout::Players3Small, 2},
    {Layout::Players3Large, 4},
    {Layout::Players4Regular, 2},
    {Layout::Players4Large, 3},
    {Layout::Players5Regular, 2},
    {Layout::Players5Small, 2},
    {Layout::Players5Large, 3},
    {Layout::Players6, 2},
    {Layout::Players7Regular, 2},
    {Layout::Players7Large, 2},
    {Layout::Players8Regular, 2},
    {Layout::Players8Large, 2}
  }}
};

uint8_t number_of_systems_per_player(const SystemCategory system_category, const Layout layout) noexcept {
  const std::unordered_map<SystemCategory, std::unordered_map<Layout, uint8_t>>::const_iterator found_system_category{system_categories_to_layouts_to_number_of_systems_per_player.find(system_category)};
  if (found_system_category != system_categories_to_layouts_to_number_of_systems_per_player.cend()) {
    const std::unordered_map<Layout, uint8_t>::const_iterator found_layout{found_system_category->second.find(layout)};
    if (found_layout != found_system_category->second.cend()) {
      return found_layout->second;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

} // namespace TI4Cartographer
