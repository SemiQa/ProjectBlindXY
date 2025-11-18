#pragma once
#include "Communication.hpp"
#include "FreeRTOS.h"
#include "Message.hpp"
#include "task.h"

namespace MessageSystem {
class Node {
public:
  Node(const Node &) = delete;
  Node(Node &&) = delete;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) = delete;

  void insertMessage(Message message);
  bool checkMessageDelivered();
  NodeID getNodeID() const;

#ifndef UT
protected:
#endif
  Node(NodeID nodeID);
  ~Node() = default;

  NodeID m_nodeID;
  Message m_message;
  bool m_newMessageDelivered{false};
};
} // namespace MessageSystem