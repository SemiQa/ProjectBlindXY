#pragma once

#include <stdint.h>
#include <stdlib.h>

#define CY_RSLT_SUCCESS 0

typedef struct {
} cyhal_uart_t;

typedef unsigned int cy_rslt_t;

extern cyhal_uart_t cy_retarget_io_uart_obj;

cy_rslt_t cyhal_uart_getc(cyhal_uart_t *obj, uint8_t *value, uint32_t timeout);

cy_rslt_t cyhal_uart_write(cyhal_uart_t *obj, const void *tx, size_t *length);
