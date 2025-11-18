#pragma once

#include "Mutex.hpp"
#include "cyhal.h"

namespace Wrappers {
class I2CI {
public:
  I2CI() = default;
  ~I2CI() = default;

  I2CI(const I2CI &) = delete;
  I2CI(I2CI &&) = delete;
  I2CI &operator=(const I2CI &) = delete;
  I2CI &operator=(I2CI &&) = delete;

  virtual cyhal_i2c_t *getHandle() = 0;
  virtual Mutex &getMutex() = 0;
};
} // namespace Wrappers