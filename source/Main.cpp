#include "Catalog.hpp"

int main(int argc, char *argv[]) {
  const TI4MapGenerator::Catalog catalog{TI4MapGenerator::GameVersion::ProphecyOfKingsExpansion, 3, 2};
  TI4MapGenerator::message(catalog.print());
  return EXIT_SUCCESS;
}
