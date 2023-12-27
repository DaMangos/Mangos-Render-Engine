#pragma once

#include <limits>
#include <ranges>
#include <source_location>
#include <utility>

namespace vulkan::ranges
{
struct size_fn
{
    constexpr std::uint32_t operator()(std::ranges::contiguous_range auto &range) const
    {
      if(std::ranges::size(range) > std::numeric_limits<std::uint32_t>::max())
        throw std::out_of_range(std::source_location::current().function_name());
      return static_cast<std::uint32_t>(std::ranges::size(range));
    }
};

constexpr auto size = size_fn{};
constexpr auto data = std::ranges::data;
}