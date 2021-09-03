#pragma once

#include "Layouts.hpp"
#include "Pathway.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief All the tiles on the board.
template <Layout layout> const std::set<Tile> Tiles;

template <> std::set<Tile> const Tiles<Layout::Players2>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 11}},
  {Position{3, 12}, Player::Player1},
  {Position{3, 13}},
  {Position{3, 14}},
  {Position{3, 15}, Player::Player2},
  {Position{3, 16}},
  {Position{4, 17}},
  {Position{4, 18}},
  {Position{4, 19}}
};

template <> std::set<Tile> const Tiles<Layout::Players3Regular>{
  {Position{0, 0}},
  {Position{1, 0}, "85A-3"},
  {Position{1, 1}, {Position{1, 3}, Position{1, 5}, Position{2, 0}, Position{2, 4}}},
  {Position{1, 2}, "85A-5"},
  {Position{1, 3}, {Position{1, 1}, Position{1, 5}, Position{2, 4}, Position{2, 8}}},
  {Position{1, 4}, "85A-1"},
  {Position{1, 5}, {Position{1, 1}, Position{1, 3}, Position{2, 0}, Position{2, 8}}},
  {Position{2, 0}, {Position{1, 1}, Position{1, 5}, Position{2, 2}, Position{2, 10}, Position{3, 2}, Position{3, 16}}},
  {Position{2, 1}, "87A-3"},
  {Position{2, 2}, {Position{2, 0}, Position{2, 4}}},
  {Position{2, 3}, "88A-5"},
  {Position{2, 4}, {Position{1, 1}, Position{1, 3}, Position{2, 2}, Position{2, 6}, Position{3, 4}, Position{3, 8}}},
  {Position{2, 5}, "87A-5"},
  {Position{2, 6}, {Position{2, 4}, Position{2, 8}}},
  {Position{2, 7}, "88A-1"},
  {Position{2, 8}, {Position{1, 3}, Position{1, 5}, Position{2, 6}, Position{2, 10}, Position{3, 10}, Position{3, 14}}},
  {Position{2, 9}, "87A-1"},
  {Position{2, 10}, {Position{2, 0}, Position{2, 8}}},
  {Position{2, 11}, "88A-3"},
  {Position{3, 0}, "86A-3"},
  {Position{3, 1}, "84A-3"},
  {Position{3, 2}, {Position{2, 0}, Position{3, 16}}},
  {Position{3, 3}, Player::Player3},
  {Position{3, 4}, {Position{2, 4}, Position{3, 8}}},
  {Position{3, 5}, "83A-5"},
  {Position{3, 6}, "86A-5"},
  {Position{3, 7}, "84A-5"},
  {Position{3, 8}, {Position{2, 4}, Position{3, 4}}},
  {Position{3, 9}, Player::Player1},
  {Position{3, 10}, {Position{2, 8}, Position{3, 14}}},
  {Position{3, 11}, "83A-1"},
  {Position{3, 12}, "86A-1"},
  {Position{3, 13}, "84A-1"},
  {Position{3, 14}, {Position{2, 8}, Position{3, 10}}},
  {Position{3, 15}, Player::Player2},
  {Position{3, 16}, {Position{2, 0}, Position{3, 2}}},
  {Position{3, 17}, "83A-3"}
};

template <> std::set<Tile> const Tiles<Layout::Players3Small>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}, Player::Player3},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}, Player::Player1},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}, Player::Player2},
  {Position{2, 11}},
};

template <> std::set<Tile> const Tiles<Layout::Players3Large>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 2}},
  {Position{3, 3}, Player::Player3},
  {Position{3, 4}},
  {Position{3, 8}},
  {Position{3, 9}, Player::Player1},
  {Position{3, 10}},
  {Position{3, 14}},
  {Position{3, 15}, Player::Player2},
  {Position{3, 16}},
};

template <> std::set<Tile> const Tiles<Layout::Players4Regular>{
  {Position{0, 0}},
  {Position{1, 0}, "85A-3"},
  {Position{1, 1}, {Position{1, 5}, Position{2, 0}}},
  {Position{1, 2}, {Position{1, 4}, Position{2, 6}}},
  {Position{1, 3}, "85A-0"},
  {Position{1, 4}, {Position{1, 2}, Position{2, 6}}},
  {Position{1, 5}, {Position{1, 1}, Position{2, 0}}},
  {Position{2, 0}, {Position{1, 1}, Position{1, 5}, Position{2, 2}, Position{2, 10}, Position{3, 2}, Position{3, 16}}},
  {Position{2, 1}, "87A-3"},
  {Position{2, 2}, {Position{2, 0}}},
  {Position{2, 3}},
  {Position{2, 4}, {Position{2, 6}}},
  {Position{2, 5}, "88A-0"},
  {Position{2, 6}, {Position{1, 2}, Position{1, 4}, Position{2, 4}, Position{2, 8}, Position{3, 7}, Position{3, 11}}},
  {Position{2, 7}, "87A-0"},
  {Position{2, 8}, {Position{2, 6}}},
  {Position{2, 9}},
  {Position{2, 10}, {Position{2, 0}}},
  {Position{2, 11}, "88A-3"},
  {Position{3, 0}, "86A-3"},
  {Position{3, 1}, "84A-3"},
  {Position{3, 2}, {Position{2, 0}, Position{3, 16}}},
  {Position{3, 3}, Player::Player4},
  {Position{3, 4}},
  {Position{3, 5}},
  {Position{3, 6}, Player::Player1},
  {Position{3, 7}, {Position{2, 6}, Position{3, 11}}},
  {Position{3, 8}, "83A-0"},
  {Position{3, 9}, "86A-0"},
  {Position{3, 10}, "84A-0"},
  {Position{3, 11}, {Position{2, 6}, Position{3, 7}}},
  {Position{3, 12}, Player::Player2},
  {Position{3, 13}},
  {Position{3, 14}},
  {Position{3, 15}, Player::Player3},
  {Position{3, 16}, {Position{2, 0}, Position{3, 2}}},
  {Position{3, 17}, "83A-3"}
};

