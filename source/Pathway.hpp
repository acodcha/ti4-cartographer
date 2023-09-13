#pragma once

#include "Distance.hpp"
#include "Position.hpp"

namespace TI4Cartographer {

/// \brief Sequence of positions that form a path from a player's home system to
/// Mecatol Rex.
class Pathway {
public:
  Pathway() noexcept {}

  void push_back(const Position& position) noexcept {
    data_.push_back(position);
  }

  struct const_iterator : public std::vector<Position>::const_iterator {
    const_iterator(const std::vector<Position>::const_iterator i) noexcept
      : std::vector<Position>::const_iterator(i) {}
  };

  bool empty() const noexcept {
    return data_.empty();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  Distance distance() const noexcept {
    return {static_cast<int8_t>(data_.size())};
  }

  const Position& at(const std::size_t index) const {
    return data_.at(index);
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  const_iterator begin() const noexcept {
    return cbegin();
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  const_iterator end() const noexcept {
    return cend();
  }

  const Position& front() const noexcept {
    return data_.front();
  }

  const Position& back() const noexcept {
    return data_.back();
  }

  bool operator==(const Pathway& other) const noexcept {
    data_ == other.data_;
  }

  bool operator!=(const Pathway& other) const noexcept {
    data_ != other.data_;
  }

  bool operator<(const Pathway& other) const noexcept {
    data_ < other.data_;
  }

  bool operator<=(const Pathway& other) const noexcept {
    data_ <= other.data_;
  }

  bool operator>(const Pathway& other) const noexcept {
    data_ > other.data_;
  }

  bool operator>=(const Pathway& other) const noexcept {
    data_ >= other.data_;
  }

  const Position& operator[](const std::size_t index) const {
    return data_[index];
  }

  std::string print() const noexcept {
    std::string text;
    for (const Position& position : data_) {
      if (!text.empty()) {
        text += " ";
      }
      text += position.print();
    }
    return text;
  }

private:
  std::vector<Position> data_;

};  // class Pathway

}  // namespace TI4Cartographer

namespace std {

template <>
struct hash<TI4Cartographer::Pathway> {
  size_t operator()(const TI4Cartographer::Pathway& pathway) const {
    size_t value{1234567890};
    for (const TI4Cartographer::Position& position : pathway) {
      value ^= hash<TI4Cartographer::Position>()(position);
    }
    return value;
  }
};

}  // namespace std
