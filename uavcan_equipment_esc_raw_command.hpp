#pragma once

#include "dronecan_dsdl_dsdl_detail.hpp"

namespace DroneCANGeneratedDsdl::uavcan::equipment::esc
{
struct RawCommand
{
  static constexpr const char* kFullName = "uavcan.equipment.esc.RawCommand";
  static constexpr std::uint16_t kDataTypeId = 1030U;
  static constexpr std::uint64_t kDataTypeSignature = 0x217F5C87D7EC951DULL;
  static constexpr std::size_t kMaxBitLength = 285U;
  static constexpr std::size_t kMinBitLength = 0U;
  static constexpr std::size_t kMaxPayloadSize = 36U;
  static constexpr bool kIsService = false;
  std::array<std::int16_t, 20U> cmd{}; std::size_t cmd_size = 0U;

  static std::size_t Encode(const RawCommand& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao = true) noexcept;
  static bool EncodeTo(const RawCommand& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao = true) noexcept;
  static bool Decode(const CanardRxTransfer& transfer, RawCommand& out, bool tao = true) noexcept;
  static bool DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, RawCommand& out, bool tao = true) noexcept;
};

inline std::size_t RawCommand::Encode(const RawCommand& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao) noexcept
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

inline bool RawCommand::Decode(const CanardRxTransfer& transfer, RawCommand& out, bool tao) noexcept
{
  std::uint32_t bit_offset = 0U;
  return DecodeFrom(transfer, bit_offset, out, tao);
}

inline bool RawCommand::EncodeTo(const RawCommand& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao) noexcept
{
  if (buffer == nullptr)
  {
    return false;
  }
  (void)tao;
  {
    const std::size_t count = std::min<std::size_t>(msg.cmd_size, 20U);
    if (tao)
    {
      for (std::size_t i = 0U; i < count; ++i)
      {
        {
          const std::int16_t value = static_cast<std::int16_t>(detail::Clamp<std::int64_t>(static_cast<std::int64_t>(msg.cmd[i]), -8192LL, 8191LL));
          if (!detail::CanWriteBits(buffer_size, bit_offset, 14U))
          {
            return false;
          }
          canardEncodeScalar(buffer, bit_offset, 14U, &value);
          bit_offset += 14U;
        }
      }
    }
    else
    {
      const std::size_t count = std::min<std::size_t>(msg.cmd_size, 20U);
      if (!detail::CanWriteBits(buffer_size, bit_offset, 5U))
      {
        return false;
      }
      std::uint64_t encoded_length = static_cast<std::uint64_t>(count);
      canardEncodeScalar(buffer, bit_offset, 5U, &encoded_length);
      bit_offset += 5U;
      for (std::size_t i = 0U; i < count; ++i)
      {
        {
          const std::int16_t value = static_cast<std::int16_t>(detail::Clamp<std::int64_t>(static_cast<std::int64_t>(msg.cmd[i]), -8192LL, 8191LL));
          if (!detail::CanWriteBits(buffer_size, bit_offset, 14U))
          {
            return false;
          }
          canardEncodeScalar(buffer, bit_offset, 14U, &value);
          bit_offset += 14U;
        }
      }
    }
  }
  return true;
}

inline bool RawCommand::DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, RawCommand& out, bool tao) noexcept
{
  const std::uint32_t payload_bit_length = detail::PayloadBitLength(transfer);
  (void)tao;
  {
    if (tao)
    {
      std::size_t count = 0U;
      while ((count < 20U) && (detail::RemainingBits(payload_bit_length, bit_offset) >= 14U))
      {
        const std::size_t i = count;
        {
          std::int16_t value = 0;
          if (!detail::DecodeScalar(transfer, bit_offset, 14U, true, &value))
          {
            return false;
          }
          bit_offset += 14U;
          out.cmd[i] = value;
        }
        ++count;
      }
      if (detail::RemainingBits(payload_bit_length, bit_offset) >= 8U)
      {
        return false;
      }
      out.cmd_size = count;
    }
    else
    {
      std::size_t count = 0U;
      std::uint64_t encoded_length = 0U;
      if (!detail::DecodeScalar(transfer, bit_offset, 5U, false, &encoded_length))
      {
        return false;
      }
      bit_offset += 5U;
      if (encoded_length > 20U)
      {
        return false;
      }
      count = static_cast<std::size_t>(encoded_length);
      out.cmd_size = count;
      for (std::size_t i = 0U; i < count; ++i)
      {
        {
          std::int16_t value = 0;
          if (!detail::DecodeScalar(transfer, bit_offset, 14U, true, &value))
          {
            return false;
          }
          bit_offset += 14U;
          out.cmd[i] = value;
        }
      }
    }
  }
  return bit_offset <= payload_bit_length;
}

}  // namespace DroneCANGeneratedDsdl::uavcan::equipment::esc
