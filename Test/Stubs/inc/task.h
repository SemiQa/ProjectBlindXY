#pragma once

#define pdMS_TO_TICKS(x) x

void vTaskDelay(const TickType_t xTicksToDelay);

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName,
                       const configSTACK_DEPTH_TYPE uxStackDepth,
                       void *pvParameters, UBaseType_t uxPriority,
                       TaskHandle_t *pxCreatedTask);

TickType_t xTaskGetTickCount();