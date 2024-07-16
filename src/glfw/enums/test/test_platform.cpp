#include <gtest/gtest.h>

#include "../to_platform.hpp"

static_assert(glfw::to_platform(GLFW_PLATFORM_COCOA) == glfw::platform::cocoa);
static_assert(glfw::to_platform(GLFW_PLATFORM_X11) == glfw::platform::x11);
static_assert(glfw::to_platform(GLFW_PLATFORM_WAYLAND) == glfw::platform::wayland);
static_assert(glfw::to_platform(GLFW_PLATFORM_WIN32) == glfw::platform::win32);
static_assert(glfw::to_platform(GLFW_PLATFORM_NULL) == glfw::platform::unknown);

static_assert(glfw::to_int(glfw::platform::cocoa) == GLFW_PLATFORM_COCOA);
static_assert(glfw::to_int(glfw::platform::x11) == GLFW_PLATFORM_X11);
static_assert(glfw::to_int(glfw::platform::wayland) == GLFW_PLATFORM_WAYLAND);
static_assert(glfw::to_int(glfw::platform::win32) == GLFW_PLATFORM_WIN32);
static_assert(glfw::to_int(glfw::platform::unknown) == GLFW_PLATFORM_NULL);
