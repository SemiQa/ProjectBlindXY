#pragma once
#include "MessageSender.hpp"
#include "MotionThread.hpp"

namespace MessageSystem::API::Motion {
enum class Command : char {
  PREDICTION = 'p',
  MOTION_DATA = 'm',
};

static void sendPredictionData(Node *source, NodeID destination,
                               Threads::MotionThread::Gesture gesture) {
  MessageSender::sendMessage(source, MessageType::COMMAND, destination,
                             static_cast<char>(Command::PREDICTION), gesture);
}

[[maybe_unused]]
static void sendMotionData(Node *source, NodeID destination,
                           Drivers::BMI270::MotionData motionData) {
  MessageSender::sendMessage(source, MessageType::RESPONSE, destination,
                             static_cast<char>(Command::MOTION_DATA),
                             motionData);
}

[[maybe_unused]]
static void askMotionData(Node *source) {
  MessageSender::sendMessage(source, MessageType::COMMAND,
                             NodeID::MOTION_THREAD,
                             static_cast<char>(Command::MOTION_DATA));
}

} // namespace MessageSystem::API::Motion