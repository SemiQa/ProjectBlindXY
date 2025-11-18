#pragma once

#include "SPII.hpp"
#include "xensiv_bgt60trxx_mtb.h"
#include <array>
#include <atomic>

namespace Drivers {

class BGT60TRXX {
private:
  static constexpr uint32_t m_configurationRegisterCount = 38;
  static constexpr uint32_t m_samplesPerChirp = 128;
  static constexpr uint32_t m_chirpsPerFrame = 1;
  static constexpr uint32_t m_antennaCount = 1;
  static constexpr uint32_t m_sampleCount =
      m_samplesPerChirp * m_chirpsPerFrame * m_antennaCount;
  static constexpr uint32_t m_interruptPriority = 6;
  const float m_normalizationFactor = 1.0f;

public:
  BGT60TRXX(Wrappers::SPII &spi);
  ~BGT60TRXX() = default;

  BGT60TRXX(const BGT60TRXX &) = delete;
  BGT60TRXX(BGT60TRXX &&) = delete;
  BGT60TRXX &operator=(const BGT60TRXX &) = delete;
  BGT60TRXX &operator=(BGT60TRXX &&) = delete;

  virtual void init();
  virtual bool readDataIfPossible();
  virtual std::array<float, m_sampleCount> &getValues();

private:
  static void interruptHandler(void *args, cyhal_gpio_event_t event);
  static std::atomic<bool> m_interruptObtained;

  Wrappers::SPII &m_spi;
  xensiv_bgt60trxx_mtb_t m_handle;
  std::array<uint32_t, m_configurationRegisterCount> m_registers{
      0x11e8270UL,  0x3088210UL,  0x9e967fdUL,  0xb0805b4UL,  0xdf02fffUL,
      0xf010700UL,  0x11000000UL, 0x13000000UL, 0x15000000UL, 0x17000be0UL,
      0x19000000UL, 0x1b000000UL, 0x1d000000UL, 0x1f000b60UL, 0x21130c51UL,
      0x234ff41fUL, 0x25006f7bUL, 0x2d000490UL, 0x3b000480UL, 0x49000480UL,
      0x57000480UL, 0x5911be0eUL, 0x5b3ef40aUL, 0x5d00f000UL, 0x5f787e1eUL,
      0x61f5208cUL, 0x630000a4UL, 0x65000252UL, 0x67000080UL, 0x69000000UL,
      0x6b000000UL, 0x6d000000UL, 0x6f092910UL, 0x7f000100UL, 0x8f000100UL,
      0x9f000100UL, 0xad000000UL, 0xb7000000UL};
  std::array<uint16_t, m_sampleCount> m_rawData;
  std::array<float, m_sampleCount> m_processedData;
};

} // namespace Drivers
