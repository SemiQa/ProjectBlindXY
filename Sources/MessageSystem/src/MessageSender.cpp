#include "MessageSender.hpp"

namespace MessageSystem {

MessageSender MessageSender::instance = {};

MessageSender &MessageSender::getInstance() { return instance; }

void MessageSender::registerNode(Node *node) {
  Lock lock{instance.m_mutex};
  instance.m_provider.registerNode(node);
}

void MessageSender::sendMessage(Node *source, Message message) {
  Lock lock{instance.m_mutex};
  message.header.source = source->getNodeID();
  instance.m_provider.insertMessage(message);
}

void MessageSender::sendMessage(Node *source, MessageType type,
                                NodeID destintation, char command) {
  sendMessage(source, instance.generateMessage(type, destintation, command));
}

Message MessageSender::generateMessage(MessageType type, NodeID destination,
                                       char command) const {
  Message message;
  message.header.type = type;
  message.header.destination = destination;
  message.header.command = command;
  return message;
}

} // namespace MessageSystem