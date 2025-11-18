#include "MutexMock.hpp"
#include <functional>

static std::function<void(SemaphoreHandle_t, TickType_t)> _xSemaphoreTake;
static std::function<void(SemaphoreHandle_t)> _xSemaphoreGive;

void xSemaphoreTake(SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait) {
  _xSemaphoreTake(xSemaphore, xTicksToWait);
}
void xSemaphoreGive(SemaphoreHandle_t xSemaphore) {
  _xSemaphoreGive(xSemaphore);
}

MutexMock::MutexMock() {
  _xSemaphoreTake = [this](SemaphoreHandle_t xSemaphore,
                           TickType_t xTicksToWait) {
    xSemaphoreTake(xSemaphore, xTicksToWait);
  };
  _xSemaphoreGive = [this](SemaphoreHandle_t xSemaphore) {
    xSemaphoreGive(xSemaphore);
  };
}

MutexMock::~MutexMock() {
  _xSemaphoreTake = {};
  _xSemaphoreGive = {};
}