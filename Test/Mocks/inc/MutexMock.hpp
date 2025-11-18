#pragma once

#include "FreeRTOS.h"
#include "semphr.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct MutexMock {
  MutexMock();
  ~MutexMock();

  MOCK_METHOD(void, xSemaphoreTake, (SemaphoreHandle_t, TickType_t));
  MOCK_METHOD(void, xSemaphoreGive, (SemaphoreHandle_t));
};