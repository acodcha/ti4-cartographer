#pragma once

#include "BoardAggressions.hpp"
#include "BoardLayouts.hpp"
#include "GameVersions.hpp"

namespace ti4cartographer {

/// \brief Namespace listing the program's command-line argument keywords.
namespace Arguments {

const std::string UsageInformation{"--help"};

const std::string NumberOfPlayersKey{"--players"};

const std::string NumberOfPlayersPattern{NumberOfPlayersKey + " <number>"};

const std::string GameVersionKey{"--version"};

const std::string GameVersionPattern{GameVersionKey + " <type>"};

const std::string BoardLayoutKey{"--layout"};

const std::string BoardLayoutPattern{BoardLayoutKey + " <type>"};

const std::string BoardAggressionKey{"--aggression"};

const std::string BoardAggressionPattern{BoardAggressionKey + " <amount>"};

const std::string NumberOfIterationsKey{"--iterations"};

const std::string NumberOfIterationsPattern{NumberOfIterationsKey + " <number>"};

} // namespace Arguments

/// \brief Parser and organizer of the program's command-line arguments.
class Instructions {

public:

  Instructions(int argc, char *argv[]) : executable_name_(argv[0]) {
    assign_arguments(argc, argv);
    message_header_information();
    message("Command: " + command());
    initialize();
    message_start_information();
  }

  GameVersion game_version() const noexcept {
    return game_version_;
  }

  BoardLayout board_layout() const noexcept {
    return board_layout_;
  }

  BoardAggression board_aggression() const noexcept {
    return board_aggression_;
  }

  uint64_t number_of_iterations() const noexcept {
    return number_of_iterations_;
  }

protected:

  std::string executable_name_;

  std::vector<std::string> arguments_;

  /// \brief This is only needed while parsing the arguments.
  uint8_t number_of_players_{6};

  GameVersion game_version_{GameVersion::ProphecyOfKingsExpansion};

  /// \brief This is only needed while parsing the arguments.
  std::string layout_;

  BoardLayout board_layout_{BoardLayout::Players6};

  BoardAggression board_aggression_{BoardAggression::Medium};

  uint64_t number_of_iterations_{DefaultNumberOfIterations};

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
    message_usage_information();
    error(text);
  }

  void initialize() {
    for (std::vector<std::string>::const_iterator argument = arguments_.cbegin(); argument < arguments_.cend(); ++argument) {
      if (*argument == Arguments::UsageInformation) {
        message_header_information();
        message_usage_information();
        exit(EXIT_SUCCESS);
      } else if (*argument == Arguments::NumberOfPlayersKey && argument + 1 < arguments_.cend()) {
        initialize_number_of_players(*(argument + 1));
      } else if (*argument == Arguments::GameVersionKey && argument + 1 < arguments_.cend()) {
        initialize_game_version(*(argument + 1));
      } else if (*argument == Arguments::BoardLayoutKey && argument + 1 < arguments_.cend()) {
        initialize_board_layout(*(argument + 1));
      } else if (*argument == Arguments::BoardAggressionKey && argument + 1 < arguments_.cend()) {
        initialize_board_aggression(*(argument + 1));
      } else if (*argument == Arguments::NumberOfIterationsKey && argument + 1 < arguments_.cend()) {
        initialize_number_of_iterations(*(argument + 1));
      }
    }
  }

  void initialize_number_of_players(const std::string number_of_players) {
    number_of_players_ = static_cast<uint8_t>(std::stoi(number_of_players));
    if (number_of_players_ < 2 || number_of_players_ > 8) {
      message_usage_information_and_error("The number of players must be 2-8.");
    }
    switch (number_of_players_) {
      case 2:
        board_layout_ = BoardLayout::Players2;
        break;
      case 3:
        board_layout_ = BoardLayout::Players3;
        break;
      case 4:
        board_layout_ = BoardLayout::Players4Regular;
        break;
      case 5:
        board_layout_ = BoardLayout::Players5Regular;
        break;
      case 6:
        board_layout_ = BoardLayout::Players6;
        break;
      case 7:
        board_layout_ = BoardLayout::Players7Regular;
        break;
      case 8:
        board_layout_ = BoardLayout::Players8Regular;
        break;
      default:
        break;
    }
  }

