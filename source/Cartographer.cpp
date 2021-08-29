#include "BoardGenerator.hpp"
#include "Instructions.hpp"
#include "SelectedSystemIds.hpp"

int main(int argc, char *argv[]) {
  const TI4Cartographer::Chronometre chronometre;
  const TI4Cartographer::Instructions instructions{argc, argv};
  const TI4Cartographer::SelectedSystemIds selected_system_ids{instructions.game_version(), instructions.layout()};
  const TI4Cartographer::BoardGenerator board_generator{chronometre, instructions.layout(), instructions.aggression(), instructions.maximum_number_of_iterations(), selected_system_ids};
  return EXIT_SUCCESS;
}
