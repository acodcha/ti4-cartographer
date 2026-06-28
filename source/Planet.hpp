#pragma once

#include "LegendaryPlanet.hpp"
#include "PlanetTrait.hpp"
#include "TechnologyType.hpp"

namespace TI4Cartographer {

class Planet {
public:
  Planet() noexcept {}

  Planet(const std::string& name, const int8_t resources,
         const int8_t influence,
         const std::vector<TechnologyType>& technology_specialties,
         const std::set<PlanetTrait>& traits,
         const std::optional<LegendaryPlanet>& legendary) noexcept
    : name_(name), resources_(resources), influence_(influence),
      technology_specialties_(technology_specialties), traits_(traits),
      legendary_(legendary) {
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

  const std::vector<TechnologyType>& technology_specialties() const noexcept {
    return technology_specialties_;
  }

  const std::set<PlanetTrait>& traits() const noexcept {
    return traits_;
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
    text +=
        " (" + std::to_string(resources_) + "/" + std::to_string(influence_);
    if (!technology_specialties_.empty()) {
      text += "/";
    }
    for (const TechnologyType technology_specialty : technology_specialties_) {
      text += abbreviation(technology_specialty);
    }
    if (!traits_.empty()) {
      text += " ";
    }
    for (const PlanetTrait trait : traits_) {
      text += abbreviation(trait);
    }
    if (is_legendary()) {
      text += " Legendary";
    }
    text += ")";
    return text;
  }

  struct sort_by_name {
    bool operator()(
        const Planet& planet_1, const Planet& planet_2) const noexcept {
      return planet_1.name_ < planet_2.name_;
    }
  };

private:
  /// \brief Within a system, each planet must have a unique name.
  std::string name_;

  int8_t resources_{0};

  int8_t influence_{0};

  std::vector<TechnologyType> technology_specialties_;

  std::set<PlanetTrait> traits_;

  std::optional<LegendaryPlanet> legendary_;

  float score_{0.0};

  void initialize_score() noexcept {
    score_ = utility_score() + voting_score() + technology_specialty_score()
             + trait_score() + legendary_objective_score()
             + legendary_component_action_score();
  }

  /// \brief This is the main component of a planet's score: it is what the
  /// planet is used for when it is exhausted.
  float utility_score() const noexcept {
    return static_cast<float>(std::max(resources_, influence_));
  }

  /// \brief High influence planets are useful for voting during the Agenda
  /// phase.
  float voting_score() const noexcept {
    return 0.25f * influence_;
  }

  /// \brief Planets with a propulsion technology specialty are preferable over
  /// other technology specialties, which are in turn preferable to no
  /// technology specialty.
  float technology_specialty_score() const noexcept {
    float best_score{0.0f};
    for (const TechnologyType technology_specialty : technology_specialties_) {
      switch (technology_specialty) {
        case TechnologyType::Propulsion:
          if (best_score < 2.0f) {
            best_score = 2.0f;
          }
          break;
        case TechnologyType::Biotic:
          if (best_score < 1.0f) {
            best_score = 1.0f;
          }
          break;
        case TechnologyType::Cybernetic:
          if (best_score < 1.0f) {
            best_score = 1.0f;
          }
          break;
        case TechnologyType::Warfare:
          if (best_score < 1.0f) {
            best_score = 1.0f;
          }
          break;
      }
    }
    if (technology_specialties_.size() >= 2) {
      best_score += 0.5f;
    }
    return best_score;
  }

  /// \brief Cultural planets are slightly preferable to hazardous planets,
  /// which are in turn preferable to industrial planets, which are in turn
  /// preferable to space stations.
  float trait_score() const noexcept {
    float best_score{0.0f};
    for (const PlanetTrait trait : traits_) {
      switch (trait) {
        case PlanetTrait::Cultural:
          if (best_score < 0.15f) {
            best_score = 0.15f;
          }
          break;
        case PlanetTrait::Hazardous:
          if (best_score < 0.1f) {
            best_score = 0.1f;
          }
          break;
        case PlanetTrait::Industrial:
          if (best_score < 0.05f) {
            best_score = 0.05f;
          }
          break;
        case PlanetTrait::SpaceStation:
          if (best_score < 0.0f) {
            best_score = 0.0f;
          }
          break;
        case PlanetTrait::Relic:
          if (best_score < 1.0f) {
            best_score = 1.0f;
          }
          break;
      }
    }
    return best_score;
  }

  /// \brief Legendary planets are relevant to scoring objectives.
  float legendary_objective_score() const noexcept {
    if (is_legendary()) {
      return 2.0f;
    }
    return 0.0f;
  }

  /// \brief Legendary planets grant bonus component actions. Some are
  /// preferable to others.
  float legendary_component_action_score() const noexcept {
    if (legendary_.has_value()) {
      switch (legendary_.value()) {
        case LegendaryPlanet::HopesEnd:
          return 2.5f;
          break;
        case LegendaryPlanet::Mallice:
          return 2.0f;
          break;
        case LegendaryPlanet::Mirage:
          return 1.0f;
          break;
        case LegendaryPlanet::Primor:
          return 1.5f;
          break;
        case LegendaryPlanet::ThundersEdge:
          return 3.0f;
          break;
        case LegendaryPlanet::Faunus:
          return 1.5f;
          break;
        case LegendaryPlanet::Garbozia:
          return 2.5f;
          break;
        case LegendaryPlanet::Emelpar:
          return 2.0f;
          break;
        case LegendaryPlanet::Tempesta:
          return 1.5f;
          break;
        case LegendaryPlanet::MecatolRex:
          return 1.5f;
          break;
        case LegendaryPlanet::Industrex:
          return 2.0f;
          break;
        case LegendaryPlanet::Styx:
          return 3.0f;
          break;
      }
    }
    return 0.0f;
  }

};  // class Planet

}  // namespace TI4Cartographer

namespace std {

template <>
struct hash<TI4Cartographer::Planet> {
  size_t operator()(const TI4Cartographer::Planet& planet) const {
    return hash<std::string>()(planet.name());
  }
};

}  // namespace std
