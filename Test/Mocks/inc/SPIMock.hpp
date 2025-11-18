#pragma once

#pragma once

#include "SPII.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct SPIMock : Wrappers::SPII {
  MOCK_METHOD(cyhal_spi_t *, getHandle, ());
  MOCK_METHOD(Mutex &, getMutex, ());
};