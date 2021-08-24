#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

/// \brief Utility for measuring runtime. Starts counting when constructed.
class Chronometre {

public:

  Chronometre() noexcept : start_(std::chrono::high_resolution_clock::now()) {}

  double value_seconds() const noexcept {
    const std::chrono::microseconds duration{std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_)};
    return duration.count() / 1000000.0;
  }

  std::string print() const noexcept {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value_seconds() << " s";
    return stream.str();
  }

protected:

  std::chrono::high_resolution_clock::time_point start_;

};

} // namespace TI4Cartographer
