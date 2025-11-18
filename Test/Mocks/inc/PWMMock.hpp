#pragma once

#include "PWMI.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct PWMMock : Wrappers::PWMI {
  PWMMock() = default;
  ~PWMMock() = default;

  MOCK_METHOD(void, init, ());
  MOCK_METHOD(void, setDutyCycle, (float));
};