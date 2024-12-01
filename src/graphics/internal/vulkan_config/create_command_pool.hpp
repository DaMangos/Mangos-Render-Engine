#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
vk::UniqueCommandPool create_command_pool(vk::Device const device, vk::PhysicalDevice const physical_device);
}
