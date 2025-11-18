#pragma once

#include "PWMI.hpp"
#include "cyhal_pwm.h"

namespace Wrappers {
class PWMInternal : public PWMI {
public:
  PWMInternal(cyhal_gpio_t gpio);
  ~PWMInternal() = default;

  PWMInternal(const PWMInternal &) = delete;
  PWMInternal(PWMInternal &&) = delete;
  PWMInternal &operator=(const PWMInternal &) = delete;
  PWMInternal &operator=(PWMInternal &&) = delete;

  void init() final;
  void setDutyCycle(float dutyCycle) final;

private:
  static constexpr uint32_t m_freq = 10000;
  static constexpr float m_maxValue = 100.0f;

  cyhal_pwm_t m_handle;
  cyhal_gpio_t m_gpio;
};
} // namespace Wrappers