#pragma once

#include "Include.hpp"

namespace TI4Cartographer {

/// \brief Make all characters in a string lowercase.
std::string lowercase(const std::string& text) noexcept {
  std::string new_text{text};
  std::transform(new_text.begin(), new_text.end(), new_text.begin(),
                 [](const char character) -> char {
                   return std::tolower(character);
                 });
  return new_text;
}

/// \brief Remove all whitespace from a string.
std::string remove_whitespace(const std::string& text) noexcept {
  std::string new_text{text};
  new_text.erase(
      remove_if(new_text.begin(), new_text.end(), ::isspace), new_text.end());
  return new_text;
}

/// \brief Remove all non-alphanumeric characters from a string.
std::string remove_non_alphanumeric_characters(
    const std::string& text) noexcept {
  std::string new_text;
  for (const char character : text) {
    if (::isalnum(character)) {
      new_text += character;
    }
  }
  return new_text;
}

/// \brief Remove all occurrences of a specific character from a string.
std::string remove_character(
    const std::string& text, const char character_to_remove) noexcept {
  std::string new_text;
  for (const char character : text) {
    if (character != character_to_remove) {
      new_text += character;
    }
  }
  return new_text;
}

/// \brief Replace each occurrence of a character with another character.
std::string replace_character(const std::string& text, const char original,
                              const char replacement) noexcept {
  std::string new_text{text};
  std::transform(new_text.begin(), new_text.end(), new_text.begin(),
                 [original, replacement](const char character) -> char {
                   if (character == original) {
                     return replacement;
                   }
                   return character;
                 });
  return new_text;
}

/// \brief Split a string into words using whitespace as a delimiter.
std::vector<std::string> split_by_whitespace(const std::string& text) noexcept {
  std::istringstream stream{text};
  std::vector<std::string> words{std::istream_iterator<std::string>{stream},
                                 std::istream_iterator<std::string>{}};
  return words;
}

/// \brief Pad a string to a given length using trailing spaces. If the string
/// is already longer than the given length, nothing is changed.
std::string pad_to_length(
    const std::string& text, const uint64_t length) noexcept {
  std::string new_text{text};
  if (length > new_text.size()) {
    new_text.append(length - new_text.size(), ' ');
  }
  return new_text;
}

/// \brief Convert a string to snake_case.
std::string snake_case(const std::string& text) noexcept {
  return {lowercase(replace_character(text, ' ', '_'))};
}

/// \brief Print a real number to a given precision.
std::string real_number_to_string(
    const float value, const int8_t precision = 2) noexcept {
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(precision) << value;
  return stream.str();
}

/// \brief Print a score.
std::string score_to_string(const float value) noexcept {
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2);
  if (value >= 0) {
    stream << "+";
  } else {
    stream << "-";
  }
  if (value < 10) {
    stream << "0";
  }
  stream << std::abs(value);
  return stream.str();
}

/// \brief Print a score imbalance.
std::string score_imbalance_ratio_to_string(const float value) noexcept {
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2);
  stream << value * 100.0 << " %";
  return stream.str();
}

template <class Type>
std::string print_vector(const std::vector<Type>& data) noexcept {
  std::string text;
  for (const Type& element : data) {
    if (!text.empty()) {
      text += ", ";
    }
    text += element.print();
  }
  return text;
}

template <class Type>
std::string print_set(const std::set<Type>& data) noexcept {
  std::string text;
  for (const Type& element : data) {
    if (!text.empty()) {
      text += ", ";
    }
    text += element.print();
  }
  return text;
}

template <class Type>
std::string print_unordered_set(const std::unordered_set<Type>& data) noexcept {
  std::string text;
  for (const Type& element : data) {
    if (!text.empty()) {
      text += ", ";
    }
    text += element.print();
  }
  return text;
}

}  // namespace TI4Cartographer
