#pragma once
#include "PWMI.hpp"

namespace Drivers {

class PWMDrivenDevice {
public:
  PWMDrivenDevice(Wrappers::PWMI &pmw, float minValue = 1000.0f,
                  float maxValue = 5000.0f);
  ~PWMDrivenDevice() = default;

  PWMDrivenDevice(const PWMDrivenDevice &) = delete;
  PWMDrivenDevice(PWMDrivenDevice &&) = delete;
  PWMDrivenDevice &operator=(const PWMDrivenDevice &) = delete;
  PWMDrivenDevice &operator=(PWMDrivenDevice &&) = delete;

  virtual void init() const;
  virtual void set(float value) const;
  float getMaxValue() { return m_maxValue; };

private:
  Wrappers::PWMI &m_pwm;

  float m_minValue;
  float m_maxValue;
};

} // namespace Drivers
