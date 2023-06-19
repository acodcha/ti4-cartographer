#include "Systems.hpp"

namespace TI4Cartographer {

using SystemIdsAndScores = std::vector<SystemIdAndScore>;

struct Statistics {
public:
  Statistics(const SystemIdsAndScores& sorted_system_ids_and_scores) noexcept {
    for (const SystemIdAndScore& system_id_and_score :
         sorted_system_ids_and_scores) {
      const std::unordered_set<System>::const_iterator found{
        Systems.find({system_id_and_score.id()})};

      if (found != Systems.cend()) {
        verbose_message(
          score_to_string(system_id_and_score.score()) + "  " + found->print());

        if (found->category() == SystemCategory::Planetary) {
          ++number_of_planetary_systems;

          for (const Planet& planet : found->planets()) {
            ++planetary_system_planets;
            planetary_system_resources += planet.useful_resources();
            planetary_system_influence += planet.useful_influence();

            if (planet.technology_specialty().has_value()) {
              ++planetary_system_technology_specialties;
            }
          }
        } else if (found->category() == SystemCategory::AnomalyWormholeEmpty) {
          ++number_of_anomaly_wormhole_empty_systems;

          for (const Planet& planet : found->planets()) {
            ++anomaly_wormhole_empty_system_planets;
            anomaly_wormhole_empty_system_resources +=
              planet.useful_resources();
            anomaly_wormhole_empty_system_influence +=
              planet.useful_influence();

            if (planet.technology_specialty().has_value()) {
              ++anomaly_wormhole_empty_system_technology_specialties;
            }
          }
        }
      }
    }

    planetary_system_average_planets =
      static_cast<float>(planetary_system_planets)
      / number_of_planetary_systems;

    planetary_system_average_useful_resources =
      static_cast<float>(planetary_system_resources)
      / number_of_planetary_systems;

    planetary_system_average_useful_influence =
      static_cast<float>(planetary_system_influence)
      / number_of_planetary_systems;

    planetary_system_average_technology_specialties =
      static_cast<float>(planetary_system_technology_specialties)
      / number_of_planetary_systems;

    anomaly_wormhole_empty_system_average_planets =
      static_cast<float>(anomaly_wormhole_empty_system_planets)
      / number_of_anomaly_wormhole_empty_systems;

    anomaly_wormhole_empty_system_average_useful_resources =
      static_cast<float>(anomaly_wormhole_empty_system_resources)
      / number_of_anomaly_wormhole_empty_systems;

    anomaly_wormhole_empty_system_average_useful_influence =
      static_cast<float>(anomaly_wormhole_empty_system_influence)
      / number_of_anomaly_wormhole_empty_systems;

    anomaly_wormhole_empty_system_average_technology_specialties =
      static_cast<float>(anomaly_wormhole_empty_system_technology_specialties)
      / number_of_anomaly_wormhole_empty_systems;
  }

  int8_t number_of_planetary_systems{0};

  int16_t planetary_system_planets{0};
  int16_t planetary_system_resources{0};
  int16_t planetary_system_influence{0};
  int16_t planetary_system_technology_specialties{0};

  int8_t number_of_anomaly_wormhole_empty_systems{0};

  int16_t anomaly_wormhole_empty_system_planets{0};
  int16_t anomaly_wormhole_empty_system_resources{0};
  int16_t anomaly_wormhole_empty_system_influence{0};
  int16_t anomaly_wormhole_empty_system_technology_specialties{0};

  float planetary_system_average_planets;
  float planetary_system_average_useful_resources;
  float planetary_system_average_useful_influence;
  float planetary_system_average_technology_specialties;

  float anomaly_wormhole_empty_system_average_planets;
  float anomaly_wormhole_empty_system_average_useful_resources;
  float anomaly_wormhole_empty_system_average_useful_influence;
  float anomaly_wormhole_empty_system_average_technology_specialties;
};

SystemIdsAndScores InitializeSortedSystemIdsAndScores() noexcept {
  SystemIdsAndScores system_ids_and_scores;

  for (const System& system : Systems) {
    if (system.category() == SystemCategory::Planetary
        || system.category() == SystemCategory::AnomalyWormholeEmpty) {
      system_ids_and_scores.push_back({system.id(), system.score()});
    }
  }

  std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(),
            SystemIdAndScore::sort_by_descending_score());

  return system_ids_and_scores;
}

void PrintAtlas() noexcept {
  verbose_message(Separator);
  verbose_message("Twilight Imperium 4th Edition Atlas");
  verbose_message("Compiled: " + CompilationDateAndTime);
  verbose_message(
    "Ranks systems from best to worst. This ranking only takes into account "
    "the individual systems by themselves, and does not account for position "
    "on the game board, suitability as a forward outpost, or other "
    "interactions; such considerations are handled by the ti4cartographer "
    "program.");
  verbose_message("Systems ranked from best to worst:");

  const std::vector<SystemIdAndScore> sorted_system_ids_and_scores =
    InitializeSortedSystemIdsAndScores();

  const Statistics statistics{sorted_system_ids_and_scores};

  verbose_message(
    "The average planetary system contains "
    + real_number_to_string(statistics.planetary_system_average_planets)
    + " planets worth an average of "
    + real_number_to_string(
      statistics.planetary_system_average_useful_resources)
    + " useful resources per system and "
    + real_number_to_string(
      statistics.planetary_system_average_useful_influence)
    + " useful influence per system with an average of "
    + real_number_to_string(
      statistics.planetary_system_average_technology_specialties)
    + " technology specialties per system.");

  verbose_message(
    "The average anomaly/wormhole/empty system contains "
    + real_number_to_string(
      statistics.anomaly_wormhole_empty_system_average_planets)
    + " planets worth an average of "
    + real_number_to_string(
      statistics.anomaly_wormhole_empty_system_average_useful_resources)
    + " useful resources per system and "
    + real_number_to_string(
      statistics.anomaly_wormhole_empty_system_average_useful_influence)
    + " useful influence per system with an average of "
    + real_number_to_string(
      statistics.anomaly_wormhole_empty_system_average_technology_specialties)
    + " technology specialties per system.");

  verbose_message(Separator);
}

}  // namespace TI4Cartographer

int main(int argc, char* argv[]) {
  TI4Cartographer::PrintAtlas();
  return EXIT_SUCCESS;
}
