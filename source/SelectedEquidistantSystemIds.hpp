#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

class SelectedEquidistantSystemIds {
public:
  SelectedEquidistantSystemIds() noexcept {}

  SelectedEquidistantSystemIds(const std::vector<std::string>& data) noexcept
    : data_(data) {}

  void push_back(const std::string& system_id) noexcept {
    data_.push_back(system_id);
  }

  void shuffle() noexcept {
    std::shuffle(data_.begin(), data_.end(), RandomEngine);
  }

  struct const_iterator : public std::vector<std::string>::const_iterator {
    const_iterator(const std::vector<std::string>::const_iterator i) noexcept
      : std::vector<std::string>::const_iterator(i) {}
  };

  bool empty() const noexcept { return data_.empty(); }

  std::size_t size() const noexcept { return data_.size(); }

  const std::string& at(const std::size_t index) const {
    return data_.at(index);
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  const_iterator begin() const noexcept { return cbegin(); }

  const_iterator cend() const noexcept { return const_iterator(data_.cend()); }

  const_iterator end() const noexcept { return cend(); }

  const std::string& front() const noexcept { return data_.front(); }

  const std::string& back() const noexcept { return data_.back(); }

  const std::string& operator[](const std::size_t index) const {
    return data_[index];
  }

  std::string print_brief() const noexcept {
    std::string text;
    for (const std::string& system_id : data_) {
      if (!text.empty()) {
        text += " ";
      }
      text += system_id;
    }
    return text;
  }

  std::string print_details() const noexcept {
    std::stringstream stream;
    uint8_t counter{0};
    for (const std::string& system_id : data_) {
      const std::unordered_set<System>::const_iterator found{
        Systems.find({system_id})};
      if (found != Systems.cend()) {
        if (counter > 0) {
          stream << std::endl;
        }
        stream << "- " << score_to_string(found->score()) << "  "
               << found->print();
        ++counter;
      }
    }
    return stream.str();
  }

private:
  std::vector<std::string> data_;

};  // class SelectedEquidistantSystemIds

}  // namespace TI4Cartographer
