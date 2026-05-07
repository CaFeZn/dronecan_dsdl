#pragma once

#include "dronecan_dsdl_dsdl_detail.hpp"

namespace DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id
{
struct Allocation
{
  static constexpr const char* kFullName = "uavcan.protocol.dynamic_node_id.Allocation";
  static constexpr std::uint16_t kDataTypeId = 1U;
  static constexpr std::uint64_t kDataTypeSignature = 0x0B2A812620A11D40ULL;
  static constexpr std::size_t kMaxBitLength = 141U;
  static constexpr std::size_t kMinBitLength = 8U;
  static constexpr std::size_t kMaxPayloadSize = 18U;
  static constexpr bool kIsService = false;
  static constexpr std::uint16_t MAX_REQUEST_PERIOD_MS = 1000U;
  static constexpr std::uint16_t MIN_REQUEST_PERIOD_MS = 600U;
  static constexpr std::uint16_t MAX_FOLLOWUP_DELAY_MS = 400U;
  static constexpr std::uint16_t MIN_FOLLOWUP_DELAY_MS = 0U;
  static constexpr std::uint16_t FOLLOWUP_TIMEOUT_MS = 500U;
  static constexpr std::uint8_t MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST = 6U;
  static constexpr std::uint8_t ANY_NODE_ID = 0U;
  std::uint8_t node_id{};
  bool first_part_of_unique_id{};
  std::array<std::uint8_t, 16U> unique_id{}; std::size_t unique_id_size = 0U;

  static std::size_t Encode(const Allocation& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao = true) noexcept;
  static bool EncodeTo(const Allocation& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao = true) noexcept;
  static bool Decode(const CanardRxTransfer& transfer, Allocation& out, bool tao = true) noexcept;
  static bool DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, Allocation& out, bool tao = true) noexcept;
};

inline std::size_t Allocation::Encode(const Allocation& msg, std::uint8_t* buffer, std::size_t buffer_size, bool tao) noexcept
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

inline bool Allocation::Decode(const CanardRxTransfer& transfer, Allocation& out, bool tao) noexcept
{
  std::uint32_t bit_offset = 0U;
  return DecodeFrom(transfer, bit_offset, out, tao);
}

inline bool Allocation::EncodeTo(const Allocation& msg, std::uint8_t* buffer, std::size_t buffer_size, std::uint32_t& bit_offset, bool tao) noexcept
{
  if (buffer == nullptr)
  {
    return false;
  }
  (void)tao;
  {
    const std::uint8_t value = static_cast<std::uint8_t>(detail::Clamp<std::uint64_t>(static_cast<std::uint64_t>(msg.node_id), 0ULL, 127ULL));
    if (!detail::CanWriteBits(buffer_size, bit_offset, 7U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 7U, &value);
    bit_offset += 7U;
  }
  {
    const bool value = (msg.first_part_of_unique_id != false);
    if (!detail::CanWriteBits(buffer_size, bit_offset, 1U))
    {
      return false;
    }
    canardEncodeScalar(buffer, bit_offset, 1U, &value);
    bit_offset += 1U;
  }
  {
    const std::size_t count = std::min<std::size_t>(msg.unique_id_size, 16U);
    if (tao)
    {
      for (std::size_t i = 0U; i < count; ++i)
      {
        {
          const std::uint8_t value = static_cast<std::uint8_t>(msg.unique_id[i]);
          if (!detail::CanWriteBits(buffer_size, bit_offset, 8U))
          {
            return false;
          }
          canardEncodeScalar(buffer, bit_offset, 8U, &value);
          bit_offset += 8U;
        }
      }
    }
    else
    {
      const std::size_t count = std::min<std::size_t>(msg.unique_id_size, 16U);
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
          const std::uint8_t value = static_cast<std::uint8_t>(msg.unique_id[i]);
          if (!detail::CanWriteBits(buffer_size, bit_offset, 8U))
          {
            return false;
          }
          canardEncodeScalar(buffer, bit_offset, 8U, &value);
          bit_offset += 8U;
        }
      }
    }
  }
  return true;
}

inline bool Allocation::DecodeFrom(const CanardRxTransfer& transfer, std::uint32_t& bit_offset, Allocation& out, bool tao) noexcept
{
  const std::uint32_t payload_bit_length = detail::PayloadBitLength(transfer);
  (void)tao;
  {
    std::uint8_t value = 0;
    if (!detail::DecodeScalar(transfer, bit_offset, 7U, false, &value))
    {
      return false;
    }
    bit_offset += 7U;
    out.node_id = value;
  }
  {
    bool value = false;
    if (!detail::DecodeScalar(transfer, bit_offset, 1U, false, &value))
    {
      return false;
    }
    bit_offset += 1U;
    out.first_part_of_unique_id = value;
  }
  {
    if (tao)
    {
      std::size_t count = 0U;
      while ((count < 16U) && (detail::RemainingBits(payload_bit_length, bit_offset) >= 8U))
      {
        const std::size_t i = count;
        {
          std::uint8_t value = 0;
          if (!detail::DecodeScalar(transfer, bit_offset, 8U, false, &value))
          {
            return false;
          }
          bit_offset += 8U;
          out.unique_id[i] = value;
        }
        ++count;
      }
      if (detail::RemainingBits(payload_bit_length, bit_offset) >= 8U)
      {
        return false;
      }
      out.unique_id_size = count;
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
      if (encoded_length > 16U)
      {
        return false;
      }
      count = static_cast<std::size_t>(encoded_length);
      out.unique_id_size = count;
      for (std::size_t i = 0U; i < count; ++i)
      {
        {
          std::uint8_t value = 0;
          if (!detail::DecodeScalar(transfer, bit_offset, 8U, false, &value))
          {
            return false;
          }
          bit_offset += 8U;
          out.unique_id[i] = value;
        }
      }
    }
  }
  return bit_offset <= payload_bit_length;
}

}  // namespace DroneCANGeneratedDsdl::uavcan::protocol::dynamic_node_id
