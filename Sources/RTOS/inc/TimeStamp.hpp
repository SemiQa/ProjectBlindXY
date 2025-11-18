#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

class TimeStamp {
public:
  TimeStamp() = default;
  ~TimeStamp() = default;

  TimeStamp(const TimeStamp &) = delete;
  TimeStamp(TimeStamp &&) = delete;
  TimeStamp &operator=(const TimeStamp &) = delete;
  TimeStamp &operator=(TimeStamp &&) = delete;

  void set(size_t timeMS);
  bool elapsed();

private:
  size_t m_setTimeMS = 0;
  TickType_t m_tick;
};