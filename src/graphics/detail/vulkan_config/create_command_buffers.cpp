#include "create_command_buffers.hpp"

std::vector<vk::UniqueCommandBuffer> graphics::detail::vulkan_config::create_command_buffers(vk::Device const      device,
                                                                                             vk::CommandPool const command_pool)
{
  vk::CommandBufferAllocateInfo const allocate_info = {
    .commandPool        = command_pool,
    .level              = vk::CommandBufferLevel::ePrimary,
    .commandBufferCount = 2,
  };

  return device.allocateCommandBuffersUnique(allocate_info);
}
