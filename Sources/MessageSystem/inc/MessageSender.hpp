#pragma once

#include "MessageProvider.hpp"
#include "Mutex.hpp"
#include <cstring>

namespace MessageSystem {

class MessageSender {
public:
  static MessageSender &getInstance();

  static void registerNode(Node *node);
  static void sendMessage(Node *source, Message message);
  static void sendMessage(Node *source, MessageType type, NodeID destintation,
                          char command);

  template <typename T>
  static void sendMessage(Node *source, MessageType type, NodeID destintation,
                          char command, T data);

private:
  MessageSender() = default;
  ~MessageSender() = default;

  MessageSender(const MessageSender &) = delete;
  MessageSender(MessageSender &&) = delete;
  MessageSender &operator=(const MessageSender &) = delete;
  MessageSender &operator=(MessageSender &&) = delete;

  Message generateMessage(MessageType type, NodeID desination,
                          char command) const;

  MessageProvider m_provider;
  Mutex m_mutex;
  static MessageSender instance;
};

template <typename T>
void MessageSender::sendMessage(Node *source, MessageType type,
                                NodeID destintation, char command, T data) {
  auto message = instance.generateMessage(type, destintation, command);
  auto dataSize = sizeof(T);
  message.header.dataSize = dataSize;
  message.data.resize(dataSize);
  std::memcpy(message.data.data(), &data, dataSize);
  sendMessage(source, message);
}

} // namespace MessageSystem