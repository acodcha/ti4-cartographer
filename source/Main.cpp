#include "Systems.hpp"

int main(int argc, char *argv[]) {
  const TI4Cartographer::SelectedSystems selected_systems{TI4Cartographer::GameVersion::ProphecyOfKingsExpansion, 3, 2};
  TI4Cartographer::message(selected_systems.print());
  return EXIT_SUCCESS;
}
