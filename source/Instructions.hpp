#pragma once

#include "Aggression.hpp"
#include "GameVersion.hpp"
#include "Layout.hpp"

namespace TI4Cartographer {

/// \brief Namespace listing the program's command-line argument keywords.
namespace Arguments {

const std::string QuietMode{"--quiet"};

const std::string UsageInformation{"--help"};

const std::string NumberOfPlayersKey{"--players"};

const std::string NumberOfPlayersPattern{NumberOfPlayersKey + " <number>"};

const std::string LayoutKey{"--layout"};

const std::string LayoutPattern{LayoutKey + " <type>"};

const std::string AggressionKey{"--aggression"};

const std::string AggressionPattern{AggressionKey + " <type>"};

const std::string GameVersionKey{"--version"};

const std::string GameVersionPattern{GameVersionKey + " <type>"};

}  // namespace Arguments

/// \brief Parser and organizer of the program's command-line arguments.
class Instructions {
public:
  Instructions(int argc, char* argv[]) : executable_name_(argv[0]) {
    assign_arguments(argc, argv);
    initialize();
    message_header_information();
    message_start_information();
    check_layout_and_game_version();
  }

  Layout layout() const noexcept { return layout_; }

  Aggression aggression() const noexcept { return aggression_; }

  GameVersion game_version() const noexcept { return game_version_; }

private:
  std::string executable_name_;

  std::vector<std::string> arguments_;

  Layout layout_{Layout::Players6Regular};

  Aggression aggression_{Aggression::Moderate};

  GameVersion game_version_{GameVersion::ProphecyOfKingsExpansion};

  void assign_arguments(int argc, char* argv[]) noexcept {
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
    for (
        std::vector<std::string>::const_iterator argument = arguments_.cbegin();
        argument < arguments_.cend(); ++argument) {
      if (*argument == Arguments::QuietMode) {
        Communicator::get().initialize(CommunicatorMode::Quiet);
      } else if (*argument == Arguments::UsageInformation) {
        message_header_information();
        message_usage_information();
        exit(EXIT_SUCCESS);
      } else if (*argument == Arguments::NumberOfPlayersKey
                 && argument + 1 < arguments_.cend()) {
        number_of_players = static_cast<uint8_t>(std::stoi(*(argument + 1)));
        check_number_of_players(number_of_players);
      } else if (*argument == Arguments::LayoutKey
                 && argument + 1 < arguments_.cend()) {
        layout_string = *(argument + 1);
      } else if (*argument == Arguments::AggressionKey
                 && argument + 1 < arguments_.cend()) {
        initialize_aggression(*(argument + 1));
      } else if (*argument == Arguments::GameVersionKey
                 && argument + 1 < arguments_.cend()) {
        initialize_game_version(*(argument + 1));
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

  void initialize_aggression(const std::string aggression) {
    const std::optional<Aggression> found{type<Aggression>(aggression)};
    if (found.has_value()) {
      aggression_ = found.value();
    } else {
      message_usage_information_and_error(
          "Unknown board aggression: " + aggression);
    }
  }

  void initialize_game_version(const std::string game_version) {
    const std::optional<GameVersion> found{type<GameVersion>(game_version)};
    if (found.has_value()) {
      game_version_ = found.value();
    } else {
      message_usage_information_and_error(
          "Unknown game version: " + game_version);
    }
  }

  void check_game_version(const uint8_t number_of_players) const {
    if (number_of_players >= 7 && game_version_ == GameVersion::BaseGame) {
      message_usage_information_and_error(
          "7 and 8 player games require the "
          + label(GameVersion::ProphecyOfKingsExpansion) + ".");
    }
  }

  void initialize_layout(
      const uint8_t number_of_players, const std::string& layout_string) {
    const std::string label{
        std::to_string(number_of_players) + "players"
        + lowercase(remove_non_alphanumeric_characters(layout_string))};
    const std::optional<Layout> found{type<Layout>(label)};
    if (found.has_value()) {
      layout_ = found.value();
    } else {
      message_usage_information_and_error(
          "Unknown board layout: " + layout_string);
    }
  }

  void message_header_information() const noexcept {
    verbose_message(Separator);
    verbose_message(ProgramName);
    verbose_message(
        "Generates randomized balanced boards for the Twilight Imperium 4th "
        "Edition board game.");
    verbose_message("Compiled: " + CompilationDateAndTime);
    verbose_message("Command: " + command());
  }

  void message_usage_information() const noexcept {
    const std::string space{"  "};
    verbose_message("Usage:");
    verbose_message(
        space + executable_name_ + space + Arguments::NumberOfPlayersPattern
        + space + Arguments::LayoutPattern + space
        + Arguments::AggressionPattern + space + Arguments::GameVersionPattern
        + space + Arguments::QuietMode);
    const uint_least64_t length{std::max(
        {Arguments::UsageInformation.length(),
         Arguments::NumberOfPlayersPattern.length(),
         Arguments::LayoutPattern.length(),
         Arguments::AggressionPattern.length(),
         Arguments::GameVersionPattern.length(),
         Arguments::QuietMode.length()})};
    verbose_message("Arguments:");
    verbose_message(space + pad_to_length(Arguments::UsageInformation, length)
                    + space + "Displays this information and exits.");
    verbose_message(
        space + pad_to_length(Arguments::NumberOfPlayersPattern, length) + space
        + "Required. Specifies the number of players. Choices are 2-8.");
    verbose_message(space + pad_to_length(Arguments::LayoutPattern, length) + space + "Optional. Specifies the board layout. Choices vary by number of players, but typically include regular, small, or large. The default is regular.");
    verbose_message(space + space + "2 players: regular");
    verbose_message(space + space + "3 players: regular, small, or large");
    verbose_message(space + space + "4 players: regular or large");
    verbose_message(space + space + "5 players: regular, small, or large");
    verbose_message(space + space + "6 players: regular");
    verbose_message(space + space + "7 players: regular or large");
    verbose_message(space + space + "8 players: regular or large");
    verbose_message(space + pad_to_length(Arguments::AggressionPattern, length) + space + "Optional. Specifies the degree of expected aggression resulting from the placement of systems on the board. Choices are low, moderate, or high. The default is moderate. Higher aggression places better systems at equidistant positions compared to the systems in each player's slice, whereas lower aggression does the opposite.");
    verbose_message(space + pad_to_length(Arguments::GameVersionPattern, length) + space + "Optional. Determines whether the system tiles from the Prophecy of Kings expansion can be used. Choices are base or expansion. The default is expansion. Note that 7 and 8 player games require the Prophecy of Kings expansion.");
    verbose_message(space + pad_to_length(Arguments::QuietMode, length) + space + "Optional. Activates quiet mode, where the only console output is the generated board's Tabletop Simulator string.");
    verbose_message("");
  }

  std::string command() const noexcept {
    std::string text{executable_name_};
    for (const std::string& argument : arguments_) {
      text += " " + argument;
    }
    return text;
  }

  void message_start_information() const noexcept {
    verbose_message(
        "The number of players and board layout is: " + label(layout_));
    verbose_message("The aggression is: " + label(aggression_));
    verbose_message("The game version is: " + label(game_version_));
  }

  void check_layout_and_game_version() const {
    if (!layout_and_game_version_are_compatible(layout_, game_version_)) {
      error("The board layout and the game version are incompatible. The "
            + label(layout_) + " board layout requires the "
            + label(GameVersion::ProphecyOfKingsExpansion) + ".");
    }
  }

};  // class Instructions

}  // namespace TI4Cartographer
