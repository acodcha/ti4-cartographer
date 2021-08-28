#pragma once

#include "Players.hpp"

namespace TI4Cartographer {

/// \brief Distance to a player's home system. Relevant for a position.
class DistanceFromPlayerHome {

public:

  DistanceFromPlayerHome() noexcept {}

  DistanceFromPlayerHome(const Player player, const uint8_t distance_from_home) noexcept : player_(player), distance_from_home_(distance_from_home) {}

  const Player player() const noexcept {
    return player_;
  }

  const uint8_t distance_from_home() const noexcept {
    return distance_from_home_;
  }

  bool operator==(const DistanceFromPlayerHome& other) const noexcept {
    return player_ == other.player_;
  }

  bool operator!=(const DistanceFromPlayerHome& other) const noexcept {
    return player_ != other.player_;
  }

  bool operator<(const DistanceFromPlayerHome& other) const noexcept {
    return player_ < other.player_;
  }

  bool operator<=(const DistanceFromPlayerHome& other) const noexcept {
    return player_ <= other.player_;
  }

  bool operator>(const DistanceFromPlayerHome& other) const noexcept {
    return player_ > other.player_;
  }

  bool operator>=(const DistanceFromPlayerHome& other) const noexcept {
    return player_ >= other.player_;
  }

private:

  Player player_{Player::Player1};

  uint8_t distance_from_home_{0};

}; // class DistanceFromPlayerHome

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::DistanceFromPlayerHome> {
    size_t operator()(const TI4Cartographer::DistanceFromPlayerHome& distance_from_player_home) const {
      return hash<uint8_t>()(static_cast<uint8_t>(distance_from_player_home.player()));
    }
  };

} // namespace std
