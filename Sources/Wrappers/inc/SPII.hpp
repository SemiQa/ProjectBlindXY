#pragma once

#include "Mutex.hpp"
#include "cyhal.h"

namespace Wrappers {
class SPII {
public:
  SPII() = default;
  ~SPII() = default;

  SPII(const SPII &) = delete;
  SPII(SPII &&) = delete;
  SPII &operator=(const SPII &) = delete;
  SPII &operator=(SPII &&) = delete;

  virtual cyhal_spi_t *getHandle() = 0;
  virtual Mutex &getMutex() = 0;
};
} // namespace Wrappers