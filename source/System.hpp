#pragma once

#include "Anomalies.hpp"
#include "GameVersions.hpp"
#include "Planet.hpp"
#include "SystemCategories.hpp"
#include "SystemIdAndScore.hpp"
#include "Wormholes.hpp"

namespace ti4cartographer {

class System {

public:

  System() noexcept {}

  System(const std::string& id) noexcept : id_(id) {}

  System(
    const std::string& id,
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
    initialize_score();
  }

  const std::string& id() const noexcept {
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

  double score() const noexcept {
    return score_;
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

  std::string print() const noexcept {
    std::string text{"#" + id_ + ":  "};
    uint8_t counter{0};
    for (const Planet& planet : planets_) {
      if (counter > 0) {
        text += "  +  ";
      }
      text += planet.print();
      ++counter;
    }
    for (const Anomaly& anomaly : anomalies_) {
      if (counter > 0) {
        text += "  +  ";
      }
      text += label(anomaly);
      ++counter;
    }
    for (const Wormhole& wormhole : wormholes_) {
      if (counter > 0) {
        text += "  +  ";
      }
      text += label(wormhole);
      ++counter;
    }
    if (counter == 0) {
      text += "Empty";
    }
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

  /// \brief Each system must have a unique ID.
  std::string id_{};

  GameVersion game_version_{GameVersion::BaseGame};

  SystemCategory category_{SystemCategory::Planetary};

  std::set<Planet, Planet::sort_by_name> planets_;

  std::set<Anomaly> anomalies_;

  std::set<Wormhole> wormholes_;

  double score_{0.0};

  void check_number_of_planets() const {
    if (planets_.size() > 3) {
      error("A system cannot contain more than 3 planets.");
    }
  }

  void initialize_score() noexcept {
    score_ = individual_planet_scores() + number_of_planets_score() + anomalies_score() + wormholes_score() + space_dock_score();
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
    const uint8_t number_of_planets_{number_of_planets()};
    if (number_of_planets_ == 1) {
      return 1.0 * number_of_planets_;
    } else if (number_of_planets_ == 2) {
      return 1.5 * number_of_planets_;
    } else if (number_of_planets_ == 3) {
      return 2.0 * number_of_planets_;
    }
    return 0.0;
  }

  /// \brief Some anomalies are generally beneficial or harmful, whereas others depend heavily on their positioning.
  double anomalies_score() const noexcept {
    double score{0.0};
    if (contains(Anomaly::AsteroidField)) {
      // If you have Antimass Deflectors researched, this is effectively an empty system.
      // If you do not, this is worse because it prevents movement and therefore reduces your options.
      // The Clan of Saar strongly prefers these due to their faction technology.
      score += -0.5;
    }
    if (contains(Anomaly::GravityRift)) {
      // Gives extra movement and therefore extra options. Beneficial.
      score += 1.0;
    }
    if (contains(Anomaly::Nebula)) {
      // Better defense, but slows movement. Net neutral.
      // The Empyrean strongly prefers these due to their faction ability.
      score += 0.0;
    }
    if (contains(Anomaly::Supernova)) {
      // Prevents movement and therefore reduces your options. Generally bad.
      // The Embers of Muaat strongly prefer these due to their faction ability and technology.
      score += -0.5;
    }
    return score;
  }

  /// \brief Wormholes are generally beneficial because they provide additional movement options and lead to the Wormhole Nexus.
  double wormholes_score() const noexcept {
    if (contains_one_or_more_wormholes()) {
      return 1.0;
    }
    return 0.0;
  }

  /// \brief The maximum planet resource value is useful for building a space dock.
  double space_dock_score() const noexcept {
    return 0.25 * highest_planet_resources();
  }

}; // class System

} // namespace ti4cartographer

namespace std {

  template <> struct hash<ti4cartographer::System> {
    size_t operator()(const ti4cartographer::System& system) const {
      return hash<string>()(system.id());
    }
  };

} // namespace std
