#pragma once

#include "String.hpp"

namespace TI4Cartographer {

template <typename Enumeration> const std::unordered_map<Enumeration, std::string> labels;

template <typename Enumeration> std::string label(const Enumeration& type) noexcept {
  const typename std::unordered_map<Enumeration, std::string>::const_iterator found{labels<Enumeration>.find(type)};
  if (found != labels<Enumeration>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> std::string label(const std::optional<Enumeration>& type) noexcept {
  if (type.has_value()) {
    return label(type.value());
  } else {
    return {};
  }
}

template <typename Enumeration> const std::unordered_map<Enumeration, std::string> abbreviations;

template <typename Enumeration> std::string abbreviation(const Enumeration& type) noexcept {
  const typename std::unordered_map<Enumeration, std::string>::const_iterator found{abbreviations<Enumeration>.find(type)};
  if (found != abbreviations<Enumeration>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template <typename Enumeration> std::string abbreviation(const std::optional<Enumeration>& type) noexcept {
  if (type.has_value()) {
    return abbreviation(type.value());
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

} // namespace TI4Cartographer
