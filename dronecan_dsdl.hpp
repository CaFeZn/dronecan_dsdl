#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: DroneCAN DSDL facade. Default instance only configures the
  base node and publishes uavcan.protocol.NodeStatus; project-specific DSDL
  handlers are generated separately and runtime values live in User/xrobot.yaml.
constructor_args:
- node_id: 10
- can_alias: can0
- timebase_alias: timebase
- node_name: org.libxr.dronecan.generated
- node_status_period_ms: 1000
template_args: []
required_hardware: can0 timebase
depends:
- CaFeZn/dronecan_core
=== END MANIFEST === */
// clang-format on

// Stable XRobot module entry. Generated implementation lives under `generated/`.
#include "generated/dronecan_dsdl.hpp"
