#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

/// \brief Position of a tile on the game board.
class Position {

public:

  constexpr Position() noexcept {}

  constexpr Position(const uint8_t layer, const uint8_t azimuth) noexcept : layer_(layer), azimuth_(azimuth) {}

  uint8_t layer() const noexcept {
    return layer_;
  }

  uint8_t azimuth() const noexcept {
    return azimuth_;
  }

  bool operator==(const Position& other) const noexcept {
    return layer_ == other.layer_ && azimuth_ == other.azimuth_;
  }

  bool operator!=(const Position& other) const noexcept {
    return layer_ != other.layer_ || azimuth_ != other.azimuth_;
  }

  bool operator<(const Position& other) const noexcept {
    if (layer_ < other.layer_) {
      return true;
    } else if (layer_ > other.layer_) {
      return false;
    } else {
      return azimuth_ < other.azimuth_;
    }
  }

  bool operator<=(const Position& other) const noexcept {
    if (layer_ < other.layer_) {
      return true;
    } else if (layer_ > other.layer_) {
      return false;
    } else {
      return azimuth_ <= other.azimuth_;
    }
  }

  bool operator>(const Position& other) const noexcept {
    if (layer_ < other.layer_) {
      return false;
    } else if (layer_ > other.layer_) {
      return true;
    } else {
      return azimuth_ > other.azimuth_;
    }
  }

  bool operator>=(const Position& other) const noexcept {
    if (layer_ < other.layer_) {
      return false;
    } else if (layer_ > other.layer_) {
      return true;
    } else {
      return azimuth_ >= other.azimuth_;
    }
  }

  std::string print() const noexcept {
    std::string text{"r" + std::to_string(layer_) + "a"};
    if (azimuth_ < 10) {
      text += "0";
    }
    return text + std::to_string(azimuth_);
  }

protected:

  /// \brief Layer from the central tile that contains the Mecatol Rex system.
  /// \details Layer 0 contains only 1 tile, which is the Mecatol Rex system.
  /// Layer 1 contains the 6 tiles adjacent to the Mecatol Rex system.
  /// Layer 2 contains the 12 tiles around those.
  /// Layer 3 contains the 18 tiles around those. This is the layer that contains all the home systems in a regular 6-player game.
  /// Layer 4 is only used in 7-8 player games and contains 24 tiles.
  uint8_t layer_{0};

  /// \brief Azimuth is the radial position around a layer.
  /// \details Azimuth 0 is the northernmost tile of the layer, and azimuth increases clockwise.
  /// The tiles of layer 1 can have azimuth 0 to 5.
  /// The tiles of layer 2 can have azimuth 0 to 11.
  /// The tiles of layer 3 can have azimuth 0 to 17.
  /// The tiles of layer 4 can have azimuth 0 to 23.
  uint8_t azimuth_{0};

}; // class Position

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::Position> {
    size_t operator()(const TI4Cartographer::Position& position) const {
      return hash<uint8_t>()(position.layer()) ^ hash<uint8_t>()(position.azimuth());
    }
  };

} // namespace std
