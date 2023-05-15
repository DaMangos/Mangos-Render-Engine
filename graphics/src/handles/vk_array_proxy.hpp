#pragma once

#include <concepts>
#include <cstdint>
#include <ranges>
#include <stdexcept>

namespace graphics::vk
{
[[nodiscard]]
inline constexpr std::uint32_t to_count(std::ranges::contiguous_range auto &container)
{
  if (container.size() > UINT32_MAX)
    throw std::out_of_range("container size is too large");
  return static_cast<std::uint32_t>(container.size());
}

[[nodiscard]]
inline constexpr auto *to_data(std::ranges::contiguous_range auto &container) noexcept
{
  return container.data();
}
}