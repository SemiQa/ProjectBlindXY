#pragma once

#include "GPIOI.hpp"

namespace Wrappers {

class GPIOInternal : public GPIOI {
public:
  GPIOInternal(cyhal_gpio_t gpio);
  ~GPIOInternal() = default;

  GPIOInternal(const GPIOInternal &) = delete;
  GPIOInternal(GPIOInternal &&) = delete;
  GPIOInternal &operator=(const GPIOInternal &) = delete;
  GPIOInternal &operator=(GPIOInternal &&) = delete;

  void init(cyhal_gpio_direction_t direction,
            cyhal_gpio_drive_mode_t mode) const final;
  void set() const final;
  void reset() const final;
  void write(bool val) const final;
  void toggle() const final;

private:
  cyhal_gpio_t m_gpio;
};

} // namespace Wrappers
