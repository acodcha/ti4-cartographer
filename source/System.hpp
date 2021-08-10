#pragma once

#include "Planet.hpp"

namespace TI4MapGenerator {

class System {

public:

  System() noexcept {}

  System(
    const uint8_t id,
    const SystemCategory category,
    const std::set<SystemPlacementType>& valid_placements,
    const std::set<Planet, Planet::sort_by_name>& planets = {},
    const std::set<WormholeType> wormholes = {},
    const std::set<AnomalyType> anomalies = {}
  ) noexcept :
    id_(id),
    category_(category),
    valid_placements_(valid_placements),
    planets_(planets),
    wormholes_(wormholes),
    anomalies_(anomalies)
  {
    check_at_least_one_valid_placement();
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
    for (const WormholeType& wormhole : wormholes_) {
      if (counter > 0) {
        text += " + ";
      }
      text += label(wormhole);
      ++counter;
    }
    for (const AnomalyType& anomaly : anomalies_) {
      if (counter > 0) {
        text += " + ";
      }
      text += label(anomaly);
      ++counter;
    }
    return text;
  }

  SystemCategory category() const noexcept {
    return category_;
  }

  const std::set<SystemPlacementType>& valid_placements() const noexcept {
    return valid_placements_;
  }

  const std::set<Planet, Planet::sort_by_name>& planets() const noexcept {
    return planets_;
  }

  const std::set<WormholeType>& wormholes() const noexcept {
    return wormholes_;
  }

  const std::set<AnomalyType>& anomalies() const noexcept {
    return anomalies_;
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

  bool contains(const WormholeType wormhole_type) const noexcept {
    return wormholes_.find(wormhole_type) != wormholes_.cend();
  }

  bool contains(const AnomalyType anomaly_type) const noexcept {
    return anomalies_.find(anomaly_type) != anomalies_.cend();
  }

  bool contains_one_or_more_wormholes() const noexcept {
    return !wormholes_.empty();
  }

  bool contains_one_or_more_anomalies() const noexcept {
    return !anomalies_.empty();
  }

  double score() const noexcept {
    return individual_planet_scores() + number_of_planets_score() + wormholes_score() + anomalies_score() + space_dock_score();
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
    for (const WormholeType& wormhole : wormholes_) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(wormhole);
      ++counter;
    }
    for (const AnomalyType& anomaly : anomalies_) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(anomaly);
      ++counter;
    }
    for (const SystemPlacementType& placement : valid_placements_) {
      if (counter > 0) {
        text += ", ";
      }
      text += label(placement);
      ++counter;
    }
    text += ".";
    return text;
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

  SystemCategory category_{SystemCategory::Planetary};

  std::set<SystemPlacementType> valid_placements_;

  std::set<Planet, Planet::sort_by_name> planets_;

  std::set<WormholeType> wormholes_;

  std::set<AnomalyType> anomalies_;

  void check_at_least_one_valid_placement() const {
    if (valid_placements_.empty()) {
      error("A system needs at least one valid placement option.");
    }
  }

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

  /// \brief Wormholes are generally unwanted.
  double wormholes_score() const noexcept {
    if (contains_one_or_more_wormholes()) {
      return -1.0;
    }
    return 0.0;
  }

  /// \brief The supernova and nebula are generally beneficial, whereas the asteroid field and the gravity rift are generally unwanted.
  double anomalies_score() const noexcept {
    double score{0.0};
    if (contains(AnomalyType::AsteroidField)) {
      score += -1.0;
    }
    if (contains(AnomalyType::GravityRift)) {
      score += -2.0;
    }
    if (contains(AnomalyType::Nebula)) {
      score += 1.0;
    }
    if (contains(AnomalyType::Supernova)) {
      score += 2.0;
    }
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
