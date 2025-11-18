#include "Mutex.hpp"

Mutex::Mutex() { m_handle = xSemaphoreCreateMutex(); }

Lock::Lock(Mutex &mutex) : m_mutex(mutex) {
  xSemaphoreTake(m_mutex.m_handle, portMAX_DELAY);
}

Lock::~Lock() { xSemaphoreGive(m_mutex.m_handle); }