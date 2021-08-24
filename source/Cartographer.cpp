#include "BoardGenerator.hpp"
#include "Instructions.hpp"
#include "SelectedSystemIds.hpp"

namespace TI4Cartographer {

void generate_board(const Chronometre& chronometre, const Instructions& instructions, const SelectedSystemIds& selected_system_ids) {
  switch (instructions.layout()) {
    case Layout::Players2:
      // TODO.
      break;
    case Layout::Players3Regular:
      // TODO.
      break;
    case Layout::Players3Small:
      // TODO.
      break;
    case Layout::Players3Large:
      // TODO.
      break;
    case Layout::Players4Regular:
      // TODO.
      break;
    case Layout::Players4Large:
      // TODO.
      break;
    case Layout::Players5Regular:
      // TODO.
      break;
    case Layout::Players5Small:
      // TODO.
      break;
    case Layout::Players5Large:
      // TODO.
      break;
    case Layout::Players6:
      {
        const BoardGenerator<Layout::Players6> board{chronometre, instructions.aggression(), instructions.maximum_number_of_iterations(), selected_system_ids};
      }
      break;
    case Layout::Players7Regular:
      // TODO.
      break;
    case Layout::Players7Large:
      // TODO.
      break;
    case Layout::Players8Regular:
      // TODO.
      break;
    case Layout::Players8Large:
      // TODO.
      break;
  }
}

} // namespace TI4Cartographer

int main(int argc, char *argv[]) {
  const TI4Cartographer::Chronometre chronometre;
  const TI4Cartographer::Instructions instructions{argc, argv};
  const TI4Cartographer::SelectedSystemIds selected_system_ids{instructions.game_version(), instructions.layout()};
  TI4Cartographer::generate_board(chronometre, instructions, selected_system_ids);
  return EXIT_SUCCESS;
}
