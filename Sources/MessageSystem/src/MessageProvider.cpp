#include "MessageProvider.hpp"
#include <algorithm>

namespace MessageSystem {

void MessageProvider::registerNode(Node *node) { m_nodes.push_back(node); }

void MessageProvider::insertMessage(Message message) const {
  auto node = std::find_if(m_nodes.begin(), m_nodes.end(), [&](auto node) {
    return node->getNodeID() == message.header.destination;
  });
  if (node == m_nodes.end())
    return;
  (*node)->insertMessage(message);
}

} // namespace MessageSystem