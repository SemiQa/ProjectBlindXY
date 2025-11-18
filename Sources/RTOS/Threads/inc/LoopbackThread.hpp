#pragma once

#include "Node.hpp"
#include "Thread.hpp"

namespace Threads {

class LoopbackThread : public Thread<LoopbackThread> {
public:
  LoopbackThread(MessageSystem::NodeID nodeID);
  ~LoopbackThread() = default;

  LoopbackThread(const LoopbackThread &) = delete;
  LoopbackThread(LoopbackThread &&) = delete;
  LoopbackThread &operator=(const LoopbackThread &) = delete;
  LoopbackThread &operator=(LoopbackThread &&) = delete;

  void onEntry() final;
  void onExit() final;
  void run() final;
  void handleRecievedMessage() final;
};

} // namespace Threads