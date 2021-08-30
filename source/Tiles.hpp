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

} // namespace TI4Cartographer
