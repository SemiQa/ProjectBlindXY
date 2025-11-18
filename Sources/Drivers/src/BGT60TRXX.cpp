#include "BGT60TRXX.hpp"
#include "cycfg_pins.h"

namespace Drivers {

std::atomic<bool> BGT60TRXX::m_interruptObtained = false;

void BGT60TRXX::interruptHandler(void *args, cyhal_gpio_event_t event) {
  m_interruptObtained.store(true);
}

BGT60TRXX::BGT60TRXX(Wrappers::SPII &spi) : m_spi(spi) {}

void BGT60TRXX::init() {
  Lock lock{m_spi.getMutex()};
  xensiv_bgt60trxx_mtb_init(&m_handle, m_spi.getHandle(), CYBSP_RSPI_CS,
                            CYBSP_RXRES_L, m_registers.data(),
                            m_configurationRegisterCount);
  xensiv_bgt60trxx_mtb_interrupt_init(&m_handle, m_sampleCount, CYBSP_RSPI_IRQ,
                                      m_interruptPriority, interruptHandler,
                                      NULL);
  xensiv_bgt60trxx_start_frame(&m_handle.dev, true);
}

bool BGT60TRXX::readDataIfPossible() {
  if (!m_interruptObtained.load()) {
    return false;
  }
  Lock lock{m_spi.getMutex()};
  m_interruptObtained.store(false);

  xensiv_bgt60trxx_get_fifo_data(&m_handle.dev, m_rawData.data(),
                                 m_sampleCount);
  xensiv_bgt60trxx_soft_reset(&m_handle.dev, XENSIV_BGT60TRXX_RESET_FIFO);
  xensiv_bgt60trxx_start_frame(&m_handle.dev, true);
  return true;
}

std::array<float, BGT60TRXX::m_sampleCount> &BGT60TRXX::getValues() {
  for (uint32_t i = 0; i < m_sampleCount; i++)
    m_processedData[i] = m_rawData[i] * m_normalizationFactor;
  return m_processedData;
}

} // namespace Drivers