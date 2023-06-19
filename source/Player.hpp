#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Player : uint8_t {
  Player1 = 1,
  Player2 = 2,
  Player3 = 3,
  Player4 = 4,
  Player5 = 5,
  Player6 = 6,
  Player7 = 7,
  Player8 = 8,
};

template<> const std::unordered_map<Player, std::string> labels<Player>{
  {Player::Player1, "Player 1"},
  {Player::Player2, "Player 2"},
  {Player::Player3, "Player 3"},
  {Player::Player4, "Player 4"},
  {Player::Player5, "Player 5"},
  {Player::Player6, "Player 6"},
  {Player::Player7, "Player 7"},
  {Player::Player8, "Player 8"},
};

template<> const std::unordered_map<std::string, Player> spellings<Player>{
  {"player1", Player::Player1},
  {"1",       Player::Player1},
  {"player2", Player::Player2},
  {"2",       Player::Player2},
  {"player3", Player::Player3},
  {"3",       Player::Player3},
  {"player4", Player::Player4},
  {"4",       Player::Player4},
  {"player5", Player::Player5},
  {"5",       Player::Player5},
  {"player6", Player::Player6},
  {"6",       Player::Player6},
  {"player7", Player::Player7},
  {"7",       Player::Player7},
  {"player8", Player::Player8},
  {"8",       Player::Player8},
};

std::set<Player> players(const uint8_t number_of_players) {
  std::set<Player> players_;
  if (number_of_players >= 1) {
    players_.insert(Player::Player1);
  }
  if (number_of_players >= 2) {
    players_.insert(Player::Player2);
  }
  if (number_of_players >= 3) {
    players_.insert(Player::Player3);
  }
  if (number_of_players >= 4) {
    players_.insert(Player::Player4);
  }
  if (number_of_players >= 5) {
    players_.insert(Player::Player5);
  }
  if (number_of_players >= 6) {
    players_.insert(Player::Player6);
  }
  if (number_of_players >= 7) {
    players_.insert(Player::Player7);
  }
  if (number_of_players >= 8) {
    players_.insert(Player::Player8);
  }
  return players_;
}

}  // namespace TI4Cartographer
