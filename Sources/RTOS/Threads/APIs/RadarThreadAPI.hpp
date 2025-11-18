#pragma once
#include "MessageSender.hpp"
#include "RadarThread.hpp"

namespace MessageSystem::API::Radar {
enum class Command : char {
  RADAR_STATE = 'r',
};

[[maybe_unused]]
static void sendRadarState(Node *source,
                           Threads::RadarThread::RadarState radarState) {
  MessageSender::sendMessage(source, MessageType::COMMAND, NodeID::RADAR_THREAD,
                             static_cast<char>(Command::RADAR_STATE),
                             radarState);
}
} // namespace MessageSystem::API::Radar
