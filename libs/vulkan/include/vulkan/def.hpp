#pragma once

#include <compare>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
struct nullhandle_t final
{
    constexpr explicit nullhandle_t(int) noexcept
    {
    }

    constexpr std::strong_ordering operator<=>(nullhandle_t) noexcept
    {
      return std::strong_ordering::equal;
    }
};

inline constexpr auto nullhandle = nullhandle_t(0);
}
