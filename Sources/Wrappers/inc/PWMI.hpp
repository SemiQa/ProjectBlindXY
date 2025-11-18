#pragma once

namespace Wrappers {
class PWMI {
public:
  PWMI() = default;
  ~PWMI() = default;

  PWMI(const PWMI &) = delete;
  PWMI(PWMI &&) = delete;
  PWMI &operator=(const PWMI &) = delete;
  PWMI &operator=(PWMI &&) = delete;

  virtual void init() = 0;
  virtual void setDutyCycle(float dutyCycle) = 0;
};
} // namespace Wrappers