#pragma once

#include "Base.hpp"

namespace TI4MapGenerator {

class Planet {

public:

  Planet() noexcept {}

  Planet(
    const std::string& name,
    const uint8_t resources,
    const uint8_t influence,
    const std::optional<PlanetTrait>& trait = {},
    const std::optional<TechnologyType>& technology_specialty = {},
    const std::optional<LegendaryPlanet>& legendary_planet = {}
  ) noexcept :
    name_(name),
    resources_(resources),
    influence_(influence),
    trait_(trait),
    technology_specialty_(technology_specialty),
    legendary_planet_(legendary_planet)
  {}

  const std::string& name() const noexcept {
    return name_;
  }

  uint8_t resources() const noexcept {
    return resources_;
  }

  uint8_t influence() const noexcept {
    return influence_;
  }

  const std::optional<PlanetTrait>& trait() const noexcept {
    return trait_;
  }

  const std::optional<TechnologyType>& technology_specialty() const noexcept {
    return technology_specialty_;
  }

  const std::optional<LegendaryPlanet>& legendary_planet() const noexcept {
    return legendary_planet_;
  }

  bool is_legendary() const noexcept {
    return legendary_planet_.has_value();
  }

  double score() const noexcept {
    return utility_score() + voting_score() + trait_score() + technology_specialty_score() + legendary_planet_objective_score() + legendary_planet_component_action_score();
  }

  std::string print() const noexcept {
    std::string text{name_};
    text += " (" + std::to_string(resources_) + "/" + std::to_string(influence_);
    if (technology_specialty_.has_value()) {
      text += "/" + abbreviation(technology_specialty_);
    }
    if (trait_.has_value()) {
      text += " " + label(trait_);
    }
    text += ")";
    return text;
  }

  struct sort_by_name {
    bool operator()(const Planet& planet_1, const Planet& planet_2) const noexcept {
      return planet_1.name_ < planet_2.name_;
    }
  };

protected:

  /// \brief Within a system, each planet must have a unique name.
  std::string name_;

  uint8_t resources_{0};

  uint8_t influence_{0};

  std::optional<PlanetTrait> trait_;

  std::optional<TechnologyType> technology_specialty_;

  std::optional<LegendaryPlanet> legendary_planet_;

  /// \brief This is the main component of a planet's score: it is what the planet is used for when it is exhausted.
  double utility_score() const noexcept {
    return std::max(resources_, influence_);
  }

  /// \brief High influence planets are useful for voting during the Agenda phase.
  double voting_score() const noexcept {
    return 0.5 * influence_;
  }

  /// \brief Cultural planets are slightly preferable to hazardous planets, which are in turn preferable to industrial planets.
  double trait_score() const noexcept {
    if (trait_.has_value()) {
      switch (trait_.value()) {
        case PlanetTrait::Cultural:
          return 0.5;
          break;
        case PlanetTrait::Hazardous:
          return 0.4;
          break;
        case PlanetTrait::Industrial:
          return 0.2;
          break;
      }
    }
    return 0.0;
  }

  /// \brief Planets with a propulsion technology specialty are preferable over other technology specialties, which are in turn preferable to no technology specialty.
  double technology_specialty_score() const noexcept {
    if (technology_specialty_.has_value()) {
      switch (technology_specialty_.value()) {
        case TechnologyType::Propulsion:
          return 2.0;
          break;
        case TechnologyType::Biotic:
          return 1.0;
          break;
        case TechnologyType::Cybernetic:
          return 1.0;
          break;
        case TechnologyType::Warfare:
          return 1.0;
          break;
      }
    }
    return 0.0;
  }

  /// \brief Legendary planets are relevant to scoring objectives.
  double legendary_planet_objective_score() const noexcept {
    if (is_legendary()) {
      return 2.0;
    }
    return 0.0;
  }

  /// \brief Legendary planets grant bonus component actions. Some are preferable to others.
  double legendary_planet_component_action_score() const noexcept {
    if (legendary_planet_.has_value()) {
      switch (legendary_planet_.value()) {
        case LegendaryPlanet::HopesEnd:
          return 3.0;
          break;
        case LegendaryPlanet::Mallice:
          return 3.0;
          break;
        case LegendaryPlanet::Mirage:
          return 1.5;
          break;
        case LegendaryPlanet::Primor:
          return 2.0;
          break;
      }
    }
    return 0.0;
  }

}; // class Planet

} // namespace TI4MapGenerator

namespace std {

  template <> struct hash<TI4MapGenerator::Planet> {
    size_t operator()(const TI4MapGenerator::Planet& planet) const {
      return hash<std::string>()(planet.name());
    }
  };

} // namespace std
