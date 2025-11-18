#pragma once
#include "SPII.hpp"

namespace Wrappers {
class SPIInternal : public SPII {
public:
  SPIInternal();
  ~SPIInternal() = default;

  SPIInternal(const SPIInternal &) = delete;
  SPIInternal(SPIInternal &&) = delete;
  SPIInternal &operator=(const SPIInternal &) = delete;
  SPIInternal &operator=(SPIInternal &&) = delete;

  cyhal_spi_t *getHandle() final;
  Mutex &getMutex() final;

private:
  static constexpr uint32_t m_frequency = 25000000;
  cyhal_spi_t m_handle;
  Mutex m_mutex;
};
} // namespace Wrappers