#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C"
{
#include "canard.h"
}

namespace DroneCANGeneratedDsdl
{
namespace detail
{
inline bool DecodeScalar(const CanardRxTransfer& transfer,
                         std::uint32_t bit_offset,
                         std::uint8_t bit_length,
                         bool is_signed,
                         void* out_value) noexcept
{
  return canardDecodeScalar(&transfer, bit_offset, bit_length, is_signed, out_value) == bit_length;
}

inline bool CanWriteBits(std::size_t buffer_size, std::uint32_t bit_offset, std::uint32_t bit_length) noexcept
{
  const std::uint64_t capacity_bits = static_cast<std::uint64_t>(buffer_size) * 8ULL;
  const std::uint64_t offset = static_cast<std::uint64_t>(bit_offset);
  return (offset <= capacity_bits) && (static_cast<std::uint64_t>(bit_length) <= (capacity_bits - offset));
}

inline std::uint32_t PayloadBitLength(const CanardRxTransfer& transfer) noexcept
{
  return static_cast<std::uint32_t>(transfer.payload_len) * 8U;
}

inline std::uint32_t RemainingBits(std::uint32_t payload_bit_length, std::uint32_t bit_offset) noexcept
{
  return (payload_bit_length > bit_offset) ? (payload_bit_length - bit_offset) : 0U;
}

template <typename T>
inline T Clamp(T value, T low, T high) noexcept
{
  return std::min(std::max(value, low), high);
}
}  // namespace detail
}
