#pragma once

#include "Tiles.hpp"

namespace TI4Cartographer {

template <> std::set<Tile> const Tiles<Layout::Players6>{
  {Position{1, 0}, 1, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 1}, 1, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 2}, 1, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 3}, 1, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 4}, 1, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{1, 5}, 1, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 0}, 2, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 1}, 2, {5, 6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 2}, 2, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 3}, 2, {1, 6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 4}, 2, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 5}, 2, {1, 2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 6}, 2, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 7}, 2, {2, 3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 8}, 2, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 9}, 2, {3, 4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 10}, 2, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{2, 11}, 2, {4, 5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 0}, 3, {5}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 1}, 3, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 2}, 3, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 3}, 3, {6}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 4}, 3, {6}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 5}, 3, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 6}, 3, {1}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 7}, 3, {1}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 8}, 3, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 9}, 3, {2}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 10}, 3, {2}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 11}, 3, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 12}, 3, {3}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 13}, 3, {3}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 14}, 3, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 15}, 3, {4}, {SystemCategory::Home, SystemCategory::CreussGate}, {}, "0"},
  {Position{3, 16}, 3, {4}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}},
  {Position{3, 17}, 3, {5}, {SystemCategory::Planetary, SystemCategory::AnomalyWormholeEmpty}}
};

template <> const std::map<uint8_t, std::set<Pathway>> PlayerPathwaysToMecatolRex<Layout::Players6>{
  {1, {{Pathway{{Position{2, 4}, Position{1, 2}}}}}},
  {2, {{Pathway{{Position{2, 6}, Position{1, 3}}}}}},
  {3, {{Pathway{{Position{2, 8}, Position{1, 4}}}}}},
  {4, {{Pathway{{Position{2, 10}, Position{1, 5}}}}}},
  {5, {{Pathway{{Position{2, 0}, Position{1, 0}}}}}},
  {6, {{Pathway{{Position{2, 2}, Position{1, 1}}}}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockPreferredPositions<Layout::Players6>{
  {1, {Position{2, 4}}},
  {2, {Position{2, 6}}},
  {3, {Position{2, 8}}},
  {4, {Position{2, 10}}},
  {5, {Position{2, 0}}},
  {6, {Position{2, 2}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerForwardSpaceDockAlternatePositions<Layout::Players6>{
  {1, {Position{1, 2}}},
  {2, {Position{1, 3}}},
  {3, {Position{1, 4}}},
  {4, {Position{1, 5}}},
  {5, {Position{1, 0}}},
  {6, {Position{1, 1}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerLateralStarboardPositions<Layout::Players6>{
  {1, {Position{3, 5}}},
  {2, {Position{3, 8}}},
  {3, {Position{3, 11}}},
  {4, {Position{3, 14}}},
  {5, {Position{3, 17}}},
  {6, {Position{3, 2}}}
};

template <> const std::map<uint8_t, std::set<Position>> PlayerLateralPortPositions<Layout::Players6>{
  {1, {Position{3, 7}}},
  {2, {Position{3, 10}}},
  {3, {Position{3, 13}}},
  {4, {Position{3, 16}}},
  {5, {Position{3, 1}}},
  {6, {Position{3, 4}}}
};

} // namespace TI4Cartographer
