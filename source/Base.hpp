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

constexpr const uint64_t DefaultMaximumNumberOfAttempts{10};

constexpr const float InitialScoreImbalanceRatioTolerance{0.1};

namespace Score {

// If you have Antimass Deflectors researched, this is effectively an empty system.
// If you do not, this is worse because it prevents movement and therefore reduces your options. Generally bad.
// The Clan of Saar strongly prefers these due to their faction technology.
constexpr const float AsteroidField{-0.75};

// Gives extra movement and therefore extra options, but destroys 30% of your ships. Situationally useful, but dangerous.
constexpr const float GravityRift{-0.25};

// Better defense, but greatly impairs movement. Generally bad.
// The Empyrean strongly prefers these due to their faction ability.
constexpr const float Nebula{-0.5};

// Prevents movement and therefore reduces your options. Generally bad.
// The Embers of Muaat strongly prefer these due to their faction ability and technology.
constexpr const float Supernova{-1.0};

// Wormholes are generally beneficial because they provide additional movement options and lead to the Wormhole Nexus.
constexpr const float Wormhole{0.5};

}

} // namespace TI4Cartographer
