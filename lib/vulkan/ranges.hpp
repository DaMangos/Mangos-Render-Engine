#pragma once

#include <limits>
#include <ranges>
#include <utility>

namespace vulkan::ranges
{
struct size_fn
{
    constexpr std::uint32_t operator()(std::ranges::contiguous_range auto &&range) const
    {
      if(std::ranges::size(std::forward<decltype(range)>(range)) > std::numeric_limits<std::uint32_t>::max())
        throw std::length_error("size");
      return static_cast<std::uint32_t>(std::ranges::size(std::forward<decltype(range)>(range)));
    }
};

constexpr auto size = size_fn{};
constexpr auto data = std::ranges::data;
}