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

  float score() const noexcept {
    return score_;
  }

  int8_t highest_planet_resources() const noexcept {
    int8_t highest_planet_resources_{0};
    for (const Planet& planet : planets_) {
      if (planet.resources() > highest_planet_resources_) {
        highest_planet_resources_ = planet.resources();
      }
    }
    return highest_planet_resources_;
  }

  float space_dock_score() const noexcept {
    if (planets_.empty() || contains(Anomaly::GravityRift)) {
      return 0.0f;
    } else {
      const float score{1.5f * std::pow(static_cast<float>(2 + highest_planet_resources()), std::sqrt(1.618034f))};
      if (contains(Anomaly::Nebula)) {
        return 0.25f * score;
      } else {
        return score;
      }
    }
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

  std::string name() const noexcept {
    std::string text;
    int8_t counter{0};
    for (const Planet& planet : planets_) {
      if (counter > 0) {
        text += "  +  ";
      }
      text += planet.name();
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

  std::string print() const noexcept {
    return "#" + id_ + ":  " + name();
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

private:

  /// \brief Each system must have a unique ID.
  std::string id_{};

  GameVersion game_version_{GameVersion::BaseGame};

  SystemCategory category_{SystemCategory::Planetary};

  std::set<Planet, Planet::sort_by_name> planets_;

  std::set<Anomaly> anomalies_;

  std::set<Wormhole> wormholes_;

  /// \brief If this system is a home system or the Creuss Gate system, this is its faction.
  std::optional<Faction> faction_;

  float score_{0.0f};

  void check_number_of_planets() const {
    if (planets_.size() > 3) {
      error("A system cannot contain more than 3 planets.");
    }
  }

  void initialize_score() noexcept {
    score_ = individual_planet_scores() + number_of_planets_score() + anomalies_score() + wormholes_score();
  }

  /// \brief The base system score is the sum of the individual planet scores.
  float individual_planet_scores() const noexcept {
    float score{0.0f};
    for (const Planet& planet : planets_) {
      score += planet.score();
    }
    return score;
  }

  /// \brief It is preferable to have multiple planets in one system due to scoring objectives, command token efficiency, and ease of defending the space area.
  float number_of_planets_score() const noexcept {
    const std::size_t number_of_planets_{planets_.size()};
    if (number_of_planets_ == 1) {
      return 1.0f * number_of_planets_;
    } else if (number_of_planets_ == 2) {
      return 2.0f * number_of_planets_;
    } else if (number_of_planets_ == 3) {
      return 3.0f * number_of_planets_;
    }
    return 0.0f;
  }

  /// \brief Some anomalies are generally beneficial or harmful, whereas others depend heavily on their positioning.
  float anomalies_score() const noexcept {
    float total{0.0f};
    if (contains(Anomaly::AsteroidField)) {
      // If you have Antimass Deflectors researched, this is effectively an empty system.
      // If you do not, this is worse because it prevents movement and therefore reduces your options. Generally bad.
      // The Clan of Saar strongly prefers these due to their faction technology.
      total += -1.0f;
    }
    if (contains(Anomaly::GravityRift)) {
      // Gives extra movement and therefore extra options, but might destroy your ships. Generally beneficial.
      total += 0.5f;
    }
    if (contains(Anomaly::Nebula)) {
      // Better defense, but slows movement. Slightly worse than neutral.
      // The Empyrean strongly prefers these due to their faction ability.
      total += -0.5f;
    }
    if (contains(Anomaly::Supernova)) {
      // Prevents movement and therefore reduces your options. Generally bad.
      // The Embers of Muaat strongly prefer these due to their faction ability and technology.
      total += -1.5f;
    }
    return total;
  }

  /// \brief Wormholes are generally beneficial because they provide additional movement options and lead to the Wormhole Nexus.
  float wormholes_score() const noexcept {
    if (contains_one_or_more_wormholes()) {
      return 1.25f;
    }
    return 0.0f;
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
