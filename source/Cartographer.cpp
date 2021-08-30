#include "Board.hpp"
#include "Instructions.hpp"
#include "SelectedSystemIds.hpp"

int main(int argc, char *argv[]) {
  const TI4Cartographer::Chronometre chronometre;
  const TI4Cartographer::Instructions instructions{argc, argv};
  const TI4Cartographer::Board board{chronometre, instructions.game_version(), instructions.layout(), instructions.aggression(), instructions.maximum_number_of_iterations()};
  TI4Cartographer::message("End of " + TI4Cartographer::ProgramName + ".");
  TI4Cartographer::message(TI4Cartographer::Separator);
  return EXIT_SUCCESS;
}
