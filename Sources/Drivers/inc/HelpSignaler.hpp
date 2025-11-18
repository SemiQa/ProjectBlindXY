#pragma once

#include "GPIOI.hpp"
#include "PWMI.hpp"
#include "TimeStamp.hpp"
#include <stdint.h>

namespace Drivers {

class HelpSignaler {
public:
  HelpSignaler(Wrappers::GPIOI &diode, uint32_t periodMS);
  ~HelpSignaler() = default;

  HelpSignaler(const HelpSignaler &) = delete;
  HelpSignaler(HelpSignaler &&) = delete;
  HelpSignaler &operator=(const HelpSignaler &) = delete;
  HelpSignaler &operator=(HelpSignaler &&) = delete;

  enum class State : uint8_t { ACTIVE, INACTIVE, DISABLED };

  State getState() const;
  void init() const;
  void evaluate();
  void toggle();
  void enable();
  void disable();

private:
  void set();
  void reset();

  Wrappers::GPIOI &m_diode;
  uint32_t m_periodMS;
  TimeStamp m_timeStamp;

  State m_state = State::DISABLED;
};

} // namespace Drivers
