#pragma once

#include "dronecan_dsdl_dsdl_detail.hpp"

namespace DroneCANGeneratedDsdl::uavcan::equipment::esc
{
struct Status
{
  static constexpr const char* kFullName = "uavcan.equipment.esc.Status";
  static constexpr std::uint16_t kDataTypeId = 1034U;
  static constexpr std::uint64_t kDataTypeSignature = 0xA9AF28AEA2FBB254ULL;
  static constexpr std::size_t kMaxBitLength = 110U;
  static constexpr std::size_t kMinBitLength = 110U;
  static constexpr std::size_t kMaxPayloadSize = 14U;
  static constexpr bool kIsService = false;
  std::uint32_t error_count{};
  float voltage{};
  float current{};
  float temperature{};
  std::int32_t rpm{};
  std::uint8_t power_rating_pct{};
  std::uint8_t esc_index{};

  static std::size_t Encode(const Status& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao = true) noexcept;
  static bool EncodeTo(const Status& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao = true) noexcept;
  static bool Decode(const CanardRxTransfer& transfer, Status& out, bool tao = true) noexcept;
  static bool DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, Status& out, bool tao = true) noexcept;
};

inline std::size_t Status::Encode(const Status& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao) noexcept
{
  if ((buffer == nullptr) || (buffer_size < kMaxPayloadSize))
  {
    return 0U;
  }
  std::memset(buffer, 0, buffer_size);
  std::uint32_t bit_offset = 0U;
  if (!EncodeTo(msg, buffer, buffer_size, bit_offset, tao))
  {
    return 0U;
  }
  return static_cast<std::size_t>((bit_offset + 7U) / 8U);
}

inline bool Status::Decode(const CanardRxTransfer& transfer, Status& out, bool tao) noexcept
{
  std::uint32_t bit_offset = 0U;
  return DecodeFrom(transfer, bit_offset, out, tao);
}

inline bool Status::EncodeTo(const Status& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao) noexcept
{
  if (buffer == nullptr)
  {
    return false;
  }
  (void)tao;
  {
    const std::uint32_t value = static_cast<std::uint32_t>(msg.error_count);
    if (!detail::CanWriteBits(buffer_size, bit_offset, 32U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 32U, &value);
    bit_offset += 32U;
  }
  {
    const std::uint16_t value = canardConvertNativeFloatToFloat16(static_cast<float>(msg.voltage));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 16U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 16U, &value);
    bit_offset += 16U;
  }
  {
    const std::uint16_t value = canardConvertNativeFloatToFloat16(static_cast<float>(msg.current));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 16U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 16U, &value);
    bit_offset += 16U;
  }
  {
    const std::uint16_t value = canardConvertNativeFloatToFloat16(static_cast<float>(msg.temperature));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 16U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 16U, &value);
    bit_offset += 16U;
  }
  {
    const std::int32_t value = static_cast<std::int32_t>(detail::Clamp<std::int64_t>(static_cast<std::int64_t>(msg.rpm), -131072LL, 131071LL));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 18U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 18U, &value);
    bit_offset += 18U;
  }
  {
    const std::uint8_t value = static_cast<std::uint8_t>(detail::Clamp<std::uint64_t>(static_cast<std::uint64_t>(msg.power_rating_pct), 0ULL, 127ULL));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 7U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 7U, &value);
    bit_offset += 7U;
  }
  {
    const std::uint8_t value = static_cast<std::uint8_t>(detail::Clamp<std::uint64_t>(static_cast<std::uint64_t>(msg.esc_index), 0ULL, 31ULL));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 5U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 5U, &value);
    bit_offset += 5U;
  }
  return true;
}

inline bool Status::DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, Status& out, bool tao) noexcept
{
  const std::uint32_t payload_bit_length = detail::PayloadBitLength(transfer);
  (void)tao;
  {
    std::uint32_t value = 0;
    if (!detail::DecodeScalar(transfer, bit_offset, 32U, false, &value))
    {
      return false;
    }
    bit_offset += 32U;
    out.error_count = value;
  }
  {
    std::uint16_t value = 0U;
    if (!detail::DecodeScalar(transfer, bit_offset, 16U, false, &value))
    {
      return false;
    }
    bit_offset += 16U;
    out.voltage = canardConvertFloat16ToNativeFloat(value);
  }
  {
    std::uint16_t value = 0U;
    if (!detail::DecodeScalar(transfer, bit_offset, 16U, false, &value))
    {
      return false;
    }
    bit_offset += 16U;
    out.current = canardConvertFloat16ToNativeFloat(value);
  }
  {
    std::uint16_t value = 0U;
    if (!detail::DecodeScalar(transfer, bit_offset, 16U, false, &value))
    {
      return false;
    }
    bit_offset += 16U;
    out.temperature = canardConvertFloat16ToNativeFloat(value);
  }
  {
    std::int32_t value = 0;
    if (!detail::DecodeScalar(transfer, bit_offset, 18U, true, &value))
    {
      return false;
    }
    bit_offset += 18U;
    out.rpm = value;
  }
  {
    std::uint8_t value = 0;
    if (!detail::DecodeScalar(transfer, bit_offset, 7U, false, &value))
    {
      return false;
    }
    bit_offset += 7U;
    out.power_rating_pct = value;
  }
  {
    std::uint8_t value = 0;
    if (!detail::DecodeScalar(transfer, bit_offset, 5U, false, &value))
    {
      return false;
    }
    bit_offset += 5U;
    out.esc_index = value;
  }
  return bit_offset <= payload_bit_length;
}

}  // namespace DroneCANGeneratedDsdl::uavcan::equipment::esc
