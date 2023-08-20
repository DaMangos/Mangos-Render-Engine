#pragma once

#include <mgo/memory.hpp>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
using window_handle = mgo::unique_handle<0, GLFWwindow *>;
using cursor_handle = mgo::unique_handle<0, GLFWcursor *>;
}