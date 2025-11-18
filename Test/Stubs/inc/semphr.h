#pragma once

#include "FreeRTOS.h"

#define portMAX_DELAY 100

typedef struct {
} SemaphoreHandle_t;

#ifdef __cplusplus
extern "C" {
#endif

SemaphoreHandle_t xSemaphoreCreateMutex();

#ifdef __cplusplus
}
#endif

void xSemaphoreTake(SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait);
void xSemaphoreGive(SemaphoreHandle_t xSemaphore);