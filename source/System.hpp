#pragma once

#include "Planet.hpp"

namespace TI4MapGenerator {

class System {

public:

  System() noexcept {}

  System(
    const uint8_t id,
    const GameVersion game_version,
    const SystemCategory category,
    const std::set<Planet, Planet::sort_by_name>& planets,
    const std::set<Anomaly> anomalies,
    const std::set<Wormhole> wormholes
  ) noexcept :
    id_(id),
    game_version_(game_version),
    category_(category),
    planets_(planets),
    anomalies_(anomalies),
    wormholes_(wormholes)
  {
    check_number_of_planets();
  }

  uint8_t id() const noexcept {
    return id_;
  }

  std::string name() const noexcept {
    if (planets_.empty() && wormholes_.empty() && anomalies_.empty()) {
      return "Empty";
    }
    std::string text;
    uint8_t counter{0};
    for (const Planet& planet : planets_) {
      if (counter > 0) {
        text += " + ";
      }
      text += planet.name();
      ++counter;
    }
    for (const Anomaly& anomaly : anomalies_) {
      if (counter > 0) {
        text += " + ";
      }
      text += label(anomaly);
      ++counter;
    }
    for (const Wormhole& wormhole : wormholes_) {
      if (counter > 0) {
        text += " + ";
      }
      text += label(wormhole);
      ++counter;
    }
    return text;
  }

  GameVersion game_version() const noexcept {
    return game_version_;
  }

  SystemCategory category() const noexcept {
    return category_;
  }

  const std::set<Planet, Planet::sort_by_name>& planets() const noexcept {
    return planets_;
  }

  const std::set<Anomaly>& anomalies() const noexcept {
    return anomalies_;
  }

  const std::set<Wormhole>& wormholes() const noexcept {
    return wormholes_;
  }

  uint8_t highest_planet_resources() const noexcept {
    uint8_t number{0};
    for (const Planet& planet : planets_) {
      if (number < planet.resources()) {
        number = planet.resources();
      }
    }
    return number;
  }

  uint8_t number_of_planets() const noexcept {
    return static_cast<uint8_t>(planets_.size());
  }

  bool contains(const Anomaly anomaly_type) const noexcept {
    return anomalies_.find(anomaly_type) != anomalies_.cend();
  }

  bool contains(const Wormhole wormhole_type) const noexcept {
    return wormholes_.find(wormhole_type) != wormholes_.cend();
  }

  bool contains_one_or_more_anomalies() const noexcept {
    return !anomalies_.empty();
  }

  bool contains_one_or_more_wormholes() const noexcept {
    return !wormholes_.empty();
  }

  double score() const noexcept {
    return individual_planet_scores() + number_of_planets_score() + anomalies_score() + wormholes_score() + space_dock_score();
  }

  std::set<SystemPlacementType> valid_placements() const noexcept {
    // All systems can be equidistant or lateral.
    std::set<SystemPlacementType> result{
      SystemPlacementType::Equidistant,
      SystemPlacementType::LateralClockwise,
      SystemPlacementType::LateralCounterClockwise
    };
    // A system can only be forward-far if it does not contain a gravity rift or a supernova.
    if (!contains(Anomaly::GravityRift) && !contains(Anomaly::Supernova)) {
      result.insert(SystemPlacementType::ForwardFar);
    }
    // A system can only be forward-near if it contains at least one planet with at least 2 resources.
    if (highest_planet_resources() >= 2) {
      result.insert(SystemPlacementType::ForwardNear);
    }
    return result;
  }

  std::string print() const noexcept {
    std::string text{"#" + std::to_string(id_) + " (" + label(category_) + ")"};
    uint8_t counter{0};
    text += ": ";
    for (const Planet& planet : planets_) {
      if (counter > 0) {
        text += ", ";
      }
      text += planet.print();
      ++counter;
    }
    for (const Wormhole& wormhole : wormholes_) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(wormhole);
      ++counter;
    }
    for (const Anomaly& anomaly : anomalies_) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(anomaly);
      ++counter;
    }
    for (const SystemPlacementType& placement : valid_placements()) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(placement);
      ++counter;
    }
    text += ".";
    return text;
  }

  bool operator==(const System& other) const noexcept {
    return id_ == other.id_;
  }

  bool operator!=(const System& other) const noexcept {
    return id_ != other.id_;
  }

  struct sort_by_id {
    bool operator()(const System& system_1, const System& system_2) const noexcept {
      return system_1.id_ < system_2.id_;
    }
  };

  struct sort_by_score {
    bool operator()(const System& system_1, const System& system_2) const noexcept {
      return system_1.score() < system_2.score();
    }
  };

protected:

  /// \brief Each system must have a unique ID number.
  uint8_t id_{0};

  GameVersion game_version_{GameVersion::BaseGame};

  SystemCategory category_{SystemCategory::Planetary};

  std::set<Planet, Planet::sort_by_name> planets_;

  std::set<Anomaly> anomalies_;

  std::set<Wormhole> wormholes_;

  void check_number_of_planets() const {
    if (planets_.size() > 3) {
      error("A system cannot contain more than 3 planets.");
    }
  }

  /// \brief The base system score is the sum of the individual planet scores.
  double individual_planet_scores() const noexcept {
    double score{0.0};
    for (const Planet& planet : planets_) {
      score += planet.score();
    }
    return score;
  }

  /// \brief It is preferable to have multiple planets in one system due to scoring objectives, command token efficiency, and ease of defending the space area.
  double number_of_planets_score() const noexcept {
    if (number_of_planets() == 1) {
      return 2.0 * number_of_planets();
    } else if (number_of_planets() == 2) {
      return 2.5 * number_of_planets();
    } else if (number_of_planets() == 3) {
      return 3.0 * number_of_planets();
    }
    return 0.0;
  }

  /// \brief The supernova and nebula are generally beneficial, whereas the asteroid field and the gravity rift are generally unwanted.
  double anomalies_score() const noexcept {
    double score{0.0};
    if (contains(Anomaly::AsteroidField)) {
      score += -1.0;
    }
    if (contains(Anomaly::GravityRift)) {
      score += -2.0;
    }
    if (contains(Anomaly::Nebula)) {
      score += 1.0;
    }
    if (contains(Anomaly::Supernova)) {
      score += 2.0;
    }
  }

  /// \brief Wormholes are generally unwanted.
  double wormholes_score() const noexcept {
    if (contains_one_or_more_wormholes()) {
      return -1.0;
    }
    return 0.0;
  }

  /// \brief The maximum planet resource value is useful for building a space dock.
  double space_dock_score() const noexcept {
    return 0.5 * highest_planet_resources();
  }

}; // class System

} // namespace TI4MapGenerator

namespace std {

  template <> struct hash<TI4MapGenerator::System> {
    size_t operator()(const TI4MapGenerator::System& system) const {
      return hash<uint8_t>()(system.id());
    }
  };

} // namespace std
