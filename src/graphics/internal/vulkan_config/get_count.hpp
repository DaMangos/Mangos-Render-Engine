#pragma once

#include <ranges>

namespace graphics::internal::vulkan_config
{
struct get_count_fn
{
    constexpr explicit get_count_fn(int)
    {
    }

    [[nodiscard]]
    constexpr std::uint32_t operator()(std::ranges::contiguous_range auto & range) const noexcept(noexcept(std::ranges::size(range)))
    {
      return static_cast<std::uint32_t>(std::ranges::size(range));
    }
};

inline constexpr auto get_count = get_count_fn(0);
}