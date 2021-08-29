#pragma once

#include "Tiles6Players.hpp"

namespace TI4Cartographer {

const std::set<Tile>& tiles(const Layout layout) noexcept {
  switch (layout) {
    case Layout::Players2:
      return Tiles<Layout::Players2>;
      break;
    case Layout::Players3Regular:
      return Tiles<Layout::Players3Regular>;
      break;
    case Layout::Players3Small:
      return Tiles<Layout::Players3Small>;
      break;
    case Layout::Players3Large:
      return Tiles<Layout::Players3Large>;
      break;
    case Layout::Players4Regular:
      return Tiles<Layout::Players4Regular>;
      break;
    case Layout::Players4Large:
      return Tiles<Layout::Players4Large>;
      break;
    case Layout::Players5Regular:
      return Tiles<Layout::Players5Regular>;
      break;
    case Layout::Players5Small:
      return Tiles<Layout::Players5Small>;
      break;
    case Layout::Players5Large:
      return Tiles<Layout::Players5Large>;
      break;
    case Layout::Players6:
      return Tiles<Layout::Players6>;
      break;
    case Layout::Players7Regular:
      return Tiles<Layout::Players7Regular>;
      break;
    case Layout::Players7Large:
      return Tiles<Layout::Players7Large>;
      break;
    case Layout::Players8Regular:
      return Tiles<Layout::Players8Regular>;
      break;
    case Layout::Players8Large:
      return Tiles<Layout::Players8Large>;
      break;
  }
}


const std::map<Player, std::set<Pathway>>& players_pathways_to_mecatol_rex(const Layout layout) noexcept {
  switch (layout) {
    case Layout::Players2:
      return PlayerPathwaysToMecatolRex<Layout::Players2>;
      break;
    case Layout::Players3Regular:
      return PlayerPathwaysToMecatolRex<Layout::Players3Regular>;
      break;
    case Layout::Players3Small:
      return PlayerPathwaysToMecatolRex<Layout::Players3Small>;
      break;
    case Layout::Players3Large:
      return PlayerPathwaysToMecatolRex<Layout::Players3Large>;
      break;
    case Layout::Players4Regular:
      return PlayerPathwaysToMecatolRex<Layout::Players4Regular>;
      break;
    case Layout::Players4Large:
      return PlayerPathwaysToMecatolRex<Layout::Players4Large>;
      break;
    case Layout::Players5Regular:
      return PlayerPathwaysToMecatolRex<Layout::Players5Regular>;
      break;
    case Layout::Players5Small:
      return PlayerPathwaysToMecatolRex<Layout::Players5Small>;
      break;
    case Layout::Players5Large:
      return PlayerPathwaysToMecatolRex<Layout::Players5Large>;
      break;
    case Layout::Players6:
      return PlayerPathwaysToMecatolRex<Layout::Players6>;
      break;
    case Layout::Players7Regular:
      return PlayerPathwaysToMecatolRex<Layout::Players7Regular>;
      break;
    case Layout::Players7Large:
      return PlayerPathwaysToMecatolRex<Layout::Players7Large>;
      break;
    case Layout::Players8Regular:
      return PlayerPathwaysToMecatolRex<Layout::Players8Regular>;
      break;
    case Layout::Players8Large:
      return PlayerPathwaysToMecatolRex<Layout::Players8Large>;
      break;
  }
}


const std::map<Player, std::set<Position>>& players_space_dock_preferred_positions(const Layout layout) noexcept {
  switch (layout) {
    case Layout::Players2:
      return PlayerSpaceDockPreferredPositions<Layout::Players2>;
      break;
    case Layout::Players3Regular:
      return PlayerSpaceDockPreferredPositions<Layout::Players3Regular>;
      break;
    case Layout::Players3Small:
      return PlayerSpaceDockPreferredPositions<Layout::Players3Small>;
      break;
    case Layout::Players3Large:
      return PlayerSpaceDockPreferredPositions<Layout::Players3Large>;
      break;
    case Layout::Players4Regular:
      return PlayerSpaceDockPreferredPositions<Layout::Players4Regular>;
      break;
    case Layout::Players4Large:
      return PlayerSpaceDockPreferredPositions<Layout::Players4Large>;
      break;
    case Layout::Players5Regular:
      return PlayerSpaceDockPreferredPositions<Layout::Players5Regular>;
      break;
    case Layout::Players5Small:
      return PlayerSpaceDockPreferredPositions<Layout::Players5Small>;
      break;
    case Layout::Players5Large:
      return PlayerSpaceDockPreferredPositions<Layout::Players5Large>;
      break;
    case Layout::Players6:
      return PlayerSpaceDockPreferredPositions<Layout::Players6>;
      break;
    case Layout::Players7Regular:
      return PlayerSpaceDockPreferredPositions<Layout::Players7Regular>;
      break;
    case Layout::Players7Large:
      return PlayerSpaceDockPreferredPositions<Layout::Players7Large>;
      break;
    case Layout::Players8Regular:
      return PlayerSpaceDockPreferredPositions<Layout::Players8Regular>;
      break;
    case Layout::Players8Large:
      return PlayerSpaceDockPreferredPositions<Layout::Players8Large>;
      break;
  }
}


const std::map<Player, std::set<Position>>& players_space_dock_alternate_positions(const Layout layout) noexcept {
  switch (layout) {
    case Layout::Players2:
      return PlayerSpaceDockAlternatePositions<Layout::Players2>;
      break;
    case Layout::Players3Regular:
      return PlayerSpaceDockAlternatePositions<Layout::Players3Regular>;
      break;
    case Layout::Players3Small:
      return PlayerSpaceDockAlternatePositions<Layout::Players3Small>;
      break;
    case Layout::Players3Large:
      return PlayerSpaceDockAlternatePositions<Layout::Players3Large>;
      break;
    case Layout::Players4Regular:
      return PlayerSpaceDockAlternatePositions<Layout::Players4Regular>;
      break;
    case Layout::Players4Large:
      return PlayerSpaceDockAlternatePositions<Layout::Players4Large>;
      break;
    case Layout::Players5Regular:
      return PlayerSpaceDockAlternatePositions<Layout::Players5Regular>;
      break;
    case Layout::Players5Small:
      return PlayerSpaceDockAlternatePositions<Layout::Players5Small>;
      break;
    case Layout::Players5Large:
      return PlayerSpaceDockAlternatePositions<Layout::Players5Large>;
      break;
    case Layout::Players6:
      return PlayerSpaceDockAlternatePositions<Layout::Players6>;
      break;
    case Layout::Players7Regular:
      return PlayerSpaceDockAlternatePositions<Layout::Players7Regular>;
      break;
    case Layout::Players7Large:
      return PlayerSpaceDockAlternatePositions<Layout::Players7Large>;
      break;
    case Layout::Players8Regular:
      return PlayerSpaceDockAlternatePositions<Layout::Players8Regular>;
      break;
    case Layout::Players8Large:
      return PlayerSpaceDockAlternatePositions<Layout::Players8Large>;
      break;
  }
}


const std::map<Player, std::set<Position>>& players_lateral_positions(const Layout layout) noexcept {
  switch (layout) {
    case Layout::Players2:
      return PlayerLateralPositions<Layout::Players2>;
      break;
    case Layout::Players3Regular:
      return PlayerLateralPositions<Layout::Players3Regular>;
      break;
    case Layout::Players3Small:
      return PlayerLateralPositions<Layout::Players3Small>;
      break;
    case Layout::Players3Large:
      return PlayerLateralPositions<Layout::Players3Large>;
      break;
    case Layout::Players4Regular:
      return PlayerLateralPositions<Layout::Players4Regular>;
      break;
    case Layout::Players4Large:
      return PlayerLateralPositions<Layout::Players4Large>;
      break;
    case Layout::Players5Regular:
      return PlayerLateralPositions<Layout::Players5Regular>;
      break;
    case Layout::Players5Small:
      return PlayerLateralPositions<Layout::Players5Small>;
      break;
    case Layout::Players5Large:
      return PlayerLateralPositions<Layout::Players5Large>;
      break;
    case Layout::Players6:
      return PlayerLateralPositions<Layout::Players6>;
      break;
    case Layout::Players7Regular:
      return PlayerLateralPositions<Layout::Players7Regular>;
      break;
    case Layout::Players7Large:
      return PlayerLateralPositions<Layout::Players7Large>;
      break;
    case Layout::Players8Regular:
      return PlayerLateralPositions<Layout::Players8Regular>;
      break;
    case Layout::Players8Large:
      return PlayerLateralPositions<Layout::Players8Large>;
      break;
  }
}

} // namespace TI4Cartographer
