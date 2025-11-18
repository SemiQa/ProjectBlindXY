#include "LoopbackThread.hpp"
#include "MessageSender.hpp"
#include "cyabs_rtos_impl.h"
#include "task.h"
namespace Threads {

LoopbackThread::LoopbackThread(MessageSystem::NodeID nodeID)
    : Thread<LoopbackThread>("Loopback thread", 512, CY_RTOS_PRIORITY_NORMAL,
                             nodeID) {}

void LoopbackThread::onEntry() {}

void LoopbackThread::onExit() {}

void LoopbackThread::run() { vTaskDelay(pdMS_TO_TICKS(10)); }

void LoopbackThread::handleRecievedMessage() {
  if (m_message.header.type != MessageSystem::MessageType::COMMAND)
    return;
  m_message.header.type = MessageSystem::MessageType::RESPONSE;
  m_message.header.destination = m_message.header.source;
  MessageSystem::MessageSender::sendMessage(this, m_message);
}

} // namespace Threads