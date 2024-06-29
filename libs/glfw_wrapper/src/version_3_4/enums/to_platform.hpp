#pragma once

#include <glfw_wrapper/version_3_4/enums/platform.hpp>

#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
inline namespace version_3_4
{
[[nodiscard]]
constexpr platform to_platform(int const platform)
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
    case GLFW_PLATFORM_NULL :
      return platform::unknown;
  }
  throw std::invalid_argument("invalid platform");
}

[[nodiscard]]
constexpr int to_int(platform const platform)
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
    case platform::unknown :
      return GLFW_PLATFORM_NULL;
  }
  throw std::invalid_argument("invalid platform");
}
}
}