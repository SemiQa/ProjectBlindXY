#pragma once

#include "GPIOI.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct GPIOMock : public Wrappers::GPIOI {
  MOCK_METHOD(void, init, (cyhal_gpio_direction_t, cyhal_gpio_drive_mode_t),
              (const));
  MOCK_METHOD(void, set, (), (const));
  MOCK_METHOD(void, reset, (), (const));
  MOCK_METHOD(void, write, (bool), (const));
  MOCK_METHOD(void, toggle, (), (const));
};
