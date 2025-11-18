#include "I2CInternal.hpp"

#include "cycfg_pins.h"

namespace Wrappers {
I2CInternal::I2CInternal() {
  cyhal_i2c_init(&m_handle, (cyhal_gpio_t)CYBSP_I2C_SDA,
                 (cyhal_gpio_t)CYBSP_I2C_SCL, NULL);

  cyhal_i2c_cfg_t cfg;
  cfg.is_slave = false;
  cfg.address = 0;
  cfg.frequencyhal_hz = m_freq;

  cyhal_i2c_configure(&m_handle, &cfg);
}

cyhal_i2c_t *I2CInternal::getHandle() { return &m_handle; }

Mutex &I2CInternal::getMutex() { return m_mutex; }

} // namespace Wrappers