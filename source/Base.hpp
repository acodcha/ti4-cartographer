#pragma once

#include "Enumerations.hpp"

namespace TI4MapGenerator {

/// \brief Namespace containing information about the program and its compilation.
namespace Program {

const std::string Title{"TI4 Map Generator"};

const std::string CompilationDateAndTime{std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Description{"Generates randomized balanced maps for Twilight Imperium 4th Edition games."};

} // namespace Program

/// \brief Print a general-purpose message to the console.
inline void message(const std::string& text) noexcept {
  std::cout << text << std::endl;
}

/// \brief Print a warning to the console.
inline void warning(const std::string& text) noexcept {
  std::cout << "Warning: " << text << std::endl;
}

/// \brief Throw an exception.
inline void error(const std::string &text) {
  throw std::runtime_error(text);
}

std::random_device RandomDevice;

std::default_random_engine RandomEngine(RandomDevice());

} // namespace TI4MapGenerator
