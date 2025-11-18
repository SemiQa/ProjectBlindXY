#pragma once
#include "FreeRTOS.h"
#include "semphr.h"

class Mutex {
public:
  Mutex();
  ~Mutex() = default;

  Mutex(const Mutex &) = delete;
  Mutex(Mutex &&) = delete;
  Mutex &operator=(const Mutex &) = delete;
  Mutex &operator=(Mutex &&) = delete;

private:
  SemaphoreHandle_t m_handle;

  friend class Lock;
};

class Lock {
public:
  Lock(Mutex &mutex);
  ~Lock();

  Lock(const Lock &) = delete;
  Lock(Lock &&) = delete;
  Lock &operator=(const Lock &) = delete;
  Lock &operator=(Lock &&) = delete;

private:
  Mutex &m_mutex;
};