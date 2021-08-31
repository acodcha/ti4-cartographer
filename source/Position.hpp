#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

int8_t maximum_azimuth(const int8_t layer) noexcept {
  if (layer <= 0) {
    return 0;
  }
  return 6 * layer - 1;
}

/// \brief Position of a tile on the game board.
class Position {

public:

  constexpr Position() noexcept {}

  constexpr Position(const int8_t layer, const int8_t azimuth) noexcept : layer_(layer), azimuth_(azimuth) {}

  int8_t layer() const noexcept {
    return layer_;
  }

  int8_t azimuth() const noexcept {
    return azimuth_;
  }

  bool is_valid() const noexcept {
    return azimuth_ <= maximum_azimuth(layer_);
  }

  /// \brief Returns true if this position is at one of the six "corners" of this layer.
  bool is_a_corner() const noexcept {
    if (layer_ == 0) {
      return true;
    } else {
      return azimuth_ % layer_ == 0;
    }
  }

  /// \brief Set of positions that are neighbors with this position, i.e. adjacent. These positions may or may not exist on the game board.
  std::set<Position> possible_neighbors() const noexcept {
    std::set<Position> positions;
    const int8_t maximum_azimuth_{maximum_azimuth(layer_)};
    const int8_t number_of_corners{static_cast<int8_t>(layer_ > 0 ? azimuth_ / layer_ : 0)};
    const int8_t azimuth_after_corner{static_cast<int8_t>(layer_ > 0 ? azimuth_ % layer_ : 0)};
    // Same layer.
    if (layer_ > 0) {
      // Same layer, previous azimuth.
      if (azimuth_ == 0) {
        positions.insert({layer_, maximum_azimuth_});
      } else {
        positions.insert({layer_, static_cast<int8_t>(azimuth_ - 1)});
      }
      // Same layer, next azimuth.
      if (azimuth_ == maximum_azimuth_) {
        positions.insert({layer_, 0});
      } else {
        positions.insert({layer_, static_cast<int8_t>(azimuth_ + 1)});
      }
    }
    // Inner layer.
    if (layer_ > 0) {
      const int8_t layer_minus_one{static_cast<int8_t>(layer_ - 1)};
      if (is_a_corner()) {
        // There is only 1 inner layer neighbor.
        positions.insert({layer_minus_one, static_cast<int8_t>(azimuth_ / layer_ * layer_minus_one)});
      } else {
        // There are 2 inner layer neighbors.
        const int8_t inner_layer_azimuth_1{static_cast<int8_t>(number_of_corners * layer_minus_one + azimuth_after_corner - 1)};
        positions.insert({layer_minus_one, inner_layer_azimuth_1});
        const int8_t inner_layer_azimuth_2{static_cast<int8_t>(number_of_corners * layer_minus_one + azimuth_after_corner)};
        if (inner_layer_azimuth_2 > maximum_azimuth(layer_minus_one)) {
          positions.insert({layer_minus_one, 0});
        } else {
          positions.insert({layer_minus_one, inner_layer_azimuth_2});
        }
      }
    }
    // Outer layer.
    const int8_t layer_plus_one{static_cast<int8_t>(layer_ + 1)};
    const int8_t outer_layer_azimuth_to_corner{static_cast<int8_t>(number_of_corners * layer_plus_one)};
    if (layer_ > 0) {
      if (is_a_corner()) {
        // There are 3 outer layer neighbors.
        positions.insert({layer_plus_one, outer_layer_azimuth_to_corner});
        if (outer_layer_azimuth_to_corner > 0) {
          positions.insert({layer_plus_one, static_cast<int8_t>(outer_layer_azimuth_to_corner - 1)});
        } else {
          positions.insert({layer_plus_one, maximum_azimuth(layer_plus_one)});
        }
        if (outer_layer_azimuth_to_corner < maximum_azimuth(layer_plus_one)) {
          positions.insert({layer_plus_one, static_cast<int8_t>(outer_layer_azimuth_to_corner + 1)});
        } else {
          positions.insert({layer_plus_one, 0});
        }
      } else {
        // There are 2 outer layer neighbors.
        positions.insert({layer_plus_one, static_cast<int8_t>(outer_layer_azimuth_to_corner + azimuth_after_corner)});
        positions.insert({layer_plus_one, static_cast<int8_t>(outer_layer_azimuth_to_corner + azimuth_after_corner + 1)});
      }
    } else {
      // In this case, the layer is 0, and the only neighbors are the 6 neighbors on layer 1.
      for (int8_t azimuth = 0; azimuth < 6; ++azimuth) {
        positions.insert({1, azimuth});
      }
    }
    return positions;
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

private:

  /// \brief Layer from the central tile that contains the Mecatol Rex system.
  /// \details Layer 0 contains only 1 tile, which is the Mecatol Rex system.
  /// Layer 1 contains the 6 tiles adjacent to the Mecatol Rex system.
  /// Layer 2 contains the 12 tiles around those.
  /// Layer 3 contains the 18 tiles around those. This is the layer that contains the home systems in a regular 6-player game.
  /// Layer 4 is only used in 7-8 player games and contains 24 tiles.
  int8_t layer_{0};

  /// \brief Azimuth is the radial position around a layer.
  /// \details Azimuth 0 is the northernmost tile of the layer, and azimuth increases clockwise.
  /// The tiles of layer 1 can have azimuth 0 to 5.
  /// The tiles of layer 2 can have azimuth 0 to 11.
  /// The tiles of layer 3 can have azimuth 0 to 17.
  /// The tiles of layer 4 can have azimuth 0 to 23.
  int8_t azimuth_{0};

}; // class Position

} // namespace TI4Cartographer

namespace std {

template <> struct hash<TI4Cartographer::Position> {
  size_t operator()(const TI4Cartographer::Position& position) const {
    return hash<int8_t>()(position.layer()) ^ hash<int8_t>()(position.azimuth());
  }
};

} // namespace std
