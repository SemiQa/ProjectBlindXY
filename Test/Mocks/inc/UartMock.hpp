#pragma once
#include "cy_retarget_io.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct UartMock {
  UartMock();
  ~UartMock();

  MOCK_METHOD(cy_rslt_t, cyhal_uart_getc,
              (cyhal_uart_t *, uint8_t *, uint32_t));
  MOCK_METHOD(cy_rslt_t, cyhal_uart_write,
              (cyhal_uart_t *, const void *, size_t *));
};