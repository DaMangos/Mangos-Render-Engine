#pragma once

#include <glfw/enums/platform.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
[[nodiscard]]
constexpr platform to_platform(int const platform) noexcept
{
  switch(platform)
  {
    case GLFW_PLATFORM_COCOA :
      return platform::cocoa;
    case GLFW_PLATFORM_X11 :
      return platform::x11;
    case GLFW_PLATFORM_WAYLAND :
      return platform::wayland;
    case GLFW_PLATFORM_WIN32 :
      return platform::win32;
    default :
      return platform::unknown;
  }
}

[[nodiscard]]
constexpr int to_int(platform const platform) noexcept
{
  switch(platform)
  {
    case platform::cocoa :
      return GLFW_PLATFORM_COCOA;
    case platform::x11 :
      return GLFW_PLATFORM_X11;
    case platform::wayland :
      return GLFW_PLATFORM_WAYLAND;
    case platform::win32 :
      return GLFW_PLATFORM_WIN32;
    default :
      return GLFW_PLATFORM_NULL;
  }
}
}