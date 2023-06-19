#pragma once

#include "Communicator.hpp"

namespace TI4Cartographer {

const std::string ProgramName{"TI4 Cartographer"};

const std::string CompilationDateAndTime{
    std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Separator{
    "=================================================="};

std::random_device RandomDevice;

std::default_random_engine RandomEngine(RandomDevice());

}  // namespace TI4Cartographer
