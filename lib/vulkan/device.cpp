#include "device.hpp"

#include "queue.hpp"

namespace vulkan
{
buffer device::create_buffer(VkBufferCreateInfo const &info) const
{
  return internal::make_unique<vkCreateBuffer, vkDestroyBuffer, VkBuffer>(_smart_ptr, &info);
}

buffer_view device::create_buffer_view(VkBufferViewCreateInfo const &info) const
{
  return internal::make_unique<vkCreateBufferView, vkDestroyBufferView, VkBufferView>(_smart_ptr, &info);
}

command_buffers device::allocate_command_buffers(VkCommandBufferAllocateInfo const &info) const
{
  auto const pool = _registered_command_pools.find(info.commandPool);
  if(pool == _registered_command_pools.end() or pool->second.expired())
    throw std::runtime_error(std::source_location::current().function_name());
  return internal::make_collection<vkAllocateCommandBuffers, vkFreeCommandBuffers, VkCommandBuffer, command_pool>(
    pool->second.lock(),
    &info,
    info.commandBufferCount);
}

command_pool device::create_command_pool(VkCommandPoolCreateInfo const &info) const
{
  auto pool = internal::make_shared<vkCreateCommandPool, vkDestroyCommandPool, VkCommandPool>(_smart_ptr, &info);
  _registered_command_pools.emplace(pool.get(), pool._smart_ptr);
  return pool;
}

descriptor_pool device::create_descriptor_pool(VkDescriptorPoolCreateInfo const &info) const
{
  auto pool = internal::make_shared<vkCreateDescriptorPool, vkDestroyDescriptorPool, VkDescriptorPool>(_smart_ptr, &info);
  _registered_descriptor_pools.emplace(pool.get(), pool._smart_ptr);
  return pool;
}

descriptor_set_layout device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const &info) const
{
  return internal::make_unique<vkCreateDescriptorSetLayout, vkDestroyDescriptorSetLayout, VkDescriptorSetLayout>(_smart_ptr,
                                                                                                                 &info);
}

descriptor_sets device::allocate_descriptor_sets(VkDescriptorSetAllocateInfo const &info) const
{
  auto const pool = _registered_descriptor_pools.find(info.descriptorPool);
  if(pool == _registered_descriptor_pools.end() or pool->second.expired())
    throw std::runtime_error(std::source_location::current().function_name());
  return internal::make_collection<vkAllocateDescriptorSets, vkFreeDescriptorSets, VkDescriptorSet, descriptor_pool>(
    pool->second.lock(),
    &info,
    info.descriptorSetCount);
}

device_memory device::allocate_memory(VkMemoryAllocateInfo const &info) const
{
  return internal::make_unique<vkAllocateMemory, vkFreeMemory, VkDeviceMemory>(_smart_ptr, &info);
}

event device::create_event(VkEventCreateInfo const &info) const
{
  return internal::make_unique<vkCreateEvent, vkDestroyEvent, VkEvent>(_smart_ptr, &info);
}

fence device::create_fence(VkFenceCreateInfo const &info) const
{
  return internal::make_unique<vkCreateFence, vkDestroyFence, VkFence>(_smart_ptr, &info);
}

framebuffer device::create_framebuffer(VkFramebufferCreateInfo const &info) const
{
  return internal::make_unique<vkCreateFramebuffer, vkDestroyFramebuffer, VkFramebuffer>(_smart_ptr, &info);
}

image device::create_image(VkImageCreateInfo const &info) const
{
  return internal::make_unique<vkCreateImage, vkDestroyImage, VkImage>(_smart_ptr, &info);
}

image_view device::create_image_view(VkImageViewCreateInfo const &info) const
{
  return internal::make_unique<vkCreateImageView, vkDestroyImageView, VkImageView>(_smart_ptr, &info);
}

pipeline_cache device::create_pipeline_cache(VkPipelineCacheCreateInfo const &info) const
{
  return internal::make_unique<vkCreatePipelineCache, vkDestroyPipelineCache, VkPipelineCache>(_smart_ptr, &info);
}

pipeline_layout device::create_pipeline_layout(VkPipelineLayoutCreateInfo const &info) const
{
  return internal::make_unique<vkCreatePipelineLayout, vkDestroyPipelineLayout, VkPipelineLayout>(_smart_ptr, &info);
}

query_pool device::create_query_pool(VkQueryPoolCreateInfo const &info) const
{
  return internal::make_unique<vkCreateQueryPool, vkDestroyQueryPool, VkQueryPool>(_smart_ptr, &info);
}

queue device::get_device_queue(VkDeviceQueueInfo2 const &info) const noexcept
{
  auto ptr = VkQueue{};
  vkGetDeviceQueue2(get(), &info, &ptr);
  return queue(_smart_ptr, ptr);
}

render_pass device::create_render_pass(VkRenderPassCreateInfo2 const &info) const
{
  return internal::make_unique<vkCreateRenderPass2, vkDestroyRenderPass, VkRenderPass>(_smart_ptr, &info);
}

sampler device::create_sampler(VkSamplerCreateInfo const &info) const
{
  return internal::make_unique<vkCreateSampler, vkDestroySampler, VkSampler>(_smart_ptr, &info);
}

semaphore device::create_semaphore(VkSemaphoreCreateInfo const &info) const
{
  return internal::make_unique<vkCreateSemaphore, vkDestroySemaphore, VkSemaphore>(_smart_ptr, &info);
}

shader_module device::create_shader_module(VkShaderModuleCreateInfo const &info) const
{
  return internal::make_unique<vkCreateShaderModule, vkDestroyShaderModule, VkShaderModule>(_smart_ptr, &info);
}

khr::swapchain device::create_swapchain(VkSwapchainCreateInfoKHR const &info) const
{
  return internal::make_unique<vkCreateSwapchainKHR, vkDestroySwapchainKHR, VkSwapchainKHR>(_smart_ptr, &info);
}

device::device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice const ptr)
: _smart_ptr(ptr, [dispatcher](VkDevice const ptr) { vkDestroyDevice(ptr, nullptr); })
{
}
}
