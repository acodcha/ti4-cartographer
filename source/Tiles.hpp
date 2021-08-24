#pragma once

#include "Layouts.hpp"
#include "Pathway.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief All the tiles on the board.
template <Layout layout> const std::set<Tile> Tiles;

uint8_t number_of_in_slice_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_in_a_slice() && tile.is_planetary_anomaly_wormhole_empty()) {
      ++number;
    }
  }
  return number;
}

uint8_t number_of_equidistant_systems(const std::set<Tile>& tiles) noexcept {
  uint8_t number{0};
  for (const Tile& tile : tiles) {
    if (tile.is_equidistant() && tile.is_planetary_anomaly_wormhole_empty()) {
      ++number;
    }
  }
  return number;
}

/// \brief Each player has one or more pathways to Mecatol Rex.
template <Layout layout> const std::map<uint8_t, std::set<Pathway>> PlayerPathwaysToMecatolRex;

template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockPreferredPositions;

template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockAlternatePositions;

/// \brief Each player has one or more tile positions that are 1 lateral to starboard of his/her home system.
template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerLateralStarboardPositions;

/// \brief Each player has one or more tile positions that are 1 lateral to port of his/her home system.
template <Layout layout> const std::map<uint8_t, std::set<Position>> PlayerLateralPortPositions;

} // namespace TI4Cartographer
