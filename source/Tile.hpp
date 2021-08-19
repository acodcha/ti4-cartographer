#pragma once

#include "Position.hpp"
#include "Systems.hpp"

namespace TI4Cartographer {

/// \brief A tile on the game board.
class Tile {

public:

  Tile() noexcept {}

  Tile(const Position& position) noexcept : position_(position) {}

  Tile(
    const Position& position,
    const std::set<uint8_t>& nearest_players,
    const std::set<SystemCategory>& system_categories,
    const std::string& system_id = {}
  ) :
    position_(position),
    nearest_players_(nearest_players),
    system_categories_(system_categories),
    system_id_(system_id)
  {
    initialize_is_planetary_anomaly_wormhole_empty();
    check_system_category();
  }

  void set_system_id(const std::string& system_id) {
    system_id_ = system_id;
    check_system_category();
  }

  const Position& position() const noexcept {
    return position_;
  }

  const std::set<uint8_t>& nearest_players() const noexcept {
    return nearest_players_;
  }

  const std::set<SystemCategory>& system_categories() const noexcept {
    return system_categories_;
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

  bool is_planetary_anomaly_wormhole_empty() const noexcept {
    return is_planetary_anomaly_wormhole_empty_;
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

  std::set<SystemCategory> system_categories_;

  bool is_planetary_anomaly_wormhole_empty_{false};

  std::string system_id_;

  void initialize_is_planetary_anomaly_wormhole_empty() noexcept {
    if (
      system_categories_.find(SystemCategory::Planetary) != system_categories_.cend()
      || system_categories_.find(SystemCategory::AnomalyWormholeEmpty) != system_categories_.cend()
    ) {
      is_planetary_anomaly_wormhole_empty_ = true;
    }
  }

  void check_system_category() const {
    const std::unordered_set<System>::const_iterator found_system{Systems.find({system_id_})};
    if (found_system != Systems.cend()) {
      const std::set<SystemCategory>::const_iterator found_category{system_categories_.find(found_system->category())};
      if (found_category == system_categories_.cend()) {
        error("System " + found_system->print() + " is of the wrong type for the tile at position " + position_.print() + ".");
      }
    }
  }

}; // class Tile

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::Tile> {
    size_t operator()(const TI4Cartographer::Tile& tile) const {
      return hash<TI4Cartographer::Position>()(tile.position());
    }
  };

} // namespace std