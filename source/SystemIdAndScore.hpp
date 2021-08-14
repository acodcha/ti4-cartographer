#pragma once

#include "Base.hpp"

namespace ti4cartographer {

/// \brief Simple pair of a system ID and score.
class SystemIdAndScore {

public:

  SystemIdAndScore() noexcept {}

  SystemIdAndScore(const std::string id, const double score) noexcept : id_(id), score_(score) {}

  const std::string& id() const noexcept {
    return id_;
  }

  const double score() const noexcept {
    return score_;
  }

  struct sort_descending {
    bool operator()(const SystemIdAndScore& system_id_and_score_1, const SystemIdAndScore& system_id_and_score_2) const noexcept {
      if (system_id_and_score_1.score() < system_id_and_score_2.score()) {
        return false;
      } else if (system_id_and_score_1.score() > system_id_and_score_2.score()) {
        return true;
      } else {
        return system_id_and_score_1.id() < system_id_and_score_2.id();
      }
    }
  };

protected:

  std::string id_;

  double score_{0.0};

}; // class SystemIdAndScore

} // namespace ti4cartographer
