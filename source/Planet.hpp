#pragma once

#include "LegendaryPlanet.hpp"
#include "PlanetTrait.hpp"
#include "TechnologyType.hpp"

namespace TI4Cartographer {

class Planet {

public:

  Planet() noexcept {}

  Planet(
    const std::string& name,
    const int8_t resources,
    const int8_t influence,
    const std::optional<TechnologyType>& technology_specialty,
    const std::optional<PlanetTrait>& trait,
    const std::optional<LegendaryPlanet>& legendary
  ) noexcept :
    name_(name),
    resources_(resources),
    influence_(influence),
    technology_specialty_(technology_specialty),
    trait_(trait),
    legendary_(legendary)
  {
    initialize_score();
  }

  const std::string& name() const noexcept {
    return name_;
  }

  int8_t resources() const noexcept {
    return resources_;
  }

  int8_t influence() const noexcept {
    return influence_;
  }

  const std::optional<TechnologyType>& technology_specialty() const noexcept {
    return technology_specialty_;
  }

  const std::optional<PlanetTrait>& trait() const noexcept {
    return trait_;
  }

  const std::optional<LegendaryPlanet>& legendary() const noexcept {
    return legendary_;
  }

  float score() const noexcept {
    return score_;
  }

  bool is_legendary() const noexcept {
    return legendary_.has_value();
  }

  int8_t useful_resources() const noexcept {
    if (resources_ > influence_) {
      return resources_;
    } else {
      return 0;
    }
  }

  int8_t useful_influence() const noexcept {
    if (influence_ >= resources_) {
      return influence_;
    } else {
      return 0;
    }
  }

  std::string print() const noexcept {
    std::string text{name_};
    text += " (" + std::to_string(resources_) + "/" + std::to_string(influence_);
    if (technology_specialty_.has_value()) {
      text += "/" + abbreviation(technology_specialty_);
    }
    if (trait_.has_value()) {
      text += " " + abbreviation(trait_);
    }
    if (is_legendary()) {
      text += " Legendary";
    }
    text += ")";
    return text;
  }

  struct sort_by_name {
    bool operator()(const Planet& planet_1, const Planet& planet_2) const noexcept {
      return planet_1.name_ < planet_2.name_;
    }
  };

private:

  /// \brief Within a system, each planet must have a unique name.
  std::string name_;

  int8_t resources_{0};

  int8_t influence_{0};

  std::optional<TechnologyType> technology_specialty_;

  std::optional<PlanetTrait> trait_;

  std::optional<LegendaryPlanet> legendary_;

  float score_{0.0};

  void initialize_score() noexcept {
    score_ = utility_score() + voting_score() + technology_specialty_score() + trait_score() + legendary_objective_score() + legendary_component_action_score();
  }

  /// \brief This is the main component of a planet's score: it is what the planet is used for when it is exhausted.
  float utility_score() const noexcept {
    return static_cast<float>(std::max(resources_, influence_));
  }

  /// \brief High influence planets are useful for voting during the Agenda phase.
  float voting_score() const noexcept {
    return 0.25 * influence_;
  }

  /// \brief Planets with a propulsion technology specialty are preferable over other technology specialties, which are in turn preferable to no technology specialty.
  float technology_specialty_score() const noexcept {
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

  /// \brief Cultural planets are slightly preferable to hazardous planets, which are in turn preferable to industrial planets.
  float trait_score() const noexcept {
    if (trait_.has_value()) {
      switch (trait_.value()) {
        case PlanetTrait::Cultural:
          return 0.5;
          break;
        case PlanetTrait::Hazardous:
          return 0.3;
          break;
        case PlanetTrait::Industrial:
          return 0.1;
          break;
      }
    }
    return 0.0;
  }

  /// \brief Legendary planets are relevant to scoring objectives.
  float legendary_objective_score() const noexcept {
    if (is_legendary()) {
      return 2.0;
    }
    return 0.0;
  }

  /// \brief Legendary planets grant bonus component actions. Some are preferable to others.
  float legendary_component_action_score() const noexcept {
    if (legendary_.has_value()) {
      switch (legendary_.value()) {
        case LegendaryPlanet::HopesEnd:
          return 2.5;
          break;
        case LegendaryPlanet::Mallice:
          return 2.5;
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

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::Planet> {
    size_t operator()(const TI4Cartographer::Planet& planet) const {
      return hash<std::string>()(planet.name());
    }
  };

} // namespace std