template <> std::set<Tile> const Tiles<Layout::Players4Large>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 4}, Player::Player4},
  {Position{3, 5}},
  {Position{3, 7}},
  {Position{3, 8}, Player::Player1},
  {Position{3, 13}, Player::Player2},
  {Position{3, 14}},
  {Position{3, 16}},
  {Position{3, 17}, Player::Player3}
};

template <> std::set<Tile> const Tiles<Layout::Players5Regular>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}, {Position{1, 4}, Position{2, 6}}},
  {Position{1, 3}, "85A-0"},
  {Position{1, 4}, {Position{1, 2}, Position{2, 6}}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}, {Position{2, 6}}},
  {Position{2, 5}, "88A-0"},
  {Position{2, 6}, {Position{1, 2}, Position{1, 4}, Position{2, 4}, Position{2, 8}, Position{3, 7}, Position{3, 11}}},
  {Position{2, 7}, "87A-0"},
  {Position{2, 8}, {Position{2, 6}}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 0}, Player::Player4},
  {Position{3, 1}},
  {Position{3, 2}},
  {Position{3, 3}, Player::Player5},
  {Position{3, 4}},
  {Position{3, 5}},
  {Position{3, 6}, Player::Player1},
  {Position{3, 7}, {Position{2, 6}, Position{3, 11}}},
  {Position{3, 8}, "83A-0"},
  {Position{3, 9}, "86A-0"},
  {Position{3, 10}, "84A-0"},
  {Position{3, 11}, {Position{2, 6}, Position{3, 7}}},
  {Position{3, 12}, Player::Player2},
  {Position{3, 13}},
  {Position{3, 14}},
  {Position{3, 15}, Player::Player3},
  {Position{3, 16}},
  {Position{3, 17}}
};

template <> std::set<Tile> const Tiles<Layout::Players5Small>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 0}, Player::Player4},
  {Position{3, 1}},
  {Position{3, 4}, Player::Player5},
  {Position{3, 5}},
  {Position{3, 7}, Player::Player1},
  {Position{3, 8}},
  {Position{3, 9}},
  {Position{3, 10}},
  {Position{3, 11}, Player::Player2},
  {Position{3, 13}},
  {Position{3, 14}, Player::Player3},
  {Position{3, 17}}
};

template <> std::set<Tile> const Tiles<Layout::Players5Large>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 0}, Player::Player4},
  {Position{3, 1}},
  {Position{3, 2}},
  {Position{3, 3}},
  {Position{3, 4}, Player::Player5},
  {Position{3, 5}},
  {Position{3, 6}},
  {Position{3, 7}, Player::Player1},
  {Position{3, 8}},
  {Position{3, 9}},
  {Position{3, 10}},
  {Position{3, 11}, Player::Player2},
  {Position{3, 12}},
  {Position{3, 13}},
  {Position{3, 14}, Player::Player3},
  {Position{3, 15}},
  {Position{3, 16}},
  {Position{3, 17}}
};

template <> std::set<Tile> const Tiles<Layout::Players6>{
  {Position{0, 0}},
  {Position{1, 0}},
  {Position{1, 1}},
  {Position{1, 2}},
  {Position{1, 3}},
  {Position{1, 4}},
  {Position{1, 5}},
  {Position{2, 0}},
  {Position{2, 1}},
  {Position{2, 2}},
  {Position{2, 3}},
  {Position{2, 4}},
  {Position{2, 5}},
  {Position{2, 6}},
  {Position{2, 7}},
  {Position{2, 8}},
  {Position{2, 9}},
  {Position{2, 10}},
  {Position{2, 11}},
  {Position{3, 0}, Player::Player5},
  {Position{3, 1}},
  {Position{3, 2}},
  {Position{3, 3}, Player::Player6},
  {Position{3, 4}},
  {Position{3, 5}},
  {Position{3, 6}, Player::Player1},
  {Position{3, 7}},
  {Position{3, 8}},
  {Position{3, 9}, Player::Player2},
  {Position{3, 10}},
  {Position{3, 11}},
  {Position{3, 12}, Player::Player3},
  {Position{3, 13}},
  {Position{3, 14}},
  {Position{3, 15}, Player::Player4},
  {Position{3, 16}},
  {Position{3, 17}}
};

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

} // namespace TI4Cartographer
