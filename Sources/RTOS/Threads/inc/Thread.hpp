#pragma once

#include "MessageSender.hpp"
#include "Node.hpp"

namespace Threads {

template <class T> class Thread : public MessageSystem::Node {
public:
  virtual void onEntry() = 0;
  virtual void onExit() = 0;
  virtual void run() = 0;
  virtual void handleRecievedMessage() = 0;

  Thread(const Thread &) = delete;
  Thread(Thread &&) = delete;
  Thread &operator=(const Thread &) = delete;
  Thread &operator=(Thread &&) = delete;

protected:
  Thread(const char *const name, const configSTACK_DEPTH_TYPE stackSize,
         UBaseType_t priority, MessageSystem::NodeID nodeID);
  ~Thread() = default;

private:
  static void runThread(void *args);
};

template <class T>
Thread<T>::Thread(const char *const name,
                  const configSTACK_DEPTH_TYPE stackSize, UBaseType_t priority,
                  MessageSystem::NodeID nodeID)
    : MessageSystem::Node(nodeID) {
  xTaskCreate(runThread, name, stackSize, this, priority, nullptr);
}

template <class T> void Thread<T>::runThread(void *args) {
  T *thread = static_cast<T *>(args);
  MessageSystem::MessageSender::registerNode(thread);
  thread->onEntry();
  for (;;) {
    if (thread->checkMessageDelivered()) {
      thread->handleRecievedMessage();
    }
    thread->run();
  }
  thread->onExit();
}

} // namespace Threads