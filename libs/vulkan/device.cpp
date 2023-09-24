#include "device.hpp"

#include <algorithm>
#include <iterator>

namespace vulkan
{
VkDevice device::get() const noexcept
{
  return device_.get<0>();
}

buffer device::create_buffer(VkBufferCreateInfo create_info) const
{
  VkBuffer ptr;
  switch(vkCreateBuffer(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return buffer(get(), std::move(ptr));
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

buffer_view device::create_buffer_view(VkBufferViewCreateInfo create_info) const
{
  VkBufferView ptr;
  switch(vkCreateBufferView(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return buffer_view(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkBufferView: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkBufferView: out of device memory");
    default :
      throw std::runtime_error("failed to create VkBufferView: unknown error");
  }
}

command_buffers device::allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const
{
  std::vector<VkCommandBuffer> ptrs(allocate_info.commandBufferCount);
  switch(vkAllocateCommandBuffers(get(), &allocate_info, ptrs.data()))
  {
    case VK_SUCCESS :
      return command_buffers(get(), allocate_info.commandPool, std::move(ptrs));
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

command_pool device::create_command_pool(VkCommandPoolCreateInfo create_info)
{
  VkCommandPool ptr;
  switch(vkCreateCommandPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return command_pool(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkCommandPool: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkCommandPool: out of device memory");
    default :
      throw std::runtime_error("failed to create VkCommandPool: unknown error");
  }
}

descriptor_pool device::create_descriptor_pool(VkDescriptorPoolCreateInfo create_info)
{
  VkDescriptorPool ptr;
  switch(vkCreateDescriptorPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return descriptor_pool(get(), std::move(ptr));
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

descriptor_set_layout device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo create_info) const
{
  VkDescriptorSetLayout ptr;
  switch(vkCreateDescriptorSetLayout(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return descriptor_set_layout(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: out of device memory");
    default :
      throw std::runtime_error("failed to create VkDescriptorSetLayout: unknown error");
  }
}

descriptor_sets device::allocate_descriptor_sets(VkDescriptorSetAllocateInfo allocate_info) const
{
  std::vector<VkDescriptorSet> ptrs(allocate_info.descriptorSetCount);
  switch(vkAllocateDescriptorSets(get(), &allocate_info, ptrs.data()))
  {
    case VK_SUCCESS :
      return descriptor_sets(get(), allocate_info.descriptorPool, std::move(ptrs));
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

device_memory device::allocate_memory(VkMemoryAllocateInfo allocate_info) const
{
  VkDeviceMemory ptr;
  switch(vkAllocateMemory(get(), &allocate_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return device_memory(get(), std::move(ptr));
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

event device::create_event(VkEventCreateInfo create_info) const
{
  VkEvent ptr;
  switch(vkCreateEvent(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return event(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkEvent: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkEvent: out of device memory");
    default :
      throw std::runtime_error("failed to create VkEvent: unknown error");
  }
}

fence device::create_fence(VkFenceCreateInfo create_info) const
{
  VkFence ptr;
  switch(vkCreateFence(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return fence(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkFence: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkFence: out of device memory");
    default :
      throw std::runtime_error("failed to create VkFence: unknown error");
  }
}

framebuffer device::create_framebuffer(VkFramebufferCreateInfo create_info) const
{
  VkFramebuffer ptr;
  switch(vkCreateFramebuffer(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return framebuffer(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkFramebuffer: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkFramebuffer: out of device memory");
    default :
      throw std::runtime_error("failed to create VkFramebuffer: unknown error");
  }
}

image device::create_image(VkImageCreateInfo create_info) const
{
  VkImage ptr;
  switch(vkCreateImage(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return image(get(), std::move(ptr));
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

image_view device::create_image_view(VkImageViewCreateInfo create_info) const
{
  VkImageView ptr;
  switch(vkCreateImageView(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return image_view(get(), std::move(ptr));
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

std::list<pipeline> device::create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                    std::vector<VkComputePipelineCreateInfo> create_infos) const
{
  if(create_infos.size() > std::numeric_limits<std::uint32_t>::max())
    throw std::runtime_error("failed to create VkPipeline: too many VkComputePipelineCreateInfo");
  std::vector<VkPipeline> ptrs(create_infos.size());
  switch(vkCreateComputePipelines(get(),
                                  pipeline_cache,
                                  static_cast<std::uint32_t>(create_infos.size()),
                                  create_infos.data(),
                                  nullptr,
                                  ptrs.data()))
  {
    case VK_SUCCESS | VK_PIPELINE_COMPILE_REQUIRED_EXT :
    {
      std::list<pipeline> pipelines;
      std::transform(std::make_move_iterator(ptrs.begin()),
                     std::make_move_iterator(ptrs.end()),
                     std::back_inserter(pipelines),
                     [this](VkPipeline ptr) { return pipeline(get(), std::move(ptr)); });
      return pipelines;
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipeline: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipeline: out of device memory");
    case VK_ERROR_INVALID_SHADER_NV :
      throw std::runtime_error("failed to create VkPipeline: invalid shader");
    default :
      throw std::runtime_error("failed to create VkPipeline: unknown error");
  }
}

std::list<pipeline> device::create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                     std::vector<VkGraphicsPipelineCreateInfo> create_infos) const
{
  if(create_infos.size() > std::numeric_limits<std::uint32_t>::max())
    throw std::runtime_error("failed to create VkPipeline: too many VkGraphicsPipelineCreateInfo");
  std::vector<VkPipeline> ptrs(create_infos.size());
  switch(vkCreateGraphicsPipelines(get(),
                                   pipeline_cache,
                                   static_cast<std::uint32_t>(create_infos.size()),
                                   create_infos.data(),
                                   nullptr,
                                   ptrs.data()))
  {
    case VK_SUCCESS | VK_PIPELINE_COMPILE_REQUIRED_EXT :
    {
      std::list<pipeline> pipelines;
      std::transform(std::make_move_iterator(ptrs.begin()),
                     std::make_move_iterator(ptrs.end()),
                     std::back_inserter(pipelines),
                     [this](VkPipeline ptr) { return pipeline(get(), std::move(ptr)); });
      return pipelines;
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipeline: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipeline: out of device memory");
    case VK_ERROR_INVALID_SHADER_NV :
      throw std::runtime_error("failed to create VkPipeline: invalid shader");
    default :
      throw std::runtime_error("failed to create VkPipeline: unknown error");
  }
}

pipeline_cache device::create_pipeline_cache(VkPipelineCacheCreateInfo create_info) const
{
  VkPipelineCache ptr;
  switch(vkCreatePipelineCache(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return pipeline_cache(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipelineCache: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipelineCache: out of device memory");
    default :
      throw std::runtime_error("failed to create VkPipelineCache: unknown error");
  }
}

pipeline_layout device::create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const
{
  VkPipelineLayout ptr;
  switch(vkCreatePipelineLayout(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return pipeline_layout(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkPipelineLayout: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkPipelineLayout: out of device memory");
    default :
      throw std::runtime_error("failed to create VkPipelineLayout: unknown error");
  }
}

query_pool device::create_query_pool(VkQueryPoolCreateInfo create_info) const
{
  VkQueryPool ptr;
  switch(vkCreateQueryPool(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return query_pool(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkQueryPool: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkQueryPool: out of device memory");
    default :
      throw std::runtime_error("failed to create VkQueryPool: unknown error");
  }
}

queue device::get_device_queue(VkDeviceQueueInfo2 create_info) const
{
  VkQueue ptr;
  vkGetDeviceQueue2(get(), &create_info, &ptr);
  return queue(std::move(ptr));
}

render_pass device::create_render_pass(VkRenderPassCreateInfo2 create_info) const
{
  VkRenderPass ptr;
  switch(vkCreateRenderPass2(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return render_pass(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkRenderPass: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkRenderPass: out of device memory");
    default :
      throw std::runtime_error("failed to create VkRenderPass: unknown error");
  }
}

sampler device::create_sampler(VkSamplerCreateInfo create_info) const
{
  VkSampler ptr;
  switch(vkCreateSampler(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return sampler(get(), std::move(ptr));
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

semaphore device::create_semaphore(VkSemaphoreCreateInfo create_info) const
{
  VkSemaphore ptr;
  switch(vkCreateSemaphore(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return semaphore(get(), std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkSemaphore: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkSemaphore: out of device memory");
    default :
      throw std::runtime_error("failed to create VkSemaphore: unknown error");
  }
}

shader_module device::create_shader_module(VkShaderModuleCreateInfo create_info) const
{
  VkShaderModule ptr;
  switch(vkCreateShaderModule(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return shader_module(get(), std::move(ptr));
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

khr::swapchain device::create_swapchain(VkSwapchainCreateInfoKHR create_info) const
{
  VkSwapchainKHR ptr;
  switch(vkCreateSwapchainKHR(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return khr::swapchain(get(), std::move(ptr));
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

device::device(VkDevice &&device) noexcept
: device_(std::move(device))
{
}
}