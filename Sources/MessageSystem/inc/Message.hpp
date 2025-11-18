#pragma once

#include "Communication.hpp"
#include <string>
#include <vector>

namespace MessageSystem {

enum class MessageType : uint8_t { COMMAND, RESPONSE };

struct MessageHeader {
  MessageType type;
  NodeID source;
  NodeID destination;
  char command;
  uint8_t dataSize{0};
};

struct Message {
  MessageHeader header;
  std::vector<uint8_t> data;

  std::string toString() const;

  static Message fromString(std::string string);

private:
  static MessageHeader parseHeader(const char **messageContent);
  static uint8_t readNumber(const char **messageContent, uint8_t paddingSize);
};

} // namespace MessageSystem