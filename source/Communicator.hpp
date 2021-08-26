#pragma once

#include "Enumerations.hpp"

namespace TI4Cartographer {

/// \brief Throw an exception.
inline void error(const std::string &text) {
  throw std::runtime_error(text);
}

enum class CommunicatorMode : uint8_t {
  Verbose,
  Quiet
};

template <> const std::unordered_map<CommunicatorMode, std::string> labels<CommunicatorMode>{
  {CommunicatorMode::Verbose, "Verbose"},
  {CommunicatorMode::Quiet, "Quiet"}
};

template <> const std::unordered_map<std::string, CommunicatorMode> spellings<CommunicatorMode>{
  {"verbose", CommunicatorMode::Verbose},
  {"quiet", CommunicatorMode::Quiet}
};

/// \brief Singleton class that tracks whether the quiet or verbose mode is used for console messages.
class Communicator {

public:

  /// \brief Obtain an instance of this singleton class.
  static Communicator& get(){
    static Communicator communicator;
    return communicator;
  }

  /// \brief Call this method once.
  void initialize(const CommunicatorMode mode) noexcept {
    if (!is_initialized_) {
      is_initialized_ = true;
      mode_ = mode;
    }
  };

  bool is_initialized() const noexcept {
    return is_initialized_;
  }

  CommunicatorMode mode() const noexcept {
    return mode_;
  }

  std::string print() const noexcept {
    return label(mode_);
  }

private:

  bool is_initialized_{false};

  CommunicatorMode mode_{CommunicatorMode::Verbose};

  Communicator() noexcept {};

  Communicator(const Communicator&) noexcept = delete;

  ~Communicator() noexcept {};

  Communicator& operator=(const Communicator&) noexcept = delete;

}; // class Communicator

/// \brief Print a general-purpose message to the console when in verbose mode.
inline void message(const std::string& text) noexcept {
  if (Communicator::get().mode() == CommunicatorMode::Verbose) {
    std::cout << text << std::endl;
  }
}

/// \brief Print a general-purpose message to the console when in quiet mode.
inline void quiet_message(const std::string& text) noexcept {
  if (Communicator::get().mode() == CommunicatorMode::Quiet) {
    std::cout << text << std::endl;
  }
}

/// \brief Print a warning to the console when in verbose mode.
inline void warning(const std::string& text) noexcept {
  if (Communicator::get().mode() == CommunicatorMode::Verbose) {
    std::cout << "Warning: " << text << std::endl;
  }
}

} // namespace TI4Cartographer
