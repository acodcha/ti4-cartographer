#pragma once

#include "Aggressions.hpp"
#include "GameVersions.hpp"
#include "Layouts.hpp"

namespace TI4Cartographer {

/// \brief Namespace listing the program's command-line argument keywords.
namespace Arguments {

const std::string QuietMode{"--quiet"};

const std::string UsageInformation{"--help"};

const std::string NumberOfPlayersKey{"--players"};

const std::string NumberOfPlayersPattern{NumberOfPlayersKey + " <number>"};

const std::string GameVersionKey{"--version"};

const std::string GameVersionPattern{GameVersionKey + " <type>"};

const std::string LayoutKey{"--layout"};

const std::string LayoutPattern{LayoutKey + " <type>"};

const std::string AggressionKey{"--aggression"};

const std::string AggressionPattern{AggressionKey + " <amount>"};

const std::string NumberOfIterationsKey{"--iterations"};

const std::string NumberOfIterationsPattern{NumberOfIterationsKey + " <number>"};

} // namespace Arguments

/// \brief Parser and organizer of the program's command-line arguments.
class Instructions {

public:

  Instructions(int argc, char *argv[]) : executable_name_(argv[0]) {
    assign_arguments(argc, argv);
    initialize();
    message_header_information();
    message("Command: " + command());
    message_start_information();
  }

  GameVersion game_version() const noexcept {
    return game_version_;
  }

  Layout layout() const noexcept {
    return layout_;
  }

  Aggression aggression() const noexcept {
    return aggression_;
  }

  uint64_t maximum_number_of_iterations() const noexcept {
    return maximum_number_of_iterations_;
  }

private:

  std::string executable_name_;

  std::vector<std::string> arguments_;

  GameVersion game_version_{GameVersion::ProphecyOfKingsExpansion};

  Layout layout_{Layout::Players6};

  Aggression aggression_{Aggression::Medium};

  uint64_t maximum_number_of_iterations_{DefaultMaximumNumberOfIterations};

  void assign_arguments(int argc, char *argv[]) noexcept {
    if (argc > 1) {
      arguments_.assign(argv + 1, argv + argc);
    } else {
      message_header_information();
      message_usage_information();
      exit(EXIT_SUCCESS);
    }
  }

  void message_usage_information_and_error(const std::string text) const {
    message_header_information();
    message_usage_information();
    error(text);
  }

  void initialize() {
    uint8_t number_of_players{6};
    std::string layout_string{"regular"};
    for (std::vector<std::string>::const_iterator argument = arguments_.cbegin(); argument < arguments_.cend(); ++argument) {
      if (*argument == Arguments::QuietMode) {
        Communicator::get().initialize(CommunicatorMode::Quiet);
      } else if (*argument == Arguments::UsageInformation) {
        message_header_information();
        message_usage_information();
        exit(EXIT_SUCCESS);
      } else if (*argument == Arguments::NumberOfPlayersKey && argument + 1 < arguments_.cend()) {
        number_of_players = static_cast<uint8_t>(std::stoi(*(argument + 1)));
        check_number_of_players(number_of_players);
      } else if (*argument == Arguments::GameVersionKey && argument + 1 < arguments_.cend()) {
        initialize_game_version(*(argument + 1));
      } else if (*argument == Arguments::LayoutKey && argument + 1 < arguments_.cend()) {
        layout_string = *(argument + 1);
      } else if (*argument == Arguments::AggressionKey && argument + 1 < arguments_.cend()) {
        initialize_aggression(*(argument + 1));
      } else if (*argument == Arguments::NumberOfIterationsKey && argument + 1 < arguments_.cend()) {
        initialize_maximum_number_of_iterations(*(argument + 1));
      }
    }
    Communicator::get().initialize(CommunicatorMode::Verbose);
    check_game_version(number_of_players);
    initialize_layout(number_of_players, layout_string);
  }

  void check_number_of_players(const uint8_t number_of_players) const {
    if (number_of_players < 2 || number_of_players > 8) {
      message_usage_information_and_error("The number of players must be 2-8.");
    }
  }

  void initialize_game_version(const std::string game_version) {
    const std::optional<GameVersion> found{type<GameVersion>(game_version)};
    if (found.has_value()) {
      game_version_ = found.value();
    } else {
      message_usage_information_and_error("Unknown game version: " + game_version);
    }
  }

  void initialize_aggression(const std::string aggression) {
    const std::optional<Aggression> found{type<Aggression>(aggression)};
    if (found.has_value()) {
      aggression_ = found.value();
    } else {
      message_usage_information_and_error("Unknown board aggression: " + aggression);
    }
  }

