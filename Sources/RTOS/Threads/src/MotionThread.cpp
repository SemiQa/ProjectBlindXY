#include "MotionThread.hpp"
#include "MessageSender.hpp"
#include "MotionThreadAPI.hpp"
#include "RadarThread.hpp"
#include "RadarThreadAPI.hpp"
#include "cyabs_rtos_impl.h"
#include "task.h"

namespace Threads {

MotionThread::MotionThread(Drivers::BMI270 &motionSensor,
                           MessageSystem::NodeID nodeID)
    : Thread<MotionThread>("Motion thread", 512, CY_RTOS_PRIORITY_NORMAL,
                           nodeID),
      m_motionSensor(motionSensor) {}

void MotionThread::onEntry() {
  m_motionSensor.init();
  GESTURE_DETECTION_init();
}

void MotionThread::onExit() {}

void MotionThread::run() {
  m_motionSensor.readData();
  detectGesture();
  vTaskDelay(pdMS_TO_TICKS(10));
}

void MotionThread::detectGesture() {
  PredictionData predictionData;
  auto motionData = m_motionSensor.getData();
  GESTURE_DETECTION_enqueue(reinterpret_cast<float *>(&motionData));
  if (GESTURE_DETECTION_dequeue(predictionData.data()) !=
      GESTURE_DETECTION_RET_SUCCESS)
    return;

  auto gesture = recogniseGesture(predictionData);
  MessageSystem::API::Motion::sendPredictionData(
      this, MessageSystem::NodeID::USB_THREAD, gesture);

  RadarThread::RadarState radarState;
  switch (gesture) {
  case Gesture::CIRCLE:
    radarState = RadarThread::RadarState::ENABLE;
    break;
  case Gesture::SHAKE:
    radarState = RadarThread::RadarState::DISABLE;
    break;
  default:
    return;
  }

  MessageSystem::API::Radar::sendRadarState(this, radarState);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

MotionThread::Gesture
MotionThread::recogniseGesture(PredictionData &predictionData) const {
  const auto circleDetectionThreashold = .3f;
  const auto shakeDetectionThreashold = .7f;
  if (predictionData[static_cast<uint8_t>(Gesture::CIRCLE)] >
      circleDetectionThreashold) {
    return Gesture::CIRCLE;
  }

  if (predictionData[static_cast<uint8_t>(Gesture::SHAKE)] >
      shakeDetectionThreashold) {
    return Gesture::SHAKE;
  }
  return Gesture::UNKNOWN;
}

void MotionThread::handleRecievedMessage() {}

} // namespace Threads