  void initialize_game_version(const std::string game_version) {
    const std::optional<GameVersion> found{type<GameVersion>(game_version)};
    if (found.has_value()) {
      game_version_ = found.value();
    } else {
      message_usage_information_and_error("Unknown game version: " + game_version);
    }
    if (number_of_players_ >= 7 && game_version_ == GameVersion::BaseGame) {
      game_version_ = GameVersion::ProphecyOfKingsExpansion;
      warning("7 and 8 player games require the " + label(GameVersion::ProphecyOfKingsExpansion) + ".");
    }
  }

  void initialize_board_layout(const std::string board_layout) {
    const std::string label{std::to_string(number_of_players_) + "players" + lowercase(remove_non_alphanumeric_characters(board_layout))};
    const std::optional<BoardLayout> found{type<BoardLayout>(label)};
    if (found.has_value()) {
      board_layout_ = found.value();
    } else {
      message_usage_information_and_error("Unknown board layout: " + board_layout);
    }
  }

  void initialize_board_aggression(const std::string board_aggression) {
    const std::optional<BoardAggression> found{type<BoardAggression>(board_aggression)};
    if (found.has_value()) {
      board_aggression_ = found.value();
    } else {
      message_usage_information_and_error("Unknown board aggression: " + board_aggression);
    }
  }

  void initialize_number_of_iterations(const std::string number_of_iterations) {
    number_of_iterations_ = static_cast<uint64_t>(std::stoull(number_of_iterations));
    if (number_of_iterations_ == 0) {
      message_usage_information_and_error("The number of iterations must be greater than zero.");
    }
  }

  void message_header_information() const noexcept {
    message(Separator);
    message("TI4 Cartographer");
    message("Generates randomized balanced boards for the Twilight Imperium 4th Edition board game.");
    message("Version: " + CompilationDateAndTime);
  }

  void message_usage_information() const noexcept {
    const std::string space{"  "};
    message("Usage:");
    message(space + executable_name_ + " " + Arguments::NumberOfPlayersPattern + " [" + Arguments::GameVersionPattern + "] [" + Arguments::BoardLayoutPattern + "] [" + Arguments::BoardAggressionPattern + "] [" + Arguments::NumberOfIterationsPattern + "]");
    const uint_least64_t length{std::max({
      Arguments::UsageInformation.length(),
      Arguments::NumberOfPlayersPattern.length(),
      Arguments::GameVersionPattern.length(),
      Arguments::BoardLayoutPattern.length(),
      Arguments::BoardAggressionPattern.length(),
      Arguments::NumberOfIterationsPattern.length()
    })};
    message("Arguments:");
    message(space + pad_to_length(Arguments::UsageInformation, length) + space + "Displays this information and exits.");
    message(space + pad_to_length(Arguments::NumberOfPlayersPattern, length) + space + "Required. Choices are 2-8. Specifies the number of players.");
    message(space + pad_to_length(Arguments::GameVersionPattern, length) + space + "Optional. Choices are base or expansion. The default is expansion. Determines whether the system tiles from the Prophecy of Kings expansion can be used. Note that 7 and 8 player games require the expansion.");
    message(space + pad_to_length(Arguments::BoardLayoutPattern, length) + space + "Optional. Choices vary by number of players. Specifies the board layout. By default, the regular layout is used.");
    message(space + space + "2 players: regular");
    message(space + space + "3 players: regular");
    message(space + space + "4 players: regular or large");
    message(space + space + "5 players: regular, small, or large");
    message(space + space + "6 players: regular");
    message(space + space + "7 players: regular or large");
    message(space + space + "8 players: regular or large");
    message(space + pad_to_length(Arguments::BoardAggressionPattern, length) + space + "Optional. Choices are very-high, high, medium, low, or very-low. Specifies the degree of expected aggression resulting from the placement of systems on the board. By default, medium is used. Higher aggression places better systems at equidistant positions compared to the systems in each player's slice, whereas lower aggression does the opposite.");
    message(space + pad_to_length(Arguments::NumberOfIterationsPattern, length) + space + "Optional. The default is " + std::to_string(DefaultNumberOfIterations) + ". Specifies the number of board layout iterations.");
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
    message("The number of players and board layout is: " + label(board_layout_));
    message("The game version is: " + label(game_version_));
    message("The amount of aggression is: " + label(board_aggression_));
    message("The number of iterations is: " + std::to_string(number_of_iterations_));
  }

}; // class Instructions

} // namespace ti4cartographer
