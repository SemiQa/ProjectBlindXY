#pragma once

#include "BGT60TRXX.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct RadarMock : Drivers::BGT60TRXX {
  RadarMock(Wrappers::SPII &spi) : Drivers::BGT60TRXX(spi) {};
  ~RadarMock() = default;

  MOCK_METHOD(void, init, ());
  MOCK_METHOD(bool, readDataIfPossible, ());
  MOCK_METHOD((std::array<float, 128> &), getValues, ());
};