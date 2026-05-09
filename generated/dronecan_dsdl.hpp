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
#include <cstdio>
#include <cstdint>
#include <cstring>

extern "C"
{
#include "canard.h"
}

#include "app_framework.hpp"
#include "can.hpp"
#include "dronecan_core/CanPoller.hpp"
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
  using UavcanEquipmentEscRawCommandTopicData = LibXR::DroneCAN::TopicMessage<::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand>;
  using UavcanEquipmentEscStatusTopicData = LibXR::DroneCAN::TopicMessage<::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status>;
  using UavcanProtocolDynamicNodeIdAllocationTopicData = LibXR::DroneCAN::TopicMessage<::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation>;

  static constexpr const char* kUavcanEquipmentEscRawCommandTopicName = "/dronecan/uavcan/equipment/esc/RawCommand";
  static constexpr const char* kUavcanEquipmentEscStatusTopicName = "/dronecan/uavcan/equipment/esc/Status";
  static constexpr const char* kUavcanProtocolDynamicNodeIdAllocationTopicName = "/dronecan/uavcan/protocol/dynamic_node_id/Allocation";
  static constexpr const char* kUavcanEquipmentEscRawCommandTxTopicName = "/dronecan/tx/uavcan/equipment/esc/RawCommand";
  static constexpr const char* kUavcanEquipmentEscStatusTxTopicName = "/dronecan/tx/uavcan/equipment/esc/Status";
  static constexpr const char* kUavcanProtocolDynamicNodeIdAllocationTxTopicName = "/dronecan/tx/uavcan/protocol/dynamic_node_id/Allocation";

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
        uavcan_equipment_esc_raw_command_topic_(LibXR::Topic::CreateTopic<UavcanEquipmentEscRawCommandTopicData>(kUavcanEquipmentEscRawCommandTopicName, nullptr, false, true, true)),
        uavcan_equipment_esc_status_topic_(LibXR::Topic::CreateTopic<UavcanEquipmentEscStatusTopicData>(kUavcanEquipmentEscStatusTopicName, nullptr, false, true, true)),
        uavcan_protocol_dynamic_node_id_allocation_topic_(LibXR::Topic::CreateTopic<UavcanProtocolDynamicNodeIdAllocationTopicData>(kUavcanProtocolDynamicNodeIdAllocationTopicName, nullptr, false, true, true)),
        uavcan_equipment_esc_raw_command_tx_topic_(LibXR::Topic::CreateTopic<UavcanEquipmentEscRawCommandTopicData>(kUavcanEquipmentEscRawCommandTxTopicName, nullptr, true, false, true)),
        uavcan_equipment_esc_status_tx_topic_(LibXR::Topic::CreateTopic<UavcanEquipmentEscStatusTopicData>(kUavcanEquipmentEscStatusTxTopicName, nullptr, true, false, true)),
        uavcan_protocol_dynamic_node_id_allocation_tx_topic_(LibXR::Topic::CreateTopic<UavcanProtocolDynamicNodeIdAllocationTopicData>(kUavcanProtocolDynamicNodeIdAllocationTxTopicName, nullptr, true, false, true)),
        uavcan_equipment_esc_raw_command_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanEquipmentEscRawCommandTransferStatic, this)),
        uavcan_equipment_esc_status_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanEquipmentEscStatusTransferStatic, this)),
        uavcan_protocol_dynamic_node_id_allocation_handler_(LibXR::DroneCAN::TransferHandler::Create(OnUavcanProtocolDynamicNodeIdAllocationTransferStatic, this)),
        uavcan_equipment_esc_raw_command_tx_callback_(LibXR::Topic::Callback::Create(OnUavcanEquipmentEscRawCommandTxTopicStatic, this)),
        uavcan_equipment_esc_status_tx_callback_(LibXR::Topic::Callback::Create(OnUavcanEquipmentEscStatusTxTopicStatic, this)),
        uavcan_protocol_dynamic_node_id_allocation_tx_callback_(LibXR::Topic::Callback::Create(OnUavcanProtocolDynamicNodeIdAllocationTxTopicStatic, this))
  {
    char poller_alias[32]{};
    MakePollerAlias(NormalizeCString(can_alias, "can0"), poller_alias, sizeof(poller_alias));
    can_poller_ = hw.Find<DroneCANCoreSupport::CanPoller>(
        {poller_alias, "can_poller", "dronecan_poller", "can1_poller", "can0_poller"});
    (void)node_.SetNodeID(node_id);
    node_.SetNodeInfo(MakeNodeInfo(NormalizeCString(node_name, "org.libxr.dronecan.generated")));
    node_.SetNodeStatusMode(LibXR::DroneCAN::NodeMode::OPERATIONAL);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::RawCommand::kDataTypeSignature, uavcan_equipment_esc_raw_command_handler_);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::equipment::esc::Status::kDataTypeSignature, uavcan_equipment_esc_status_handler_);
    (void)node_.RegisterTransferHandler(LibXR::DroneCAN::TransferKind::Message, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeId, ::DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id::Allocation::kDataTypeSignature, uavcan_protocol_dynamic_node_id_allocation_handler_);
    uavcan_equipment_esc_raw_command_tx_topic_.RegisterCallback(uavcan_equipment_esc_raw_command_tx_callback_);
    uavcan_equipment_esc_status_tx_topic_.RegisterCallback(uavcan_equipment_esc_status_tx_callback_);
    uavcan_protocol_dynamic_node_id_allocation_tx_topic_.RegisterCallback(uavcan_protocol_dynamic_node_id_allocation_tx_callback_);
    appmgr.Register(*this);
  }

  void OnMonitor() override
  {
    if (can_poller_ != nullptr)
    {
      can_poller_->Poll();
    }
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

  LibXR::Topic UavcanEquipmentEscRawCommandTopic() const noexcept
  {
    return uavcan_equipment_esc_raw_command_topic_;
  }

  LibXR::Topic UavcanEquipmentEscStatusTopic() const noexcept
  {
    return uavcan_equipment_esc_status_topic_;
  }

  LibXR::Topic UavcanProtocolDynamicNodeIdAllocationTopic() const noexcept
  {
    return uavcan_protocol_dynamic_node_id_allocation_topic_;
  }

  LibXR::Topic UavcanEquipmentEscRawCommandTxTopic() const noexcept
  {
    return uavcan_equipment_esc_raw_command_tx_topic_;
  }

  LibXR::Topic UavcanEquipmentEscStatusTxTopic() const noexcept
  {
    return uavcan_equipment_esc_status_tx_topic_;
  }

  LibXR::Topic UavcanProtocolDynamicNodeIdAllocationTxTopic() const noexcept
  {
    return uavcan_protocol_dynamic_node_id_allocation_tx_topic_;
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

  static std::uint8_t NormalizePriority(std::uint8_t priority) noexcept
  {
    return (priority <= CANARD_TRANSFER_PRIORITY_LOWEST) ? priority : CANARD_TRANSFER_PRIORITY_MEDIUM;
  }

  static void MakePollerAlias(const char* can_alias, char* out, std::size_t out_size) noexcept
  {
    if ((out == nullptr) || (out_size == 0U))
    {
      return;
    }
    const char* normalized = NormalizeCString(can_alias, "can0");
    (void)std::snprintf(out, out_size, "%s_poller", normalized);
    out[out_size - 1U] = '\0';
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

    UavcanEquipmentEscRawCommandTopicData topic_data{meta, decoded};
    uavcan_equipment_esc_raw_command_topic_.Publish(topic_data);

    if (uavcan_equipment_esc_raw_command_callback_ != nullptr)
    {
      uavcan_equipment_esc_raw_command_callback_(uavcan_equipment_esc_raw_command_context_, meta, decoded);
    }
  }

  static void OnUavcanEquipmentEscRawCommandTxTopicStatic(bool, DroneCANDsdl* self, LibXR::RawData& data)
  {
    if (self != nullptr)
    {
      self->OnUavcanEquipmentEscRawCommandTxTopic(data);
    }
  }

  void OnUavcanEquipmentEscRawCommandTxTopic(LibXR::RawData& data) noexcept
  {
    if ((data.addr_ == nullptr) || (data.size_ != sizeof(UavcanEquipmentEscRawCommandTopicData)))
    {
      return;
    }

    const auto& topic_data = *reinterpret_cast<const UavcanEquipmentEscRawCommandTopicData*>(data.addr_);
    (void)PublishUavcanEquipmentEscRawCommand(topic_data.message, NormalizePriority(topic_data.metadata.priority));
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

    UavcanEquipmentEscStatusTopicData topic_data{meta, decoded};
    uavcan_equipment_esc_status_topic_.Publish(topic_data);

    if (uavcan_equipment_esc_status_callback_ != nullptr)
    {
      uavcan_equipment_esc_status_callback_(uavcan_equipment_esc_status_context_, meta, decoded);
    }
  }

  static void OnUavcanEquipmentEscStatusTxTopicStatic(bool, DroneCANDsdl* self, LibXR::RawData& data)
  {
    if (self != nullptr)
    {
      self->OnUavcanEquipmentEscStatusTxTopic(data);
    }
  }

  void OnUavcanEquipmentEscStatusTxTopic(LibXR::RawData& data) noexcept
  {
    if ((data.addr_ == nullptr) || (data.size_ != sizeof(UavcanEquipmentEscStatusTopicData)))
    {
      return;
    }

    const auto& topic_data = *reinterpret_cast<const UavcanEquipmentEscStatusTopicData*>(data.addr_);
    (void)PublishUavcanEquipmentEscStatus(topic_data.message, NormalizePriority(topic_data.metadata.priority));
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

    UavcanProtocolDynamicNodeIdAllocationTopicData topic_data{meta, decoded};
    uavcan_protocol_dynamic_node_id_allocation_topic_.Publish(topic_data);

    if (uavcan_protocol_dynamic_node_id_allocation_callback_ != nullptr)
    {
      uavcan_protocol_dynamic_node_id_allocation_callback_(uavcan_protocol_dynamic_node_id_allocation_context_, meta, decoded);
    }
  }

  static void OnUavcanProtocolDynamicNodeIdAllocationTxTopicStatic(bool, DroneCANDsdl* self, LibXR::RawData& data)
  {
    if (self != nullptr)
    {
      self->OnUavcanProtocolDynamicNodeIdAllocationTxTopic(data);
    }
  }

  void OnUavcanProtocolDynamicNodeIdAllocationTxTopic(LibXR::RawData& data) noexcept
  {
    if ((data.addr_ == nullptr) || (data.size_ != sizeof(UavcanProtocolDynamicNodeIdAllocationTopicData)))
    {
      return;
    }

    const auto& topic_data = *reinterpret_cast<const UavcanProtocolDynamicNodeIdAllocationTopicData*>(data.addr_);
    (void)PublishUavcanProtocolDynamicNodeIdAllocation(topic_data.message, NormalizePriority(topic_data.metadata.priority));
  }


  LibXR::CAN& can_;
  LibXR::Timebase& timebase_;
  DroneCANCoreSupport::CanPoller* can_poller_ = nullptr;
  std::array<std::uint8_t, kNodeArenaSize> node_arena_{};
  DroneCANCoreSupport::DroneCANNode node_;
  LibXR::Topic uavcan_equipment_esc_raw_command_topic_;
  LibXR::Topic uavcan_equipment_esc_status_topic_;
  LibXR::Topic uavcan_protocol_dynamic_node_id_allocation_topic_;
  LibXR::Topic uavcan_equipment_esc_raw_command_tx_topic_;
  LibXR::Topic uavcan_equipment_esc_status_tx_topic_;
  LibXR::Topic uavcan_protocol_dynamic_node_id_allocation_tx_topic_;
  LibXR::DroneCAN::TransferHandler uavcan_equipment_esc_raw_command_handler_;
  void* uavcan_equipment_esc_raw_command_context_ = nullptr;
  UavcanEquipmentEscRawCommandCallback uavcan_equipment_esc_raw_command_callback_ = nullptr;
  LibXR::DroneCAN::TransferHandler uavcan_equipment_esc_status_handler_;
  void* uavcan_equipment_esc_status_context_ = nullptr;
  UavcanEquipmentEscStatusCallback uavcan_equipment_esc_status_callback_ = nullptr;
  LibXR::DroneCAN::TransferHandler uavcan_protocol_dynamic_node_id_allocation_handler_;
  void* uavcan_protocol_dynamic_node_id_allocation_context_ = nullptr;
  UavcanProtocolDynamicNodeIdAllocationCallback uavcan_protocol_dynamic_node_id_allocation_callback_ = nullptr;
  LibXR::Topic::Callback uavcan_equipment_esc_raw_command_tx_callback_;
  LibXR::Topic::Callback uavcan_equipment_esc_status_tx_callback_;
  LibXR::Topic::Callback uavcan_protocol_dynamic_node_id_allocation_tx_callback_;
};

using dronecan_dsdl = DroneCANDsdl;
using DronecanDsdl = DroneCANDsdl;
