#include "UartMock.hpp"
#include <functional>

static std::function<cy_rslt_t(cyhal_uart_t *, uint8_t *, uint32_t)>
    _cyhal_uart_getc;
static std::function<cy_rslt_t(cyhal_uart_t *, const void *, size_t *)>
    _cyhal_uart_write;

cy_rslt_t cyhal_uart_getc(cyhal_uart_t *obj, uint8_t *value, uint32_t timeout) {
  return _cyhal_uart_getc(obj, value, timeout);
}

cy_rslt_t cyhal_uart_write(cyhal_uart_t *obj, const void *tx, size_t *length) {
  return _cyhal_uart_write(obj, tx, length);
}

UartMock::UartMock() {
  _cyhal_uart_getc = [this](cyhal_uart_t *obj, uint8_t *value,
                            uint32_t timeout) {
    return cyhal_uart_getc(obj, value, timeout);
  };
  _cyhal_uart_write = [this](cyhal_uart_t *obj, const void *tx,
                             size_t *length) {
    return cyhal_uart_write(obj, tx, length);
  };
}

UartMock::~UartMock() {
  _cyhal_uart_getc = {};
  _cyhal_uart_write = {};
}
