#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
std::vector<vk::UniqueCommandBuffer> create_command_buffers(vk::Device const device, vk::CommandPool const command_pool);
}
