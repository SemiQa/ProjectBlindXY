#include "SPIInternal.hpp"

#include "cycfg_pins.h"

namespace Wrappers {
SPIInternal::SPIInternal() {
  cyhal_spi_init(&m_handle, CYBSP_RSPI_MOSI, CYBSP_RSPI_MISO, CYBSP_RSPI_CLK,
                 NC, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
  cyhal_spi_set_frequency(&m_handle, m_frequency);
}

cyhal_spi_t *SPIInternal::getHandle() { return &m_handle; }

Mutex &SPIInternal::getMutex() { return m_mutex; }

} // namespace Wrappers