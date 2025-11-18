#pragma once

#include "BMI270.hpp"
#include "GestureDetectionModel.h"
#include "Node.hpp"
#include "Thread.hpp"

namespace Threads {

class MotionThread : public Thread<MotionThread> {
public:
  enum class Gesture : uint8_t { UNKNOWN = 0x00, CIRCLE, SHAKE };

  MotionThread(Drivers::BMI270 &motionSensor, MessageSystem::NodeID nodeID);
  ~MotionThread() = default;

  MotionThread(const MotionThread &) = delete;
  MotionThread(MotionThread &&) = delete;
  MotionThread &operator=(const MotionThread &) = delete;
  MotionThread &operator=(MotionThread &&) = delete;

  void onEntry() final;
  void onExit() final;
  void run() final;
  void handleRecievedMessage() final;

#ifndef UT
private:
#endif
  typedef std::array<float, GESTURE_DETECTION_DATA_OUT_COUNT> PredictionData;

  void detectGesture();
  Gesture recogniseGesture(PredictionData &predictionData) const;

  Drivers::BMI270 &m_motionSensor;
};

} // namespace Threads