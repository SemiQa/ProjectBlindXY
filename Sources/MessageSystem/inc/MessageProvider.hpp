#pragma once
#include "Node.hpp"
#include <vector>

namespace MessageSystem {
class MessageProvider {

public:
  MessageProvider() = default;
  ~MessageProvider() = default;
  MessageProvider(const MessageProvider &) = delete;
  MessageProvider(MessageProvider &&) = delete;
  MessageProvider &operator=(const MessageProvider &) = delete;
  MessageProvider &operator=(MessageProvider &&) = delete;

  void registerNode(Node *node);
  void insertMessage(Message message) const;

private:
  std::vector<Node *> m_nodes;
};
} // namespace MessageSystem