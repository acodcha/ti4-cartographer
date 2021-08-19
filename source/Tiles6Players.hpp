#pragma once

#include "Tiles.hpp"

namespace TI4Cartographer {

template <> std::set<Tile> const Tiles<BoardLayout::Players6>{
  {Position{1, 0}, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 1}, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 2}, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 3}, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 4}, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 5}, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 0}, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 1}, {5, 6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 2}, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 3}, {1, 6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 4}, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 5}, {1, 2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 6}, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 7}, {2, 3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 8}, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 9}, {3, 4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 10}, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 11}, {4, 5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 0}, {5}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 1}, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 2}, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 3}, {6}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 4}, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 5}, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 6}, {1}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 7}, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 8}, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 9}, {2}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 10}, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 11}, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 12}, {3}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 13}, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 14}, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 15}, {4}, {SystemCategory::Home, SystemCategory::CreussGate}, "0"},
  {Position{3, 16}, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 17}, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}}
};

template <> const std::map<uint8_t, std::set<Pathway>> PlayerPathwaysToMecatolRex<BoardLayout::Players6>{
  {1, {{Pathway{{Position{2, 4}, Position{1, 2}}}}}},
  {2, {{Pathway{{Position{2, 6}, Position{1, 3}}}}}},
  {3, {{Pathway{{Position{2, 8}, Position{1, 4}}}}}},
  {4, {{Pathway{{Position{2, 10}, Position{1, 5}}}}}},
  {5, {{Pathway{{Position{2, 0}, Position{1, 0}}}}}},
  {6, {{Pathway{{Position{2, 2}, Position{1, 1}}}}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockPreferredPositions<BoardLayout::Players6>{
  {1, {Position{2, 4}}},
  {2, {Position{2, 6}}},
  {3, {Position{2, 8}}},
  {4, {Position{2, 10}}},
  {5, {Position{2, 0}}},
  {6, {Position{2, 2}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockAlternatePositions<BoardLayout::Players6>{
  {1, {Position{1, 2}}},
  {2, {Position{1, 3}}},
  {3, {Position{1, 4}}},
  {4, {Position{1, 5}}},
  {5, {Position{1, 0}}},
  {6, {Position{1, 1}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerLateralStarboardPositions<BoardLayout::Players6>{
  {1, {Position{3, 5}}},
  {2, {Position{3, 8}}},
  {3, {Position{3, 11}}},
  {4, {Position{3, 14}}},
  {5, {Position{3, 17}}},
  {6, {Position{3, 2}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerLateralPortPositions<BoardLayout::Players6>{
  {1, {Position{3, 7}}},
  {2, {Position{3, 10}}},
  {3, {Position{3, 13}}},
  {4, {Position{3, 16}}},
  {5, {Position{3, 1}}},
  {6, {Position{3, 4}}}
};

} // namespace TI4Cartographer
