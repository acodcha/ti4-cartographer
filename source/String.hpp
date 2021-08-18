#pragma once

#include "Include.hpp"

namespace TI4Cartographer {

/// \brief Make each character in a string lowercase.
std::string lowercase(const std::string& text) noexcept {
  std::string new_text{text};
  std::transform(new_text.begin(), new_text.end(), new_text.begin(), [](const char character)->char{return std::tolower(character);});
  return new_text;
}

/// \brief Remove whitespace in a string.
std::string remove_whitespace(const std::string& text) noexcept {
  std::string new_text{text};
  new_text.erase(remove_if(new_text.begin(), new_text.end(), ::isspace), new_text.end());
  return new_text;
}

/// \brief Remove non-alphanumeric characters in a string.
std::string remove_non_alphanumeric_characters(const std::string& text) noexcept {
  std::string new_text;
  for (const char character : text) {
    if (::isalnum(character)) {
      new_text += character;
    }
  }
  return new_text;
}

/// \brief Replace each occurrence of a character with another character.
std::string replace_character(const std::string& text, const char original, const char replacement) noexcept {
  std::string new_text{text};
  std::transform(new_text.begin(), new_text.end(), new_text.begin(), [original, replacement](const char character)->char{
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
  std::vector<std::string> words{std::istream_iterator<std::string>{stream}, std::istream_iterator<std::string>{}};
  return words;
}

/// \brief Pad a string to a given length using trailing spaces. If the string is already longer than the given length, nothing is changed.
std::string pad_to_length(const std::string& text, const uint64_t length) noexcept {
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

/// \brief Print a score.
std::string score_to_string(const double value) noexcept {
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
std::string score_imbalance_to_string(const double value) noexcept {
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2);
  stream << value;
  return stream.str();
}

} // namespace TI4Cartographer
