#pragma once

#include "BGT60TRXX.hpp"
#include "DCTCalculator.hpp"
#include "HelpSignaler.hpp"
#include "Node.hpp"
#include "PWMDrivenDevice.hpp"
#include "Thread.hpp"
#include "TimeStamp.hpp"
#include <functional>
#include <vector>

namespace Threads {

class RadarThread : public Thread<RadarThread> {
public:
  enum class RadarState : uint8_t { DISABLE, ENABLE };

  RadarThread(Drivers::BGT60TRXX &radarSensor,
              std::vector<std::reference_wrapper<Drivers::PWMDrivenDevice>>
                  &obtacleSignalers,
              Drivers::HelpSignaler &helpSignaler,
              MessageSystem::NodeID nodeID);
  ~RadarThread() = default;

  RadarThread(const RadarThread &) = delete;
  RadarThread(RadarThread &&) = delete;
  RadarThread &operator=(const RadarThread &) = delete;
  RadarThread &operator=(RadarThread &&) = delete;

  void onEntry() final;
  void onExit() final;
  void run() final;
  void handleRecievedMessage() final;

#ifndef UT
private:
#endif
  enum class ObstacleDetectionState : uint8_t {
    DISABLE,
    TURNING_ON,
    ENABLE,
    TURNING_OFF,
  };

  void handleCommandMessage();
  void handleRadarMessage();
  void readDataFromRadar();
  void detectObstacles() const;
  void evaluateState();
  bool giveChangeSignal();
  void switchChangeSignal();

  Drivers::BGT60TRXX &m_radarSensor;
  std::vector<std::reference_wrapper<Drivers::PWMDrivenDevice>>
      &m_obstacleSignalers;
  Drivers::HelpSignaler &m_helpSignaler;

  ObstacleDetectionState m_obstacleDetectionState =
      ObstacleDetectionState::DISABLE;
  DCTCalculator m_dctCalculator;
  uint8_t m_changeSignalCounter = 0;
  bool m_changeSignalState = false;
  TimeStamp m_changeSignalTimeStamp;

  static constexpr float m_obstacleDetectionMinValue = 2000.0f;
  static constexpr float m_obstacleDetectionMaxValue = 5000.0f;
  static constexpr size_t m_changeSignalDurationMS = 200;

  static constexpr uint8_t m_idleSignalCount = 3;
  static constexpr uint8_t m_helpSignalCount = 2;
  uint8_t m_changeSignalCount = m_idleSignalCount;
};

} // namespace Threads
