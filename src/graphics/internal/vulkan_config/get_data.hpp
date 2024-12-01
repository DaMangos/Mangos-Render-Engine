#pragma once

#include <ranges>

namespace graphics::internal::vulkan_config
{
struct get_data_fn
{
    constexpr explicit get_data_fn(int)
    {
    }

    [[nodiscard]]
    constexpr decltype(auto) operator()(std::ranges::contiguous_range auto & range) const noexcept(noexcept(std::ranges::data(range)))
    {
      return std::ranges::data(range);
    }
};

inline constexpr auto get_data = get_data_fn(0);
}