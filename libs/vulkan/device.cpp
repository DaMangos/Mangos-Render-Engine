#include "device.hpp"

#include "command_buffers.hpp"
#include "descriptor_sets.hpp"
#include "queue.hpp"

namespace vulkan
{
VkDevice device::get() const noexcept
{
  return _device.get();
}

buffer device::create_buffer(VkBufferCreateInfo create_info) const
{
  VkBuffer      ptr;
  VkResult      result = vkCreateBuffer(get(), &create_info, nullptr, &ptr);
  buffer_handle handle(vkDestroyBuffer, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return buffer(_device, std::move(handle));
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
  VkBufferView       ptr;
  VkResult           result = vkCreateBufferView(get(), &create_info, nullptr, &ptr);
  buffer_view_handle handle(vkDestroyBufferView, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return buffer_view(_device, std::move(handle));
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
  auto registered_command_pool = _registered_command_pools.find(allocate_info.commandPool);
  if(registered_command_pool == _registered_command_pools.end() or registered_command_pool->second.expired())
    throw std::runtime_error("failed to allocate VkCommandBuffers: command pool not found");
  VkCommandBuffer       *ptr    = new VkCommandBuffer[allocate_info.commandBufferCount];
  VkResult               result = vkAllocateCommandBuffers(get(), &allocate_info, ptr);
  command_buffers_handle handle(
    [](VkDevice device, VkCommandPool pool, uint32_t count, VkCommandBuffer const *ptr)
    {
      vkFreeCommandBuffers(device, pool, count, ptr);
      delete[] ptr;
    },
    get(),
    allocate_info.commandPool,
    allocate_info.commandBufferCount,
    ptr);
  switch(result)
  {
    case VK_SUCCESS :
      return command_buffers(registered_command_pool->second.lock(), std::move(handle));
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
  VkCommandPool       ptr;
  VkResult            result = vkCreateCommandPool(get(), &create_info, nullptr, &ptr);
  command_pool_handle handle(vkDestroyCommandPool, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      _registered_command_pools.emplace(ptr, handle);
      return command_pool(_device, std::move(handle));
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
  VkDescriptorPool       ptr;
  VkResult               result = vkCreateDescriptorPool(get(), &create_info, nullptr, &ptr);
  descriptor_pool_handle handle(vkDestroyDescriptorPool, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      _registered_descriptor_pools.emplace(ptr, handle);
      return descriptor_pool(_device, std::move(handle));
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
  VkDescriptorSetLayout        ptr;
  VkResult                     result = vkCreateDescriptorSetLayout(get(), &create_info, nullptr, &ptr);
  descriptor_set_layout_handle handle(vkDestroyDescriptorSetLayout, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return descriptor_set_layout(_device, std::move(handle));
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
  auto registered_descriptor_pool = _registered_descriptor_pools.find(allocate_info.descriptorPool);
  if(registered_descriptor_pool == _registered_descriptor_pools.end() or registered_descriptor_pool->second.expired())
    throw std::runtime_error("failed to allocate VkDescriptorSets: descriptor pool not found");
  VkDescriptorSet       *ptr    = new VkDescriptorSet[allocate_info.descriptorSetCount];
  VkResult               result = vkAllocateDescriptorSets(get(), &allocate_info, ptr);
  descriptor_sets_handle handle(
    [](VkDevice device, VkDescriptorPool pool, uint32_t count, VkDescriptorSet const *ptr)
    {
      vkFreeDescriptorSets(device, pool, count, ptr);
      delete[] ptr;
    },
    get(),
    allocate_info.descriptorPool,
    allocate_info.descriptorSetCount,
    ptr);
  switch(result)
  {
    case VK_SUCCESS :
      return descriptor_sets(registered_descriptor_pool->second.lock(), std::move(handle));
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
  VkDeviceMemory       ptr;
  VkResult             result = vkAllocateMemory(get(), &allocate_info, nullptr, &ptr);
  device_memory_handle handle(vkFreeMemory, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return device_memory(_device, std::move(handle));
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
  VkEvent      ptr;
  VkResult     result = vkCreateEvent(get(), &create_info, nullptr, &ptr);
  event_handle handle(vkDestroyEvent, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return event(_device, std::move(handle));
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
  VkFence      ptr;
  VkResult     result = vkCreateFence(get(), &create_info, nullptr, &ptr);
  fence_handle handle(vkDestroyFence, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return fence(_device, std::move(handle));
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
  VkFramebuffer      ptr;
  VkResult           result = vkCreateFramebuffer(get(), &create_info, nullptr, &ptr);
  framebuffer_handle handle(vkDestroyFramebuffer, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return framebuffer(_device, std::move(handle));
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
  VkImage      ptr;
  VkResult     result = vkCreateImage(get(), &create_info, nullptr, &ptr);
  image_handle handle(vkDestroyImage, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return image(_device, std::move(handle));
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
  VkImageView       ptr;
  VkResult          result = vkCreateImageView(get(), &create_info, nullptr, &ptr);
  image_view_handle handle(vkDestroyImageView, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return image_view(_device, std::move(handle));
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

std::vector<pipeline> device::create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                      std::vector<VkComputePipelineCreateInfo> create_infos) const
{
  if(create_infos.size() > std::numeric_limits<std::uint32_t>::max())
    throw std::runtime_error("failed to create VkPipeline: too many VkComputePipelineCreateInfo");
  std::vector<VkPipeline> ptrs(create_infos.size());
  std::vector<pipeline>   handles;
  handles.reserve(create_infos.size());
  VkResult result = vkCreateComputePipelines(get(),
                                             pipeline_cache,
                                             static_cast<std::uint32_t>(create_infos.size()),
                                             create_infos.data(),
                                             nullptr,
                                             ptrs.data());
  for(VkPipeline ptr : ptrs)
    handles.emplace_back(pipeline(_device, pipeline_handle(vkDestroyPipeline, get(), ptr, nullptr)));
  switch(result)
  {
    case VK_SUCCESS | VK_PIPELINE_COMPILE_REQUIRED_EXT :
      return handles;
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

std::vector<pipeline> device::create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                       std::vector<VkGraphicsPipelineCreateInfo> create_infos) const
{
  if(create_infos.size() > std::numeric_limits<std::uint32_t>::max())
    throw std::runtime_error("failed to create VkPipeline: too many VkGraphicsPipelineCreateInfo");
  std::vector<VkPipeline> ptrs(create_infos.size());
  std::vector<pipeline>   handles;
  handles.reserve(create_infos.size());
  VkResult result = vkCreateGraphicsPipelines(get(),
                                              pipeline_cache,
                                              static_cast<std::uint32_t>(create_infos.size()),
                                              create_infos.data(),
                                              nullptr,
                                              ptrs.data());
  for(VkPipeline ptr : ptrs)
    handles.emplace_back(pipeline(_device, pipeline_handle(vkDestroyPipeline, get(), ptr, nullptr)));
  switch(result)
  {
    case VK_SUCCESS | VK_PIPELINE_COMPILE_REQUIRED_EXT :
      return handles;
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
  VkPipelineCache       ptr;
  VkResult              result = vkCreatePipelineCache(get(), &create_info, nullptr, &ptr);
  pipeline_cache_handle handle(vkDestroyPipelineCache, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return pipeline_cache(_device, std::move(handle));
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
  VkPipelineLayout       ptr;
  VkResult               result = vkCreatePipelineLayout(get(), &create_info, nullptr, &ptr);
  pipeline_layout_handle handle(vkDestroyPipelineLayout, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return pipeline_layout(_device, std::move(handle));
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
  VkQueryPool       ptr;
  VkResult          result = vkCreateQueryPool(get(), &create_info, nullptr, &ptr);
  query_pool_handle handle(vkDestroyQueryPool, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return query_pool(_device, std::move(handle));
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
  return queue(ptr);
}

render_pass device::create_render_pass(VkRenderPassCreateInfo2 create_info) const
{
  VkRenderPass       ptr;
  VkResult           result = vkCreateRenderPass2(get(), &create_info, nullptr, &ptr);
  render_pass_handle handle(vkDestroyRenderPass, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return render_pass(_device, std::move(handle));
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
  VkSampler      ptr;
  VkResult       result = vkCreateSampler(get(), &create_info, nullptr, &ptr);
  sampler_handle handle(vkDestroySampler, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return sampler(_device, std::move(handle));
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
  VkSemaphore      ptr;
  VkResult         result = vkCreateSemaphore(get(), &create_info, nullptr, &ptr);
  semaphore_handle handle(vkDestroySemaphore, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return semaphore(_device, std::move(handle));
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
  VkShaderModule       ptr;
  VkResult             result = vkCreateShaderModule(get(), &create_info, nullptr, &ptr);
  shader_module_handle handle(vkDestroyShaderModule, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return shader_module(_device, std::move(handle));
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
  VkSwapchainKHR        ptr;
  VkResult              result = vkCreateSwapchainKHR(get(), &create_info, nullptr, &ptr);
  khr::swapchain_handle handle(vkDestroySwapchainKHR, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return khr::swapchain(_device, std::move(handle));
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

device::device(device_handle device) noexcept
: _device(device)
{
}
}