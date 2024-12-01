#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
vk::UniqueSurfaceKHR create_surface(vk::Instance const instance, GLFWwindow * const window);
}