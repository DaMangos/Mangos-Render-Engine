#include "create_command_pool.hpp"

#include "find_queue_family_index.hpp"

vk::UniqueCommandPool graphics::internal::vulkan_config::create_command_pool(vk::Device const device, vk::PhysicalDevice const physical_device)
{
  auto const graphics_queue_family_index = find_queue_family_index(physical_device.getQueueFamilyProperties(), vk::QueueFlagBits::eGraphics);

  vk::CommandPoolCreateInfo const info = {
    .flags            = vk::CommandPoolCreateFlagBits::eTransient | vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
    .queueFamilyIndex = graphics_queue_family_index.value(),
  };

  return device.createCommandPoolUnique(info);
}
