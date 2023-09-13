#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

/// \brief Distance between two positions on the board.
/// \details A distance of 0 is the same position, a distance of 1 is an
/// adjacent position, and so on.
class Distance {
public:
  constexpr Distance() noexcept {}

  constexpr Distance(const int8_t value) noexcept : value_(value) {}

  constexpr int8_t value() const noexcept {
    return value_;
  }

  std::string print() const noexcept {
    return std::to_string(value_);
  }

  constexpr bool operator==(const Distance& other) const noexcept {
    return value_ == other.value_;
  }

  constexpr bool operator!=(const Distance& other) const noexcept {
    return value_ != other.value_;
  }

  constexpr bool operator<(const Distance& other) const noexcept {
    return value_ < other.value_;
  }

  constexpr bool operator<=(const Distance& other) const noexcept {
    return value_ <= other.value_;
  }

  constexpr bool operator>(const Distance& other) const noexcept {
    return value_ > other.value_;
  }

  constexpr bool operator>=(const Distance& other) const noexcept {
    return value_ >= other.value_;
  }

  /// \brief Pre-increment ++ operator.
  constexpr Distance& operator++() noexcept {
    ++value_;
    return *this;
  }

  /// \brief Post-increment ++ operator.
  Distance operator++(int) {
    Distance copy(*this);
    ++(*this);
    return copy;
  }

  /// \brief Pre-increment -- operator.
  constexpr Distance& operator--() noexcept {
    --value_;
    return *this;
  }

  /// \brief Post-increment -- operator.
  Distance operator--(int) {
    Distance copy(*this);
    --(*this);
    return copy;
  }

  constexpr Distance operator+(const Distance& other) const noexcept {
    return {static_cast<int8_t>(value_ + other.value_)};
  }

  constexpr void operator+=(const Distance& other) noexcept {
    value_ += other.value_;
  }

  constexpr Distance operator-(const Distance& other) const noexcept {
    return {static_cast<int8_t>(value_ - other.value_)};
  }

  constexpr void operator-=(const Distance& other) noexcept {
    value_ -= other.value_;
  }

  constexpr Distance operator*(const int8_t number) const noexcept {
    return {static_cast<int8_t>(value_ * number)};
  }

  constexpr void operator*=(const int8_t number) noexcept {
    value_ *= number;
  }

  constexpr Distance operator/(const int8_t number) const noexcept {
    return {static_cast<int8_t>(value_ / number)};
  }

  constexpr void operator/=(const int8_t number) noexcept {
    value_ /= number;
  }

private:
  int8_t value_{0};

};  // class Distance

}  // namespace TI4Cartographer

namespace std {

template <>
struct hash<TI4Cartographer::Distance> {
  size_t operator()(const TI4Cartographer::Distance& distance) const {
    return hash<int8_t>()(distance.value());
  }
};

template <>
class numeric_limits<TI4Cartographer::Distance> {
public:
  static int8_t max() {
    return numeric_limits<int8_t>::max();
  };
  static int8_t lowest() {
    return numeric_limits<int8_t>::lowest();
  };
};

}  // namespace std
