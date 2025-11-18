#include "Node.hpp"

namespace MessageSystem {
Node::Node(NodeID nodeId) : m_nodeID(nodeId) {}

void Node::insertMessage(Message message) {
  m_message = message;
  m_newMessageDelivered = true;
}

NodeID Node::getNodeID() const { return m_nodeID; }

bool Node::checkMessageDelivered() {
  auto val = m_newMessageDelivered;
  m_newMessageDelivered = false;
  return val;
}

} // namespace MessageSystem