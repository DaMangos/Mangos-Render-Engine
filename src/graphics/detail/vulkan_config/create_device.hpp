#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::detail::vulkan_config
{
[[nodiscard]]
vk::UniqueDevice create_device(vk::PhysicalDevice const physical_device, vk::SurfaceKHR const surface);
}
