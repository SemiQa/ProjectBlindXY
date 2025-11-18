#pragma once

#include "cyhal_gpio.h"

namespace Wrappers {

class GPIOI {
public:
  GPIOI() = default;
  ~GPIOI() = default;

  GPIOI(const GPIOI &) = delete;
  GPIOI(GPIOI &&) = delete;
  GPIOI &operator=(const GPIOI &) = delete;
  GPIOI &operator=(GPIOI &&) = delete;

  virtual void init(cyhal_gpio_direction_t direction,
                    cyhal_gpio_drive_mode_t mode) const = 0;
  virtual void set() const = 0;
  virtual void reset() const = 0;
  virtual void write(bool val) const = 0;
  virtual void toggle() const = 0;
};

} // namespace Wrappers
