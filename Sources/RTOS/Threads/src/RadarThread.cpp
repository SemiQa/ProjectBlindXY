#include "RadarThread.hpp"
#include "RadarThreadAPI.hpp"
#include "cyabs_rtos_impl.h"

namespace Threads {
RadarThread::RadarThread(
    Drivers::BGT60TRXX &radarSensor,
    std::vector<std::reference_wrapper<Drivers::PWMDrivenDevice>>
        &obstacleSignalers,
    Drivers::HelpSignaler &helpSignaler, MessageSystem::NodeID nodeID)
    : Thread<RadarThread>("Radar thread", 512, CY_RTOS_PRIORITY_NORMAL, nodeID),
      m_radarSensor(radarSensor), m_obstacleSignalers(obstacleSignalers),
      m_helpSignaler(helpSignaler) {}

void RadarThread::onEntry() {
  for (auto &signaler : m_obstacleSignalers)
    signaler.get().init();
  m_radarSensor.init();
  m_helpSignaler.init();
}

void RadarThread::onExit() {}

void RadarThread::run() {
  readDataFromRadar();
  evaluateState();
  m_helpSignaler.evaluate();
  vTaskDelay(pdMS_TO_TICKS(10));
}

void RadarThread::handleRecievedMessage() {
  switch (m_message.header.type) {
  case MessageSystem::MessageType::COMMAND:
    handleCommandMessage();
    break;
  default:
    return;
  }
}

void RadarThread::evaluateState() {
  switch (m_obstacleDetectionState) {
  case ObstacleDetectionState::ENABLE:
    detectObstacles();
    break;
  case ObstacleDetectionState::TURNING_ON:
    if (giveChangeSignal())
      m_obstacleDetectionState = ObstacleDetectionState::ENABLE;
    break;
  case ObstacleDetectionState::TURNING_OFF:
    if (giveChangeSignal())
      m_obstacleDetectionState = ObstacleDetectionState::DISABLE;
    break;
  default:
    break;
  }
}

void RadarThread::switchChangeSignal() {
  for (auto signaler : m_obstacleSignalers) {
    float val = 0.0f;
    if (!m_changeSignalState) {
      val = signaler.get().getMaxValue();
    }
    signaler.get().set(val);
  }
  if (m_changeSignalState)
    m_changeSignalCounter++;
  m_changeSignalState = !m_changeSignalState;
}

bool RadarThread::giveChangeSignal() {
  if (!(m_changeSignalState || m_changeSignalCounter)) {
    m_changeSignalTimeStamp.set(m_changeSignalDurationMS);
    for (auto signaler : m_obstacleSignalers)
      signaler.get().set(signaler.get().getMaxValue());
    m_changeSignalState = true;
    return false;
  }
  if (m_changeSignalTimeStamp.elapsed()) {
    switchChangeSignal();
  }
  if (m_changeSignalCounter == m_changeSignalCount) {
    m_changeSignalCounter = 0;
    return true;
  }
  return false;
}

void RadarThread::handleCommandMessage() {
  auto command =
      static_cast<MessageSystem::API::Radar::Command>(m_message.header.command);

  switch (command) {
  case MessageSystem::API::Radar::Command::RADAR_STATE:
    handleRadarMessage();
    break;
  default:
    return;
  }
}

void RadarThread::handleRadarMessage() {
  auto state = static_cast<RadarState>(m_message.data[0]);
  if (state == RadarState::ENABLE &&
      m_obstacleDetectionState == ObstacleDetectionState::DISABLE) {
    m_obstacleDetectionState = ObstacleDetectionState::TURNING_ON;
    m_changeSignalCount = 3;
    m_helpSignaler.enable();
  } else if (state == RadarState::DISABLE &&
             m_obstacleDetectionState == ObstacleDetectionState::ENABLE) {
    m_obstacleDetectionState = ObstacleDetectionState::TURNING_OFF;
    for (auto signaler : m_obstacleSignalers)
      signaler.get().set(.0f);
    m_changeSignalCount = 3;
    m_helpSignaler.disable();
  } else if (state == RadarState::ENABLE &&
             m_obstacleDetectionState == ObstacleDetectionState::ENABLE) {
    m_obstacleDetectionState = ObstacleDetectionState::TURNING_ON;
    m_helpSignaler.toggle();
    m_changeSignalCount =
        m_helpSignaler.getState() == Drivers::HelpSignaler::State::ACTIVE ? 2
                                                                          : 3;
  }
}

void RadarThread::readDataFromRadar() {
  if (m_radarSensor.readDataIfPossible()) {
    m_dctCalculator.push(m_radarSensor.getValues());
  }
}

void RadarThread::detectObstacles() const {
  auto val = m_dctCalculator.computeSTD();
  val = val >= m_obstacleDetectionMinValue ? val : 0.0f;
  for (auto &signaler : m_obstacleSignalers)
    signaler.get().set(val / m_obstacleDetectionMaxValue *
                       signaler.get().getMaxValue());
}

} // namespace Threads
