#pragma once

#include "Node.hpp"
#include "Thread.hpp"

namespace Threads {

class USBThread : public Thread<USBThread> {
public:
  USBThread(MessageSystem::NodeID nodeID);
  ~USBThread() = default;

  USBThread(const USBThread &) = delete;
  USBThread(USBThread &&) = delete;
  USBThread &operator=(const USBThread &) = delete;
  USBThread &operator=(USBThread &&) = delete;

  void onEntry() final;
  void onExit() final;
  void run() final;
  void handleRecievedMessage() final;

#ifndef UT
private:
#endif
  void forwardMessage();

  uint8_t m_buffer[100] = {0};
  uint8_t *m_ptr = m_buffer;
};

} // namespace Threads