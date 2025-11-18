#include "Message.hpp"

#include <string.h>

namespace MessageSystem {

std::string Message::toString() const {
  const uint8_t maxDataSize = 50;
  char buffer[sizeof(header) + maxDataSize + 1];
  memset(buffer, '\0', sizeof(buffer));
  sprintf(buffer,
          "%02x:%02x:%02x:%02x:%02x:", static_cast<uint8_t>(header.type),
          static_cast<uint8_t>(header.source),
          static_cast<uint8_t>(header.destination),
          static_cast<uint8_t>(header.command),
          static_cast<uint8_t>(header.dataSize));
  auto bufferPtr = buffer + sizeof(header) * 3;
  for (int i = 0; i < header.dataSize; i++) {
    sprintf(bufferPtr, "%02x", data[i]);
    bufferPtr += 2;
  }
  *bufferPtr = '\n';
  return std::string(buffer);
}

Message Message::fromString(std::string messageString) {
  std::vector<uint8_t> data;
  auto messageContent = messageString.c_str();

  auto header = parseHeader(&messageContent);

  auto &dataSize = header.dataSize;
  data.reserve(dataSize);
  for (uint8_t i = 0; i < dataSize; i++) {
    data.push_back(readNumber(&messageContent, 0));
    if (*messageContent == '\0') {
      dataSize = data.size();
      break;
    }
  }
  return {header, data};
}

MessageHeader Message::parseHeader(const char **messageContent) {
  MessageHeader header;

  header.type = static_cast<MessageType>(readNumber(messageContent, 1));
  header.source = static_cast<NodeID>(readNumber(messageContent, 1));
  header.destination = static_cast<NodeID>(readNumber(messageContent, 1));
  header.command = static_cast<char>(readNumber(messageContent, 1));
  header.dataSize = static_cast<uint8_t>(readNumber(messageContent, 1));
  return header;
}

uint8_t Message::readNumber(const char **messageContent, uint8_t paddingSize) {
  char numberBuffer[3] = "";
  memcpy(numberBuffer, *messageContent, 2);
  *messageContent += 2 + paddingSize;
  return static_cast<uint8_t>(strtol(numberBuffer, nullptr, 16));
}
} // namespace MessageSystem