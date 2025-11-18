#include "RadarThread.hpp"
#include "GPIOMock.hpp"
#include "HelpSignaler.hpp"
#include "MathMock.hpp"
#include "PWMDrivenDevice.hpp"
#include "PWMMock.hpp"
#include "RadarMock.hpp"
#include "RadarThreadAPI.hpp"
#include "SPIMock.hpp"
#include "TaskMock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

struct RadarThreadShould
    : public TestWithParam<
          std::pair<Threads::RadarThread::RadarState,
                    Threads::RadarThread::ObstacleDetectionState>> {
  StrictMock<TaskMock> taskMock;
  StrictMock<MathMock> mathMock;

  SPIMock spi;
  RadarMock radarMock{spi};

  PWMMock motorPwm;
  Drivers::PWMDrivenDevice motor{motorPwm};
  PWMMock noiseMakerPwm;
  Drivers::PWMDrivenDevice noiseMaker{noiseMakerPwm};

  std::vector<std::reference_wrapper<Drivers::PWMDrivenDevice>>
      obstacleSignalers{motor, noiseMaker};

  GPIOMock helpDiodeMock;
  Drivers::HelpSignaler helpSignaler{helpDiodeMock, 500};

  Threads::RadarThread createRadarThread() {
    EXPECT_CALL(taskMock, xTaskCreate(_, _, _, _, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mathMock, sqrtf(_)).WillOnce(Return(1.0f));
    EXPECT_CALL(mathMock, arm_dct4_init_f32(_, _, _, _, _, _))
        .WillOnce(Return((arm_status){}));
    return Threads::RadarThread(radarMock, obstacleSignalers, helpSignaler,
                                MessageSystem::NodeID::RADAR_THREAD);
  }

  void configureMessage(Threads::RadarThread &radarThread,
                        Threads::RadarThread::RadarState radarState) {
    radarThread.m_message.header.type = MessageSystem::MessageType::COMMAND;
    radarThread.m_message.header.command =
        static_cast<uint8_t>(MessageSystem::API::Radar::Command::RADAR_STATE);
    radarThread.m_message.data.resize(1);
    radarThread.m_message.data[0] = static_cast<uint8_t>(radarState);
  }
};

TEST_P(RadarThreadShould, HandlesRadarStateCommand) {
  auto params = GetParam();
  auto radarState = params.first;
  auto detectionState = params.second;

  auto radarThread = createRadarThread();
  radarThread.m_obstacleDetectionState = detectionState;
  configureMessage(radarThread, radarState);

  radarThread.handleRecievedMessage();

  using DetectionState = Threads::RadarThread::ObstacleDetectionState;
  auto expectedState = detectionState == DetectionState::DISABLE
                           ? DetectionState::TURNING_ON
                           : DetectionState::TURNING_OFF;
  EXPECT_EQ(radarThread.m_obstacleDetectionState, expectedState);
}

INSTANTIATE_TEST_SUITE_P(
    RadarStateCommands, RadarThreadShould,
    Values(std::pair{Threads::RadarThread::RadarState::ENABLE,
                     Threads::RadarThread::ObstacleDetectionState::DISABLE},
           std::pair{Threads::RadarThread::RadarState::DISABLE,
                     Threads::RadarThread::ObstacleDetectionState::ENABLE}));
