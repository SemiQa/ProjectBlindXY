#include "Message.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

struct MessageShould : public Test {
  void SetUp() {}
};

TEST_F(MessageShould, ParseMessageFromString) {
  std::string str = "00:00:00:64:10:15141312111009080706050403020100";
  auto msg = MessageSystem::Message::fromString(str);
  EXPECT_EQ(msg.header.type, MessageSystem::MessageType::COMMAND);
  EXPECT_EQ(msg.header.source, MessageSystem::NodeID::LOOPBACK_THREAD);
  EXPECT_EQ(msg.header.destination, MessageSystem::NodeID::LOOPBACK_THREAD);
  EXPECT_EQ(msg.header.command, 'd');
  EXPECT_EQ(msg.header.dataSize, 16);
  EXPECT_EQ(msg.data.size(), 16);
  EXPECT_EQ(msg.data[0], 21);
  EXPECT_EQ(msg.data[3], 18);
  EXPECT_EQ(msg.data[15], 0);
}
