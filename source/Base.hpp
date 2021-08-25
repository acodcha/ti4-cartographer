#pragma once

#include "Communicator.hpp"

namespace TI4Cartographer {

const std::string ProgramName{"TI4 Cartographer"};

const std::string CompilationDateAndTime{std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Separator{"=================================================="};

const std::string MecatolRexSystemId{"18"};

std::random_device RandomDevice;

std::default_random_engine RandomEngine(RandomDevice());

constexpr const uint64_t DefaultMaximumNumberOfIterations{1000000};

constexpr const double ScoreImbalanceTolerance{3.0};

} // namespace TI4Cartographer
