#include "LoopbackThread.hpp"
#include "MutexMock.hpp"
#include "TaskMock.hpp"
#include "USBThread.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

struct MessageExchangeShould : public Test {
  StrictMock<TaskMock> taskMock;
  StrictMock<MutexMock> mutexMock;

  void expectMutex(uint32_t times = 1) {
    EXPECT_CALL(mutexMock, xSemaphoreTake(_, _)).Times(times);
    EXPECT_CALL(mutexMock, xSemaphoreGive(_)).Times(times);
  }
};

TEST_F(MessageExchangeShould, TransferMessageProperly) {
  EXPECT_CALL(taskMock, xTaskCreate(_, _, _, _, _, _))
      .Times(2)
      .WillRepeatedly(Return(0));
  Threads::LoopbackThread loopbackThread{
      MessageSystem::NodeID::LOOPBACK_THREAD};
  Threads::USBThread usbThread{MessageSystem::NodeID::USB_THREAD};

  expectMutex(3);
  MessageSystem::MessageSender::registerNode(&loopbackThread);
  MessageSystem::MessageSender::registerNode(&usbThread);

  char messageStr[] = "00:00:00:05:03:020304\n";
  memcpy(usbThread.m_buffer, messageStr, sizeof(messageStr));
  usbThread.forwardMessage();

  messageStr[3] = '1';
  EXPECT_STREQ(messageStr, loopbackThread.m_message.toString().c_str());
}