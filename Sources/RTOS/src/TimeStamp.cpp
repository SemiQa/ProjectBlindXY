#include "TimeStamp.hpp"

void TimeStamp::set(size_t timeMS) {
  m_setTimeMS = timeMS;
  m_tick = xTaskGetTickCount();
}

bool TimeStamp::elapsed() {
  auto currentTick = xTaskGetTickCount();
  if (pdMS_TO_TICKS(currentTick - m_tick) < m_setTimeMS)
    return false;
  m_tick = currentTick;
  return true;
}