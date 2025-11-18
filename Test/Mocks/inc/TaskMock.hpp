#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct TaskMock {
  TaskMock();
  ~TaskMock();

  MOCK_METHOD(BaseType_t, xTaskCreate,
              (TaskFunction_t, const char *const, const configSTACK_DEPTH_TYPE,
               void *, UBaseType_t, TaskHandle_t *));
  MOCK_METHOD(void, vTaskDelay, (const TickType_t));
  MOCK_METHOD(TickType_t, xTaskGetTickCount, ());
};