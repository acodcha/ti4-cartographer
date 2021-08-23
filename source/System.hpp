#pragma once

#include "Anomalies.hpp"
#include "Factions.hpp"
#include "GameVersions.hpp"
#include "Planet.hpp"
#include "SystemCategories.hpp"
#include "SystemIdAndScore.hpp"
#include "Wormholes.hpp"

namespace TI4Cartographer {

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
    const std::set<Wormhole> wormholes,
    const std::optional<Faction>& faction = {}
  ) noexcept :
    id_(id),
    game_version_(game_version),
    category_(category),
    planets_(planets),
    anomalies_(anomalies),
    wormholes_(wormholes),
    faction_(faction)
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

  const std::optional<Faction>& faction() const noexcept {
    return faction_;
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

  double space_dock_score() const noexcept {
    const uint8_t highest_planet_resources_{highest_planet_resources()};
    if (highest_planet_resources_ == 0) {
      return 1.0;
    } else if (highest_planet_resources_ == 1) {
      return 1.5;
    } else if (highest_planet_resources_ == 2) {
      return 2.5;
    } else if (highest_planet_resources_ >= 3) {
      return 4.5;
    }
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

  /// \brief If this system is a home system or the Creuss Gate system, this is its faction.
  std::optional<Faction> faction_;

  double score_{0.0};

  void check_number_of_planets() const {
    if (planets_.size() > 3) {
      error("A system cannot contain more than 3 planets.");
    }
  }

  void initialize_score() noexcept {
    score_ = individual_planet_scores() + number_of_planets_score() + anomalies_score() + wormholes_score();
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
      return 2.0 * number_of_planets_;
    } else if (number_of_planets_ == 3) {
      return 3.0 * number_of_planets_;
    }
    return 0.0;
  }

  /// \brief Some anomalies are generally beneficial or harmful, whereas others depend heavily on their positioning.
  double anomalies_score() const noexcept {
    double total{0.0};
    for (const Anomaly anomaly : anomalies_) {
      total += TI4Cartographer::score(anomaly);
    }
    return total;
  }

  /// \brief Wormholes are generally beneficial because they provide additional movement options and lead to the Wormhole Nexus.
  double wormholes_score() const noexcept {
    if (contains_one_or_more_wormholes()) {
      return 0.5;
    }
    return 0.0;
  }

}; // class System

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::System> {
    size_t operator()(const TI4Cartographer::System& system) const {
      return hash<string>()(system.id());
    }
  };

} // namespace std
