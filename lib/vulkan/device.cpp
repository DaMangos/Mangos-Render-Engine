#include "device.hpp"

#include "command_buffers.hpp"
#include "descriptor_sets.hpp"
#include "queue.hpp"

namespace vulkan
{
VkDevice device::get() const noexcept
{
  return _handle.get();
}

buffer device::create_buffer(VkBufferCreateInfo const &create_info) const
{
  VkBuffer ptr = VK_NULL_HANDLE;
  switch(vkCreateBuffer(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return buffer(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkBuffer: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkBuffer: out of device memory");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR :
      throw std::runtime_error("failed to create VkBuffer: invalid opaque capture address");
    default :
      throw std::runtime_error("failed to create VkBuffer: unknown error");
  }
}

buffer_view device::create_buffer_view(VkBufferViewCreateInfo const &create_info) const
{
  VkBufferView ptr = VK_NULL_HANDLE;
  switch(vkCreateBufferView(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return buffer_view(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkBufferView: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkBufferView: out of device memory");
    default :
      throw std::runtime_error("failed to create VkBufferView: unknown error");
  }
}

command_buffers device::allocate_command_buffers(VkCommandBufferAllocateInfo const &allocate_info) const
{
  auto const pool = _registered_command_pools.find(allocate_info.commandPool);
  if(pool == _registered_command_pools.end())
    throw std::runtime_error("failed to allocate VkCommandBuffers: VkCommandPool is not registered");
  if(pool->second.expired())
    throw std::runtime_error("failed to allocate VkCommandBuffers: VkCommandPool has expired");
  std::vector<VkCommandBuffer> ptrs(allocate_info.commandBufferCount);
  switch(vkAllocateCommandBuffers(get(), &allocate_info, ptrs.data()))
  {
    case VK_SUCCESS :
      return command_buffers(pool->second.lock(), std::move(ptrs));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to allocate VkCommandBuffers: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to allocate VkCommandBuffers: out of device memory");
    case VK_ERROR_OUT_OF_POOL_MEMORY :
      throw std::runtime_error("failed to allocate VkCommandBuffers: out of pool memory");
    default :
      throw std::runtime_error("failed to allocate VkCommandBuffers: unknown error");
  }
}

command_pool device::create_command_pool(VkCommandPoolCreateInfo const &create_info) const
{
  VkCommandPool ptr = VK_NULL_HANDLE;
  switch(vkCreateCommandPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
    {
      command_pool command_pool(_handle, ptr);
      _registered_command_pools.emplace(ptr, command_pool._handle);
      return command_pool;
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkCommandPool: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkCommandPool: out of device memory");
    default :
      throw std::runtime_error("failed to create VkCommandPool: unknown error");
  }
}

descriptor_pool device::create_descriptor_pool(VkDescriptorPoolCreateInfo const &create_info) const
{
  VkDescriptorPool ptr = VK_NULL_HANDLE;
  switch(vkCreateDescriptorPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
    {
      descriptor_pool descriptor_pool(_handle, ptr);
      _registered_descriptor_pools.emplace(ptr, descriptor_pool._handle);
      return descriptor_pool;
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorPool: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorPool: out of device memory");
    case VK_ERROR_FRAGMENTATION_EXT :
      throw std::runtime_error("failed to create VkDescriptorPool: fragmentation");
    default :
      throw std::runtime_error("failed to create VkDescriptorPool: unknown error");
  }
}

descriptor_set_layout device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const &create_info) const
{
  VkDescriptorSetLayout ptr = VK_NULL_HANDLE;
  switch(vkCreateDescriptorSetLayout(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return descriptor_set_layout(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: out of device memory");
    default :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: unknown error");
  }
}

descriptor_sets device::allocate_descriptor_sets(VkDescriptorSetAllocateInfo const &allocate_info) const
{
  auto const pool = _registered_descriptor_pools.find(allocate_info.descriptorPool);
  if(pool == _registered_descriptor_pools.end())
    throw std::runtime_error("failed to allocate VkDescriptorSets: VkDescriptorPool is not registered");
  if(pool->second.expired())
    throw std::runtime_error("failed to allocate VkDescriptorSets: VkDescriptorPool has expired");
  std::vector<VkDescriptorSet> ptrs(allocate_info.descriptorSetCount);
  switch(vkAllocateDescriptorSets(get(), &allocate_info, ptrs.data()))
  {
    case VK_SUCCESS :
      return descriptor_sets(pool->second.lock(), std::move(ptrs));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to allocate VkDescriptorSets: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to allocate VkDescriptorSets: out of device memory");
    case VK_ERROR_FRAGMENTED_POOL :
      throw std::runtime_error("failed to allocate VkDescriptorSets: fragmented pool");
    case VK_ERROR_OUT_OF_POOL_MEMORY :
      throw std::runtime_error("failed to allocate VkDescriptorSets: out of pool memory");
    default :
      throw std::runtime_error("failed to allocate VkDescriptorSets: unknown error");
  }
}

device_memory device::allocate_memory(VkMemoryAllocateInfo const &allocate_info) const
{
  VkDeviceMemory ptr = VK_NULL_HANDLE;
  switch(vkAllocateMemory(get(), &allocate_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return device_memory(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to allocate VkDeviceMemory: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to allocate VkDeviceMemory: out of device memory");
    case VK_ERROR_INVALID_EXTERNAL_HANDLE :
      throw std::runtime_error("failed to allocate VkDeviceMemory: invalid external handle");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR :
      throw std::runtime_error("failed to allocate VkDeviceMemory: invalid opaque capture address");
    default :
      throw std::runtime_error("failed to allocate VkDeviceMemory: unknown error");
  }
}

event device::create_event(VkEventCreateInfo const &create_info) const
{
  VkEvent ptr = VK_NULL_HANDLE;
  switch(vkCreateEvent(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return event(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkEvent: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkEvent: out of device memory");
    default :
      throw std::runtime_error("failed to create VkEvent: unknown error");
  }
}

fence device::create_fence(VkFenceCreateInfo const &create_info) const
{
  VkFence ptr = VK_NULL_HANDLE;
  switch(vkCreateFence(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return fence(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkFence: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkFence: out of device memory");
    default :
      throw std::runtime_error("failed to create VkFence: unknown error");
  }
}

framebuffer device::create_framebuffer(VkFramebufferCreateInfo const &create_info) const
{
  VkFramebuffer ptr = VK_NULL_HANDLE;
  switch(vkCreateFramebuffer(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return framebuffer(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkFramebuffer: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkFramebuffer: out of device memory");
    default :
      throw std::runtime_error("failed to create VkFramebuffer: unknown error");
  }
}

image device::create_image(VkImageCreateInfo const &create_info) const
{
  VkImage ptr = VK_NULL_HANDLE;
  switch(vkCreateImage(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return image(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkImage: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkImage: out of device memory");
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT :
      throw std::runtime_error("failed to create VkImage: compression exhausted");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR :
      throw std::runtime_error("failed to create VkImage: invalid opaque capture address");
    default :
      throw std::runtime_error("failed to create VkImage: unknown error");
  }
}

image_view device::create_image_view(VkImageViewCreateInfo const &create_info) const
{
  VkImageView ptr = VK_NULL_HANDLE;
  switch(vkCreateImageView(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return image_view(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkImageView: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkImageView: out of device memory");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR :
      throw std::runtime_error("failed to create VkImageView: invalid opaque capture address");
    default :
      throw std::runtime_error("failed to create VkImageView: unknown error");
  }
}

pipeline_cache device::create_pipeline_cache(VkPipelineCacheCreateInfo const &create_info) const
{
  VkPipelineCache ptr = VK_NULL_HANDLE;
  switch(vkCreatePipelineCache(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return pipeline_cache(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipelineCache: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipelineCache: out of device memory");
    default :
      throw std::runtime_error("failed to create VkPipelineCache: unknown error");
  }
}

pipeline_layout device::create_pipeline_layout(VkPipelineLayoutCreateInfo const &create_info) const
{
  VkPipelineLayout ptr = VK_NULL_HANDLE;
  switch(vkCreatePipelineLayout(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return pipeline_layout(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipelineLayout: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipelineLayout: out of device memory");
    default :
      throw std::runtime_error("failed to create VkPipelineLayout: unknown error");
  }
}

query_pool device::create_query_pool(VkQueryPoolCreateInfo const &create_info) const
{
  VkQueryPool ptr = VK_NULL_HANDLE;
  switch(vkCreateQueryPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return query_pool(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkQueryPool: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkQueryPool: out of device memory");
    default :
      throw std::runtime_error("failed to create VkQueryPool: unknown error");
  }
}

queue device::get_device_queue(VkDeviceQueueInfo2 const &create_info) const
{
  VkQueue ptr = VK_NULL_HANDLE;
  vkGetDeviceQueue2(get(), &create_info, &ptr);
  return queue(_handle, ptr);
}

render_pass device::create_render_pass(VkRenderPassCreateInfo2 const &create_info) const
{
  VkRenderPass ptr = VK_NULL_HANDLE;
  switch(vkCreateRenderPass2(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return render_pass(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkRenderPass: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkRenderPass: out of device memory");
    default :
      throw std::runtime_error("failed to create VkRenderPass: unknown error");
  }
}

sampler device::create_sampler(VkSamplerCreateInfo const &create_info) const
{
  VkSampler ptr = VK_NULL_HANDLE;
  switch(vkCreateSampler(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return sampler(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkSampler: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkSampler: out of device memory");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR :
      throw std::runtime_error("failed to create VkSampler: invalid opaque capture address");
    default :
      throw std::runtime_error("failed to create VkSampler: unknown error");
  }
}

semaphore device::create_semaphore(VkSemaphoreCreateInfo const &create_info) const
{
  VkSemaphore ptr = VK_NULL_HANDLE;
  switch(vkCreateSemaphore(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return semaphore(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkSemaphore: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkSemaphore: out of device memory");
    default :
      throw std::runtime_error("failed to create VkSemaphore: unknown error");
  }
}

shader_module device::create_shader_module(VkShaderModuleCreateInfo const &create_info) const
{
  VkShaderModule ptr = VK_NULL_HANDLE;
  switch(vkCreateShaderModule(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return shader_module(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkShaderModule: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkShaderModule: out of device memory");
    case VK_ERROR_INVALID_SHADER_NV :
      throw std::runtime_error("failed to create VkShaderModule: invalid shader");
    default :
      throw std::runtime_error("failed to create VkShaderModule: unknown error");
  }
}

khr::swapchain device::create_swapchain(VkSwapchainCreateInfoKHR const &create_info) const
{
  VkSwapchainKHR ptr = VK_NULL_HANDLE;
  switch(vkCreateSwapchainKHR(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return khr::swapchain(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkSwapchainKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkSwapchainKHR: out of device memory");
    case VK_ERROR_DEVICE_LOST :
      throw std::runtime_error("failed to create VkSwapchainKHR: device lost");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to create VkSwapchainKHR: surface lost");
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
      throw std::runtime_error("failed to create VkSwapchainKHR: native window in use");
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error("failed to create VkSwapchainKHR: initialization failed");
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT :
      throw std::runtime_error("failed to create VkSwapchainKHR: compression exhausted");
    default :
      throw std::runtime_error("failed to create VkSwapchainKHR: unknown error");
  }
}

device::device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice const ptr)
: _handle(ptr, [dispatcher](VkDevice ptr) { vkDestroyDevice(ptr, nullptr); })
{
}
}