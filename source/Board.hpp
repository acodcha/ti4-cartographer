#pragma once

#include "Aggressions.hpp"
#include "BoardInitializer.hpp"
#include "Chronometre.hpp"
#include "SelectedSystemIds.hpp"

namespace TI4Cartographer {

/// \brief Arrangement of tiles that form a board.
template <Layout layout> class Board : public BoardInitializer<layout> {

public:

  Board(const GameVersion game_version, const Aggression aggression) noexcept : BoardInitializer<layout>() {
    initialize_player_scores();
    initialize_system_ids(game_version, aggression);
  }

private:

  std::map<Player, float> player_scores_;

  std::vector<std::string> equidistant_system_ids_;

  std::vector<std::string> in_slice_system_ids_;

  void initialize_player_scores() noexcept {
    for (const Player player : this->players_) {
      player_scores_.insert({player, 0.0});
    }
  }

  void initialize_system_ids(const GameVersion game_version, const Aggression aggression) noexcept {
    const SelectedSystemIds selected_system_ids{game_version, layout};
    std::vector<SystemIdAndScore> system_ids_and_scores;
    for (const std::string& id : selected_system_ids) {
      system_ids_and_scores.push_back({id, Systems.find({id})->score()});
    }
    std::sort(system_ids_and_scores.begin(), system_ids_and_scores.end(), SystemIdAndScore::sort_by_descending_score());
    uint8_t start_index{0};
    switch (aggression) {
      case Aggression::VeryLow:
        start_index = static_cast<uint8_t>(selected_system_ids.size() - this->equidistant_positions_.size());
        break;
      case Aggression::Low:
        start_index = static_cast<uint8_t>(std::floor(selected_system_ids.size() * 0.7 - this->equidistant_positions_.size() * 0.5));
        break;
      case Aggression::Medium:
        start_index = static_cast<uint8_t>(std::round(selected_system_ids.size() * 0.5 - this->equidistant_positions_.size() * 0.5));
        break;
      case Aggression::High:
        start_index = static_cast<uint8_t>(std::ceil(selected_system_ids.size() * 0.3 - this->equidistant_positions_.size() * 0.5));
        break;
      case Aggression::VeryHigh:
        start_index = 0;
        break;
    }
    for (uint8_t index = 0; index < system_ids_and_scores.size(); ++index) {
      if (index >= start_index && index < start_index + static_cast<uint8_t>(this->equidistant_positions_.size())) {
        equidistant_system_ids_.push_back(system_ids_and_scores[index].id());
      } else {
        in_slice_system_ids_.push_back(system_ids_and_scores[index].id());
      }
    }
  }

}; // class Board

} // namespace TI4Cartographer
