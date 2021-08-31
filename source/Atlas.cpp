#include "Systems.hpp"

namespace TI4Cartographer {

void print_atlas() noexcept {
  std::vector<SystemIdAndScore> system_ids_and_scores;
  for (const System& system : Systems) {
    if (system.category() == SystemCategory::Planetary || system.category() == SystemCategory::AnomalyWormholeEmpty) {
      system_ids_and_scores.push_back({system.id(), system.score()});
    }
  }
  std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_by_descending_score());
  verbose_message(Separator);
  verbose_message("Twilight Imperium 4th Edition Atlas");
  verbose_message("Compiled: " + CompilationDateAndTime);
  verbose_message("Ranks systems from best to worst. This ranking only takes into account the");
  verbose_message("individual systems by themselves, and does not account for position on the");
  verbose_message("game board, suitability as a forward outpost, or other interactions; such");
  verbose_message("considerations are handled by the ti4cartographer program.");
  verbose_message("Systems ranked from best to worst:");
  for (const SystemIdAndScore& system_id_and_score : system_ids_and_scores) {
    const std::unordered_set<System>::const_iterator found{Systems.find({system_id_and_score.id()})};
    if (found != Systems.cend()) {
      verbose_message(score_to_string(system_id_and_score.score()) + "  " + found->print());
    }
  }
  verbose_message(Separator);
}

} // namespace TI4Cartographer

int main(int argc, char *argv[]) {
  TI4Cartographer::print_atlas();
  return EXIT_SUCCESS;
}
