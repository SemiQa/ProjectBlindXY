#include "TaskMock.hpp"
#include <functional>

static std::function<void(const TickType_t)> _vTaskDelay;
static std::function<BaseType_t(TaskFunction_t, const char *const,
                                const configSTACK_DEPTH_TYPE, void *,
                                UBaseType_t, TaskHandle_t *)>
    _xTaskCreate;
static std::function<TickType_t()> _xTaskGetTickCount;

void vTaskDelay(const TickType_t xTicksToDelay) { _vTaskDelay(xTicksToDelay); }

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName,
                       const configSTACK_DEPTH_TYPE uxStackDepth,
                       void *pvParameters, UBaseType_t uxPriority,
                       TaskHandle_t *pxCreatedTask) {
  return _xTaskCreate(pvTaskCode, pcName, uxStackDepth, pvParameters,
                      uxPriority, pxCreatedTask);
}

TickType_t xTaskGetTickCount() { return _xTaskGetTickCount(); }

TaskMock::TaskMock() {
  _vTaskDelay = [this](const TickType_t xTicksToDelay) {
    vTaskDelay(xTicksToDelay);
  };
  _xTaskCreate = [this](TaskFunction_t pvTaskCode, const char *const pcName,
                        const configSTACK_DEPTH_TYPE uxStackDepth,
                        void *pvParameters, UBaseType_t uxPriority,
                        TaskHandle_t *pxCreatedTask) {
    return xTaskCreate(pvTaskCode, pcName, uxStackDepth, pvParameters,
                       uxPriority, pxCreatedTask);
  };
  _xTaskGetTickCount = [this]() { return xTaskGetTickCount(); };
}

TaskMock::~TaskMock() {
  _vTaskDelay = {};
  _xTaskCreate = {};
  _xTaskGetTickCount = {};
}
