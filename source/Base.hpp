#pragma once

#include "Enumerations.hpp"

namespace ti4cartographer {

const std::string CompilationDateAndTime{std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Separator{"=================================================="};

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

constexpr const uint64_t DefaultNumberOfIterations{100};

} // namespace ti4cartographer
