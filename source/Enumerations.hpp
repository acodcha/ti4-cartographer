#pragma once

#include "String.hpp"

namespace TI4MapGenerator {

template <typename Type> const std::map<Type, std::string> labels;

template <typename Type> std::string label(const Type type) noexcept {
  const typename std::map<Type, std::string>::const_iterator found{labels<Type>.find(type)};
  if (found != labels<Type>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> const std::unordered_map<std::string, Enumeration> spellings;

template <typename Enumeration> std::optional<Enumeration> type(const std::string& spelling) noexcept {
  const std::string new_spelling{lowercase(remove_non_alphanumeric_characters(spelling))};
  const typename std::unordered_map<std::string, Enumeration>::const_iterator enumeration{spellings<Enumeration>.find(new_spelling)};
  if (enumeration != spellings<Enumeration>.cend()) {
    return {enumeration->second};
  } else {
    const std::optional<Enumeration> no_data;
    return no_data;
  }
}

enum class GameVersion : uint8_t {
  BaseGame,
  ProphecyOfKingsExpansion
};

template <> const std::map<GameVersion, std::string> labels<GameVersion>{
  {GameVersion::BaseGame, "Base Game"},
  {GameVersion::ProphecyOfKingsExpansion, "Prophecy of Kings Expansion"}
};

template <> const std::unordered_map<std::string, GameVersion> spellings<GameVersion>{
  {"basegame", GameVersion::BaseGame},
  {"base", GameVersion::BaseGame},
  {"prophecyofkingsexpansion", GameVersion::ProphecyOfKingsExpansion},
  {"prophecyofkings", GameVersion::ProphecyOfKingsExpansion},
  {"expansion", GameVersion::ProphecyOfKingsExpansion},
  {"pok", GameVersion::ProphecyOfKingsExpansion}
};

enum class MapLayout : uint8_t {
  Standard
};

template <> const std::map<MapLayout, std::string> labels<MapLayout>{
  {MapLayout::Standard, "Standard"}
};

template <> const std::unordered_map<std::string, MapLayout> spellings<MapLayout>{
  {"standard", MapLayout::Standard}
};

} // namespace TI4MapGenerator
