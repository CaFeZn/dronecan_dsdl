#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: 由 DroneCAN DSDL 生成的 XRobot/LibXR 模块 / Generated XRobot/LibXR module
  from DroneCAN DSDL
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

#include "uavcan_equipment_esc_raw_command.hpp"
#include "uavcan_equipment_esc_status.hpp"
#include "uavcan_protocol_dynamic_node_id_allocation.hpp"

#include <array>
#include <cstdint>
#include <cstring>

extern "C"
{
#include "canard.h"
}

#include "app_framework.hpp"
#include "can.hpp"
#include "dronecan_core/DroneCANNode.hpp"
#include "dronecan_core/dronecan_types.hpp"
#include "libxr.hpp"
#include "timebase.hpp"

class DroneCANDsdl final : public LibXR::Application
{
 public:
  using UavcanEquipmentEscRawCommandCallback = void (*)(void*, const LibXR::DroneCAN::TransferMetadata&, const ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand&);
  using UavcanEquipmentEscStatusCallback = void (*)(void*, const LibXR::DroneCAN::TransferMetadata&, const ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status&);
  using UavcanProtocolDynamicNodeIdAllocationCallback = void (*)(void*, const LibXR::DroneCAN::TransferMetadata&, const ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation&);

  DroneCANDsdl(LibXR::HardwareContainer& hw,
                        LibXR::ApplicationManager& appmgr,
                        std::uint8_t node_id = 10U,
                        const char* can_alias = "can0",
                        const char* timebase_alias = "timebase",
                        const char* node_name = "org.libxr.dronecan.generated",
                        std::uint32_t node_status_period_ms = 1000U)
      : can_(*hw.FindOrExit<LibXR::CAN>({NormalizeCString(can_alias, "can0")})),
        timebase_(*hw.FindOrExit<LibXR::Timebase>({NormalizeCString(timebase_alias, "timebase")})),
        node_(can_, timebase_, node_arena_.data(), node_arena_.size(), MakeNodeConfig(node_status_period_ms)),
        uavcan_equipment_esc_raw_command_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanEquipmentEscRawCommandTransferStatic, this)),
        uavcan_equipment_esc_status_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanEquipmentEscStatusTransferStatic, this)),
        uavcan_protocol_dynamic_node_id_allocation_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanProtocolDynamicNodeIdAllocationTransferStatic, this))
  {
    (void)node_.SetNodeID(node_id);
    node_.SetNodeInfo(MakeNodeInfo(NormalizeCString(node_name, "org.libxr.dronecan.generated")));
    node_.SetNodeStatusMode(LibXR::DroneCAN::NodeMode::OPERATIONAL);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeSignature, uavcan_equipment_esc_raw_command_handler_);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeSignature, uavcan_equipment_esc_status_handler_);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeSignature, uavcan_protocol_dynamic_node_id_allocation_handler_);
    appmgr.Register(*this);
  }

  void OnMonitor() override
  {
    node_.Poll();
  }

  DroneCANCoreSupport::DroneCANNode& Node() noexcept
  {
    return node_;
  }

  const DroneCANCoreSupport::DroneCANNode& Node() const noexcept
  {
    return node_;
  }

  void SetUavcanEquipmentEscRawCommandCallback(void* context, UavcanEquipmentEscRawCommandCallback callback) noexcept
  {
    uavcan_equipment_esc_raw_command_context_ = context;
    uavcan_equipment_esc_raw_command_callback_ = callback;
  }

  LibXR::ErrorCode PublishUavcanEquipmentEscRawCommand(const ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand& message, std::uint8_t priority = CANARD_TRANSFER_PRIORITY_MEDIUM)
  {
    std::array<std::uint8_t, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kMaxPayloadSize> payload{};
    const std::size_t payload_size = ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::Encode(message, payload.data(), payload.size());
    return node_.Broadcast(::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeSignature, priority, LibXR::ConstRawData(payload.data(), payload_size));
  }

  void SetUavcanEquipmentEscStatusCallback(void* context, UavcanEquipmentEscStatusCallback callback) noexcept
  {
    uavcan_equipment_esc_status_context_ = context;
    uavcan_equipment_esc_status_callback_ = callback;
  }

  LibXR::ErrorCode PublishUavcanEquipmentEscStatus(const ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status& message, std::uint8_t priority = CANARD_TRANSFER_PRIORITY_MEDIUM)
  {
    std::array<std::uint8_t, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kMaxPayloadSize> payload{};
    const std::size_t payload_size = ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::Encode(message, payload.data(), payload.size());
    return node_.Broadcast(::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeSignature, priority, LibXR::ConstRawData(payload.data(), payload_size));
  }

  void SetUavcanProtocolDynamicNodeIdAllocationCallback(void* context, UavcanProtocolDynamicNodeIdAllocationCallback callback) noexcept
  {
    uavcan_protocol_dynamic_node_id_allocation_context_ = context;
    uavcan_protocol_dynamic_node_id_allocation_callback_ = callback;
  }

  LibXR::ErrorCode PublishUavcanProtocolDynamicNodeIdAllocation(const ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation& message, std::uint8_t priority = CANARD_TRANSFER_PRIORITY_MEDIUM)
  {
    std::array<std::uint8_t, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kMaxPayloadSize> payload{};
    const std::size_t payload_size = ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::Encode(message, payload.data(), payload.size());
    return node_.Broadcast(::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeSignature, priority, LibXR::ConstRawData(payload.data(), payload_size));
  }


 private:
  static constexpr std::size_t kNodeArenaSize = 4096U;

  static const char* NormalizeCString(const char* value, const char* fallback) noexcept
  {
    return (value != nullptr && value[0] != '\0') ? value : fallback;
  }

  static std::uint32_t NormalizePeriodMs(std::uint32_t period_ms) noexcept
  {
    return period_ms == 0U ? 1U : period_ms;
  }

  static LibXR::DroneCAN::Config MakeNodeConfig(std::uint32_t node_status_period_ms) noexcept
  {
    LibXR::DroneCAN::Config config{};
    config.node_status_period_us = static_cast<std::uint64_t>(NormalizePeriodMs(node_status_period_ms)) * 1000ULL;
    return config;
  }

  static LibXR::DroneCAN::NodeInfo MakeNodeInfo(const char* node_name)
  {
    LibXR::DroneCAN::NodeInfo info{};
    const char* normalized = NormalizeCString(node_name, "org.libxr.dronecan.generated");
    std::strncpy(info.name, normalized, LibXR::DroneCAN::MAX_NODE_NAME_LENGTH);
    info.name[LibXR::DroneCAN::MAX_NODE_NAME_LENGTH] = '\0';
    return info;
  }

  static void OnUavcanEquipmentEscRawCommandTransferStatic(bool, DroneCANDsdl* self, const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload)
  {
    if (self != nullptr)
    {
      self->OnUavcanEquipmentEscRawCommandTransfer(meta, payload);
    }
  }

  void OnUavcanEquipmentEscRawCommandTransfer(const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload) noexcept
  {
    CanardRxTransfer transfer{};
    transfer.payload_len = static_cast<std::uint16_t>(payload.size_);
    transfer.payload_head = static_cast<const std::uint8_t*>(payload.addr_);

    ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand decoded{};
    if (!::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::Decode(transfer, decoded))
    {
      return;
    }

    if (uavcan_equipment_esc_raw_command_callback_ != nullptr)
    {
      uavcan_equipment_esc_raw_command_callback_(uavcan_equipment_esc_raw_command_context_, meta, decoded);
    }
  }

  static void OnUavcanEquipmentEscStatusTransferStatic(bool, DroneCANDsdl* self, const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload)
  {
    if (self != nullptr)
    {
      self->OnUavcanEquipmentEscStatusTransfer(meta, payload);
    }
  }

  void OnUavcanEquipmentEscStatusTransfer(const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload) noexcept
  {
    CanardRxTransfer transfer{};
    transfer.payload_len = static_cast<std::uint16_t>(payload.size_);
    transfer.payload_head = static_cast<const std::uint8_t*>(payload.addr_);

    ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status decoded{};
    if (!::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::Decode(transfer, decoded))
    {
      return;
    }

    if (uavcan_equipment_esc_status_callback_ != nullptr)
    {
      uavcan_equipment_esc_status_callback_(uavcan_equipment_esc_status_context_, meta, decoded);
    }
  }

  static void OnUavcanProtocolDynamicNodeIdAllocationTransferStatic(bool, DroneCANDsdl* self, const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload)
  {
    if (self != nullptr)
    {
      self->OnUavcanProtocolDynamicNodeIdAllocationTransfer(meta, payload);
    }
  }

  void OnUavcanProtocolDynamicNodeIdAllocationTransfer(const LibXR::DroneCAN::TransferMetadata& meta, LibXR::ConstRawData payload) noexcept
  {
    CanardRxTransfer transfer{};
    transfer.payload_len = static_cast<std::uint16_t>(payload.size_);
    transfer.payload_head = static_cast<const std::uint8_t*>(payload.addr_);

    ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation decoded{};
    if (!::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::Decode(transfer, decoded))
    {
      return;
    }

    if (uavcan_protocol_dynamic_node_id_allocation_callback_ != nullptr)
    {
      uavcan_protocol_dynamic_node_id_allocation_callback_(uavcan_protocol_dynamic_node_id_allocation_context_, meta, decoded);
    }
  }


  LibXR::CAN& can_;
  LibXR::Timebase& timebase_;
  std::array<std::uint8_t, kNodeArenaSize> node_arena_{};
  DroneCANCoreSupport::DroneCANNode node_;
  LibXR::DroneCAN::TransferHandler uavcan_equipment_esc_raw_command_handler_;
  void* uavcan_equipment_esc_raw_command_context_ = nullptr;
  UavcanEquipmentEscRawCommandCallback uavcan_equipment_esc_raw_command_callback_ = nullptr;
  LibXR::DroneCAN::TransferHandler uavcan_equipment_esc_status_handler_;
  void* uavcan_equipment_esc_status_context_ = nullptr;
  UavcanEquipmentEscStatusCallback uavcan_equipment_esc_status_callback_ = nullptr;
  LibXR::DroneCAN::TransferHandler uavcan_protocol_dynamic_node_id_allocation_handler_;
  void* uavcan_protocol_dynamic_node_id_allocation_context_ = nullptr;
  UavcanProtocolDynamicNodeIdAllocationCallback uavcan_protocol_dynamic_node_id_allocation_callback_ = nullptr;
};

using dronecan_dsdl = DroneCANDsdl;
using DronecanDsdl = DroneCANDsdl;