  void initialize_maximum_number_of_iterations(const std::string maximum_number_of_iterations) {
    maximum_number_of_iterations_ = static_cast<uint64_t>(std::stoull(maximum_number_of_iterations));
    if (maximum_number_of_iterations_ == 0) {
      message_usage_information_and_error("The number of iterations must be greater than zero.");
    }
  }

  void check_game_version(const uint8_t number_of_players) const {
    if (number_of_players >= 7 && game_version_ == GameVersion::BaseGame) {
      message_usage_information_and_error("7 and 8 player games require the " + label(GameVersion::ProphecyOfKingsExpansion) + ".");
    }
  }

  void initialize_layout(const uint8_t number_of_players, const std::string& layout_string) {
    const std::string label{std::to_string(number_of_players) + "players" + lowercase(remove_non_alphanumeric_characters(layout_string))};
    const std::optional<Layout> found{type<Layout>(label)};
    if (found.has_value()) {
      layout_ = found.value();
    } else {
      message_usage_information_and_error("Unknown board layout: " + layout_string);
    }
  }

  void message_header_information() const noexcept {
    message(Separator);
    message(ProgramName);
    message("Generates randomized balanced boards for the Twilight Imperium 4th Edition board game.");
    message("Compiled: " + CompilationDateAndTime);
  }

  void message_usage_information() const noexcept {
    const std::string space{"  "};
    message("Usage:");
    message(space + executable_name_ + " " + Arguments::NumberOfPlayersPattern + " [" + Arguments::GameVersionPattern + "] [" + Arguments::LayoutPattern + "] [" + Arguments::AggressionPattern + "] [" + Arguments::NumberOfIterationsPattern + "] [" + Arguments::QuietMode + "]");
    const uint_least64_t length{std::max({
      Arguments::UsageInformation.length(),
      Arguments::NumberOfPlayersPattern.length(),
      Arguments::GameVersionPattern.length(),
      Arguments::LayoutPattern.length(),
      Arguments::AggressionPattern.length(),
      Arguments::NumberOfIterationsPattern.length(),
      Arguments::QuietMode.length()
    })};
    message("Arguments:");
    message(space + pad_to_length(Arguments::UsageInformation, length) + space + "Displays this information and exits.");
    message(space + pad_to_length(Arguments::NumberOfPlayersPattern, length) + space + "Required. Choices are 2-8. Specifies the number of players.");
    message(space + pad_to_length(Arguments::GameVersionPattern, length) + space + "Optional. Choices are base or expansion. The default is expansion. Determines whether the system tiles from the Prophecy of Kings expansion can be used. Note that 7 and 8 player games require the expansion.");
    message(space + pad_to_length(Arguments::LayoutPattern, length) + space + "Optional. Choices vary by number of players, but typically include regular, small, or large. The default is regular. Specifies the board layout.");
    message(space + space + "2 players: regular");
    message(space + space + "3 players: regular, small, or large");
    message(space + space + "4 players: regular or large");
    message(space + space + "5 players: regular, small, or large");
    message(space + space + "6 players: regular");
    message(space + space + "7 players: regular or large");
    message(space + space + "8 players: regular or large");
    message(space + pad_to_length(Arguments::AggressionPattern, length) + space + "Optional. Choices are very-high, high, medium, low, or very-low. The default is medium. Specifies the degree of expected aggression resulting from the placement of systems on the board. Higher aggression places better systems at equidistant positions compared to the systems in each player's slice, whereas lower aggression does the opposite.");
    message(space + pad_to_length(Arguments::NumberOfIterationsPattern, length) + space + "Optional. The default is " + std::to_string(DefaultMaximumNumberOfIterations) + ". Specifies the number of board layout iterations.");
    message(space + pad_to_length(Arguments::QuietMode, length) + space + "Optional. Activates quiet mode, where the only console output is the generated board's Tabletop Simulator string.");
    message("");
  }

  std::string command() const noexcept {
    std::string text{executable_name_};
    for (const std::string& argument : arguments_) {
      text += " " + argument;
    }
    return text;
  }

  void message_start_information() const noexcept {
    message("The number of players and board layout is: " + label(layout_));
    message("The game version is: " + label(game_version_));
    message("The aggression is: " + label(aggression_));
    message("The number of iterations is: " + std::to_string(maximum_number_of_iterations_));
  }

}; // class Instructions

} // namespace TI4Cartographer
