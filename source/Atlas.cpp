#include "Systems.hpp"

namespace ti4cartographer {

void print_atlas() noexcept {
  std::vector<SystemIdAndScore> system_ids_and_scores;
  for (const System& system : Systems) {
    if (system.category() == SystemCategory::Planetary || system.category() == SystemCategory::AnomalyWormholeEmpty) {
      system_ids_and_scores.push_back({system.id(), system.score()});
    }
  }
  std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_descending());
  message(Separator);
  message("Twilight Imperium 4th Edition Atlas");
  message("Compiled on: " + CompilationDateAndTime);
  message("Systems Ranked from Best to Worst:");
  for (const SystemIdAndScore& system_id_and_score : system_ids_and_scores) {
    const std::unordered_set<System>::const_iterator found{Systems.find({system_id_and_score.id()})};
    if (found != Systems.cend()) {
      message(score_to_string(system_id_and_score.score()) + "  " + found->print());
    }
  }
  message(Separator);
}

} // namespace ti4cartographer

int main(int argc, char *argv[]) {
  ti4cartographer::print_atlas();
  return EXIT_SUCCESS;
}
