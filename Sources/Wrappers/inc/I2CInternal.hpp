#pragma once
#include "I2CI.hpp"

namespace Wrappers {
class I2CInternal : public I2CI {
public:
  I2CInternal();
  ~I2CInternal() = default;

  I2CInternal(const I2CInternal &) = delete;
  I2CInternal(I2CInternal &&) = delete;
  I2CInternal &operator=(const I2CInternal &) = delete;
  I2CInternal &operator=(I2CInternal &&) = delete;

  cyhal_i2c_t *getHandle() final;
  Mutex &getMutex() final;

private:
  cyhal_i2c_t m_handle;
  static constexpr uint32_t m_freq = 100000;
  Mutex m_mutex;
};
} // namespace Wrappers