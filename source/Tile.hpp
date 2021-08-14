#pragma once

#include "Position.hpp"

namespace ti4cartographer {

/// \brief A tile on the game board.
class Tile {

public:

  Tile() noexcept {}

  Tile(const Position& position) noexcept : position_(position) {}

  Tile(
    const Position& position,
    const std::set<uint8_t>& nearest_players,
    const std::string& system_id = {}
  ) noexcept :
    position_(position),
    nearest_players_(nearest_players),
    system_id_(system_id)
  {}

  void set_system_id(const std::string& system_id) noexcept {
    system_id_ = system_id;
  }

  const Position& position() const noexcept {
    return position_;
  }

  const std::set<uint8_t>& nearest_players() const noexcept {
    return nearest_players_;
  }

  const std::string& system_id() const noexcept {
    return system_id_;
  }

  bool is_equidistant() const noexcept {
    return nearest_players_.size() >= 2;
  }

  bool is_in_a_slice() const noexcept {
    return nearest_players_.size() == 1;
  }

  bool is_in_slice(const uint8_t player_index) const noexcept {
    return nearest_players_.find(player_index) != nearest_players_.cend();
  }

  bool operator==(const Tile& other) const noexcept {
    return position_ == other.position_ ;
  }

  bool operator!=(const Tile& other) const noexcept {
    return position_ != other.position_ ;
  }

  bool operator<(const Tile& other) const noexcept {
    return position_ < other.position_ ;
  }

  bool operator<=(const Tile& other) const noexcept {
    return position_ <= other.position_ ;
  }

  bool operator>(const Tile& other) const noexcept {
    return position_ > other.position_ ;
  }

  bool operator>=(const Tile& other) const noexcept {
    return position_ >= other.position_ ;
  }

protected:

  Position position_;

  /// \brief Set of players whose home systems are equally nearest to this tile. Note that player numbering starts at 1.
  /// \details If this set contains a single player, then this tile is in that player's slice of the game board.
  /// If this set contains multiple players, then this tile is equidistant to each of those players.
  std::set<uint8_t> nearest_players_;

  std::string system_id_;

}; // class Tile

} // namespace ti4cartographer

namespace std {

  template <> struct hash<ti4cartographer::Tile> {
    size_t operator()(const ti4cartographer::Tile& tile) const {
      return hash<ti4cartographer::Position>()(tile.position());
    }
  };

} // namespace std
