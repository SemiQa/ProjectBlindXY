#include "PWMInternal.hpp"

namespace Wrappers {
PWMInternal::PWMInternal(cyhal_gpio_t gpio) : m_gpio(gpio) {}

void PWMInternal::init() {
  cyhal_pwm_init(&m_handle, m_gpio, nullptr);
  setDutyCycle(.0f);
  cyhal_pwm_start(&m_handle);
}

void PWMInternal::setDutyCycle(float dutyCycle) {
  cyhal_pwm_set_duty_cycle(
      &m_handle, dutyCycle >= m_maxValue ? m_maxValue : dutyCycle, m_freq);
}
} // namespace Wrappers