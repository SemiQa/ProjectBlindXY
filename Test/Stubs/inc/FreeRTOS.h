#pragma once

#define CY_RTOS_PRIORITY_HIGH 2

#define CY_RTOS_PRIORITY_NORMAL 1

typedef unsigned int configSTACK_DEPTH_TYPE;

typedef unsigned int UBaseType_t;

typedef unsigned int TickType_t;

typedef int BaseType_t;

typedef struct {
} TaskHandle_t;

typedef void (*TaskFunction_t)(void *args);