#pragma once

#include <vulkan/vulkan.h>

#include <utility>

namespace vulkan
{
struct throw_if_error_t
{
    constexpr throw_if_error_t(int) noexcept
    {
    }

    VkResult operator()(VkResult const result) const;
};

inline constexpr auto throw_if_error = throw_if_error_t(0);

template <class ValueType>
std::pair<ValueType, VkResult const> operator|(std::pair<ValueType, VkResult const> && result, throw_if_error_t)
{
  return std::pair(std::move(result.first), throw_if_error(result.second));
}
}