#pragma once

#include "Layouts.hpp"
#include "Pathway.hpp"
#include "Tile.hpp"

namespace TI4Cartographer {

/// \brief All the tiles on the board.
template <Layout layout> const std::set<Tile> Tiles;

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
