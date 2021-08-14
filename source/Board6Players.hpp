#pragma once

#include "Board.hpp"

namespace ti4cartographer {

void Board<BoardLayout::Players6>::initialize_tiles() noexcept {
  tiles_.push_back({Position{1, 0}, {5}});
  tiles_.push_back({Position{1, 1}, {6}});
  tiles_.push_back({Position{1, 2}, {1}});
  tiles_.push_back({Position{1, 3}, {2}});
  tiles_.push_back({Position{1, 4}, {3}});
  tiles_.push_back({Position{1, 5}, {4}});
  tiles_.push_back({Position{2, 0}, {5}});
  tiles_.push_back({Position{2, 1}, {5, 6}});
  tiles_.push_back({Position{2, 2}, {6}});
  tiles_.push_back({Position{2, 3}, {1, 6}});
  tiles_.push_back({Position{2, 4}, {1}});
  tiles_.push_back({Position{2, 5}, {1, 2}});
  tiles_.push_back({Position{2, 6}, {2}});
  tiles_.push_back({Position{2, 7}, {2, 3}});
  tiles_.push_back({Position{2, 8}, {3}});
  tiles_.push_back({Position{2, 9}, {3, 4}});
  tiles_.push_back({Position{2, 10}, {4}});
  tiles_.push_back({Position{2, 11}, {4, 5}});
  tiles_.push_back({Position{3, 1}, {5}});
  tiles_.push_back({Position{3, 2}, {6}});
  tiles_.push_back({Position{3, 4}, {6}});
  tiles_.push_back({Position{3, 5}, {1}});
  tiles_.push_back({Position{3, 7}, {1}});
  tiles_.push_back({Position{3, 8}, {2}});
  tiles_.push_back({Position{3, 10}, {2}});
  tiles_.push_back({Position{3, 11}, {3}});
  tiles_.push_back({Position{3, 13}, {3}});
  tiles_.push_back({Position{3, 14}, {4}});
  tiles_.push_back({Position{3, 16}, {4}});
  tiles_.push_back({Position{3, 17}, {5}});
}

void Board<BoardLayout::Players6>::initialize_player_pathways_to_mecatol_rex() noexcept {
  player_pathways_to_mecatol_rex.insert({1, {{Pathway{{Position{2, 4}, Position{1, 2}}}}}});
  player_pathways_to_mecatol_rex.insert({2, {{Pathway{{Position{2, 6}, Position{1, 3}}}}}});
  player_pathways_to_mecatol_rex.insert({3, {{Pathway{{Position{2, 8}, Position{1, 4}}}}}});
  player_pathways_to_mecatol_rex.insert({4, {{Pathway{{Position{2, 10}, Position{1, 5}}}}}});
  player_pathways_to_mecatol_rex.insert({5, {{Pathway{{Position{2, 0}, Position{1, 0}}}}}});
  player_pathways_to_mecatol_rex.insert({6, {{Pathway{{Position{2, 2}, Position{1, 1}}}}}});
}

void Board<BoardLayout::Players6>::initialize_player_forward_positions() noexcept {
  player_forward_positions_.insert({1, {Position{2, 4}}});
  player_forward_positions_.insert({2, {Position{2, 6}}});
  player_forward_positions_.insert({3, {Position{2, 8}}});
  player_forward_positions_.insert({4, {Position{2, 10}}});
  player_forward_positions_.insert({5, {Position{2, 0}}});
  player_forward_positions_.insert({6, {Position{2, 2}}});
}

void Board<BoardLayout::Players6>::initialize_player_lateral_starboard_positions() noexcept {
  player_lateral_starboard_positions_.insert({1, {Position{3, 5}}});
  player_lateral_starboard_positions_.insert({2, {Position{3, 8}}});
  player_lateral_starboard_positions_.insert({3, {Position{3, 11}}});
  player_lateral_starboard_positions_.insert({4, {Position{3, 14}}});
  player_lateral_starboard_positions_.insert({5, {Position{3, 17}}});
  player_lateral_starboard_positions_.insert({6, {Position{3, 2}}});
}

void Board<BoardLayout::Players6>::initialize_player_lateral_port_positions() noexcept {
  player_lateral_port_positions_.insert({1, {Position{3, 7}}});
  player_lateral_port_positions_.insert({2, {Position{3, 10}}});
  player_lateral_port_positions_.insert({3, {Position{3, 13}}});
  player_lateral_port_positions_.insert({4, {Position{3, 16}}});
  player_lateral_port_positions_.insert({5, {Position{3, 1}}});
  player_lateral_port_positions_.insert({6, {Position{3, 4}}});
}

} // namespace ti4cartographer
