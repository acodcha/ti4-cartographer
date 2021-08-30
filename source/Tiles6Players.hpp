#pragma once

#include "TilesBase.hpp"

namespace TI4Cartographer {

template <> std::set<Tile> const Tiles<Layout::Players6>{
  {Position{0, 0}, {SystemCategory::MecatolRex}},
  {Position{1, 0}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 0}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 7}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 8}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 9}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 10}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 11}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 0}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player5},
  {Position{3, 1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 3}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player6},
  {Position{3, 4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 6}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player1},
  {Position{3, 7}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 8}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 9}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player2},
  {Position{3, 10}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 11}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 12}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player3},
  {Position{3, 13}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 14}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 15}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player4},
  {Position{3, 16}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 17}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}}
};

} // namespace TI4Cartographer
