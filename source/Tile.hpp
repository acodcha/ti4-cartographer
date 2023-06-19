#pragma once

#include "Player.hpp"
#include "Position.hpp"
#include "Systems.hpp"

namespace TI4Cartographer {

/// \brief A tile on the game board.
class Tile {
public:
  /// \brief Constructor for a planetary system, an anomaly/wormhole/empty
  /// system, or the Mecatol Rex system.
  Tile(const Position& position,
       const std::set<Position>& hyperlane_neighbors = {}) noexcept
    : position_(position), hyperlane_neighbors_(hyperlane_neighbors) {
    if (position_ == MecatolRexPosition) {
      system_categories_.insert(SystemCategory::MecatolRex);
      system_id_ = MecatolRexSystemId;
    } else {
      system_categories_.insert(SystemCategory::Planetary);
      system_categories_.insert(SystemCategory::AnomalyWormholeEmpty);
      is_planetary_anomaly_wormhole_or_empty_ = true;
    }
  }

  /// \brief Constructor for a home system.
  Tile(const Position& position, const Player home_player,
       const std::set<Position>& hyperlane_neighbors = {}) noexcept
    : position_(position), hyperlane_neighbors_(hyperlane_neighbors),
      home_player_(home_player) {
    system_categories_.insert(SystemCategory::Home);
    system_categories_.insert(SystemCategory::CreussGate);
    system_id_ = "0";
  }

  /// \brief Constructor for a hyperlane system or a skipped tile. System ID -1
  /// indicates a skipped tile.
  Tile(const Position& position, const std::string& system_id)
    : position_(position), system_id_(system_id) {
    if (system_id_ != "-1") {
      system_categories_.insert(SystemCategory::Hyperlane);
      is_hyperlane_ = true;
      const std::unordered_set<System>::const_iterator system{
        Systems.find({system_id_})};
      if (system == Systems.cend()) {
        error("System ID " + system_id + " does not exist. Trying to assign this system to the tile at position " + position.print() + ".");
      }
      if (system != Systems.cend()
          && system->category() != SystemCategory::Hyperlane) {
        error("System " + system->print() + " is not a hyperlane. Trying to assign this system to the tile at position " + position.print() + ".");
      }
    }
  }

  void set_system_id(const std::string& system_id) {
    system_id_ = system_id;
    check_system_category();
  }

  const Position& position() const noexcept { return position_; }

  const std::set<SystemCategory>& system_categories() const noexcept {
    return system_categories_;
  }

  bool system_categories_contains(
    const SystemCategory system_category) const noexcept {
    if (system_categories_.find(system_category) != system_categories_.cend()) {
      return true;
    } else {
      return false;
    }
  }

  bool is_planetary_anomaly_wormhole_or_empty() const noexcept {
    return is_planetary_anomaly_wormhole_or_empty_;
  }

  bool is_hyperlane() const noexcept { return is_hyperlane_; }

  const std::set<Position>& hyperlane_neighbors() const noexcept {
    return hyperlane_neighbors_;
  }

  const std::string& system_id() const noexcept { return system_id_; }

  const std::optional<Player>& home_player() const noexcept {
    return home_player_;
  }

  bool operator==(const Tile& other) const noexcept {
    return position_ == other.position_;
  }

  bool operator!=(const Tile& other) const noexcept {
    return position_ != other.position_;
  }

  bool operator<(const Tile& other) const noexcept {
    return position_ < other.position_;
  }

  bool operator<=(const Tile& other) const noexcept {
    return position_ <= other.position_;
  }

  bool operator>(const Tile& other) const noexcept {
    return position_ > other.position_;
  }

  bool operator>=(const Tile& other) const noexcept {
    return position_ >= other.position_;
  }

  std::string print() const noexcept {
    return position_.print() + " " + system_id_;
  }

private:
  Position position_;

  std::set<SystemCategory> system_categories_;

  bool is_planetary_anomaly_wormhole_or_empty_{false};

  bool is_hyperlane_{false};

  std::set<Position> hyperlane_neighbors_;

  std::string system_id_;

  /// \brief If this tile is a home system or the Creuss Gate system, this is
  /// the player whose system this is.
  std::optional<Player> home_player_;

  void check_system_category() const {
    const std::unordered_set<System>::const_iterator system{
      Systems.find({system_id_})};
    if (system != Systems.cend()) {
      const std::set<SystemCategory>::const_iterator system_category{
        system_categories_.find(system->category())};
      if (system_category == system_categories_.cend()) {
        error("System " + system->print()
              + " is of the wrong type for the tile at position "
              + position_.print() + ".");
      }
    }
  }

};  // class Tile

}  // namespace TI4Cartographer

namespace std {

template<> struct hash<TI4Cartographer::Tile> {
  size_t operator()(const TI4Cartographer::Tile& tile) const {
    return hash<TI4Cartographer::Position>()(tile.position());
  }
};

}  // namespace std
