#pragma once

#include "Tiles.hpp"

namespace TI4Cartographer {

template <> std::set<Tile> const Tiles<Layout::Players6>{
  {Position{0, 0}, 0, {}, {SystemCategory::MecatolRex}},
  {Position{1, 0}, 1, {Player::Player5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 1}, 1, {Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 2}, 1, {Player::Player1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 3}, 1, {Player::Player2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 4}, 1, {Player::Player3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 5}, 1, {Player::Player4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 0}, 2, {Player::Player5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 1}, 2, {Player::Player5, Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 2}, 2, {Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 3}, 2, {Player::Player1, Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 4}, 2, {Player::Player1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 5}, 2, {Player::Player1, Player::Player2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 6}, 2, {Player::Player2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 7}, 2, {Player::Player2, Player::Player3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 8}, 2, {Player::Player3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 9}, 2, {Player::Player3, Player::Player4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 10}, 2, {Player::Player4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 11}, 2, {Player::Player4, Player::Player5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 0}, 3, {Player::Player5}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player5},
  {Position{3, 1}, 3, {Player::Player5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 2}, 3, {Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 3}, 3, {Player::Player6}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player6},
  {Position{3, 4}, 3, {Player::Player6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 5}, 3, {Player::Player1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 6}, 3, {Player::Player1}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player1},
  {Position{3, 7}, 3, {Player::Player1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 8}, 3, {Player::Player2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 9}, 3, {Player::Player2}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player2},
  {Position{3, 10}, 3, {Player::Player2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 11}, 3, {Player::Player3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 12}, 3, {Player::Player3}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player3},
  {Position{3, 13}, 3, {Player::Player3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 14}, 3, {Player::Player4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 15}, 3, {Player::Player4}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0", Player::Player4},
  {Position{3, 16}, 3, {Player::Player4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 17}, 3, {Player::Player5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}}
};

template <> const std::map<Player, std::set<Pathway>> PlayerPathwaysToMecatolRex<Layout::Players6>{
  {Player::Player1, {{Pathway{{Position{2, 4}, Position{1, 2}}}}}},
  {Player::Player2, {{Pathway{{Position{2, 6}, Position{1, 3}}}}}},
  {Player::Player3, {{Pathway{{Position{2, 8}, Position{1, 4}}}}}},
  {Player::Player4, {{Pathway{{Position{2, 10}, Position{1, 5}}}}}},
  {Player::Player5, {{Pathway{{Position{2, 0}, Position{1, 0}}}}}},
  {Player::Player6, {{Pathway{{Position{2, 2}, Position{1, 1}}}}}}
};

template <> const std::map<Player, std::set<Position>> PlayerForwardSpaceDockPreferredPositions<Layout::Players6>{
  {Player::Player1, {Position{2, 4}}},
  {Player::Player2, {Position{2, 6}}},
  {Player::Player3, {Position{2, 8}}},
  {Player::Player4, {Position{2, 10}}},
  {Player::Player5, {Position{2, 0}}},
  {Player::Player6, {Position{2, 2}}}
};

template <> const std::map<Player, std::set<Position>> PlayerForwardSpaceDockAlternatePositions<Layout::Players6>{
  {Player::Player1, {Position{1, 2}}},
  {Player::Player2, {Position{1, 3}}},
  {Player::Player3, {Position{1, 4}}},
  {Player::Player4, {Position{1, 5}}},
  {Player::Player5, {Position{1, 0}}},
  {Player::Player6, {Position{1, 1}}}
};

template <> const std::map<Player, std::set<Position>> PlayerLateralStarboardPositions<Layout::Players6>{
  {Player::Player1, {Position{3, 5}}},
  {Player::Player2, {Position{3, 8}}},
  {Player::Player3, {Position{3, 11}}},
  {Player::Player4, {Position{3, 14}}},
  {Player::Player5, {Position{3, 17}}},
  {Player::Player6, {Position{3, 2}}}
};

template <> const std::map<Player, std::set<Position>> PlayerLateralPortPositions<Layout::Players6>{
  {Player::Player1, {Position{3, 7}}},
  {Player::Player2, {Position{3, 10}}},
  {Player::Player3, {Position{3, 13}}},
  {Player::Player4, {Position{3, 16}}},
  {Player::Player5, {Position{3, 1}}},
  {Player::Player6, {Position{3, 4}}}
};

} // namespace TI4Cartographer
