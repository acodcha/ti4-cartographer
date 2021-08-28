#pragma once

#include "DistanceFromPlayerHome.hpp"
#include "Layouts.hpp"
#include "Pathway.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief All the tiles on the board.
template <Layout layout> const std::set<Tile> Tiles;

// TODO: Everything below this point should be deprecated once ready.

uint8_t number_of_in_slice_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_in_a_slice() && tile.is_planetary_anomaly_wormhole_or_empty()) {
      ++number;
    }
  }
  return number;
}

uint8_t number_of_equidistant_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_equidistant() && tile.is_planetary_anomaly_wormhole_or_empty()) {
      ++number;
    }
  }
  return number;
}

template <Layout layout> const std::map<Player, std::set<Pathway>> PlayerPathwaysToMecatolRex;

template <Layout layout> const std::map<Player, std::set<Position>> PlayerForwardSpaceDockPreferredPositions;

template <Layout layout> const std::map<Player, std::set<Position>> PlayerForwardSpaceDockAlternatePositions;

template <Layout layout> const std::map<Player, std::set<Position>> PlayerLateralStarboardPositions;

template <Layout layout> const std::map<Player, std::set<Position>> PlayerLateralPortPositions;

} // namespace TI4Cartographer
