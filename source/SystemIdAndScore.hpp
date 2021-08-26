#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

/// \brief Simple pair of a system ID and score.
class SystemIdAndScore {

public:

  SystemIdAndScore() noexcept {}

  SystemIdAndScore(const std::string& id, const double score) noexcept : id_(id), score_(score) {}

  const std::string& id() const noexcept {
    return id_;
  }

  const double score() const noexcept {
    return score_;
  }

  struct sort_by_descending_score {
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

  bool operator==(const SystemIdAndScore& other) const noexcept {
    return id_ == other.id_;
  }

  bool operator!=(const SystemIdAndScore& other) const noexcept {
    return id_ != other.id_;
  }

private:

  std::string id_;

  double score_{0.0};

}; // class SystemIdAndScore

} // namespace TI4Cartographer

namespace std {

  template <> struct hash<TI4Cartographer::SystemIdAndScore> {
    size_t operator()(const TI4Cartographer::SystemIdAndScore& system_id_and_score) const {
      return hash<std::string>()(system_id_and_score.id());
    }
  };

} // namespace std
