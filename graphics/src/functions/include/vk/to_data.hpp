#pragma once

#include <concepts>
#include <ranges>

namespace graphics::vk
{
[[nodiscard]]
inline constexpr auto *to_data(std::ranges::contiguous_range auto &container) noexcept
{
  return container.data();
}
}