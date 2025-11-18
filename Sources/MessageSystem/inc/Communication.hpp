#pragma once

#include <stdint.h>

namespace MessageSystem {
enum class NodeID : uint8_t {
  LOOPBACK_THREAD = 0x00,

  USB_THREAD = 0x10,

  MOTION_THREAD = 0x20,

  RADAR_THREAD = 0x30,
};
}