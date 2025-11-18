#include "PWMDrivenDevice.hpp"

namespace Drivers {

PWMDrivenDevice::PWMDrivenDevice(Wrappers::PWMI &pwm, float minValue,
                                 float maxValue)
    : m_pwm(pwm), m_minValue(minValue), m_maxValue(maxValue) {}

void PWMDrivenDevice::init() const { m_pwm.init(); }

void PWMDrivenDevice::set(float value) const {
  if (value == 0.0f)
    m_pwm.setDutyCycle(0.0f);
  else if (value < m_minValue)
    m_pwm.setDutyCycle(m_minValue);
  else
    m_pwm.setDutyCycle(value / m_maxValue * 100.0f);
}

} // namespace Drivers