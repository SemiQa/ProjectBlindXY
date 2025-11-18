#include "USBThread.hpp"
#include "MessageSender.hpp"
#include "cy_retarget_io.h"
#include "cyabs_rtos_impl.h"
#include <string.h>

namespace Threads {

USBThread::USBThread(MessageSystem::NodeID nodeID)
    : Thread<USBThread>("USB thread", 512, CY_RTOS_PRIORITY_HIGH, nodeID) {}

void USBThread::onEntry() {}

void USBThread::onExit() {}

void USBThread::run() {
  vTaskDelay(pdMS_TO_TICKS(1));
  size_t size = m_ptr - m_buffer;
  if (cyhal_uart_getc(&cy_retarget_io_uart_obj, m_ptr, 1) == CY_RSLT_SUCCESS)
    m_ptr++;
  else if (size) {
    forwardMessage();
  }
}

void USBThread::handleRecievedMessage() {
  auto str = m_message.toString();
  size_t size = str.size() + 1;
  cyhal_uart_write(&cy_retarget_io_uart_obj, (void *)(str.c_str()), &size);
}

void USBThread::forwardMessage() {
  auto messageString = std::string{(char *)(m_buffer)};
  MessageSystem::MessageSender::sendMessage(
      this, MessageSystem::Message::fromString(messageString));
  m_ptr = m_buffer;
  memset(m_buffer, 0, sizeof(m_buffer));
}

} // namespace Threads