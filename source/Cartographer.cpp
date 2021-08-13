#include "Instructions.hpp"
#include "SelectedSystems.hpp"

int main(int argc, char *argv[]) {
  const ti4cartographer::Instructions instructions{argc, argv};
  const ti4cartographer::SelectedSystems selected_systems{ti4cartographer::GameVersion::ProphecyOfKingsExpansion, 3, 2};
  ti4cartographer::message(selected_systems.print());
  return EXIT_SUCCESS;
}
