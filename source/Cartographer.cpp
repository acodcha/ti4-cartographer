#include "Instructions.hpp"
#include "SelectedSystemIds.hpp"

int main(int argc, char *argv[]) {
  const ti4cartographer::Instructions instructions{argc, argv};
  const ti4cartographer::SelectedSystemIds selected_system_ids{instructions.game_version(), instructions.board_layout()};
  ti4cartographer::message(selected_system_ids.print());
  return EXIT_SUCCESS;
}
