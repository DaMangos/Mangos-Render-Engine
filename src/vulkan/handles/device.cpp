#include "internal/create_pipelines.hpp"
#include "internal/create_shared_handle.hpp"
#include "internal/create_unique_handle.hpp"
#include "internal/make_range_element_handle.hpp"
#include <vulkan/handles/device.hpp>

VkDevice vulkan::device::get() const noexcept
{
  return _shared_device.get();
}

VkAllocationCallbacks const * vulkan::device::get_allocation_callbacks() const noexcept
{
  return _shared_allocation_callbacks.get();
}

std::pair<vulkan::buffer, VkResult const> vulkan::device::create_buffer(VkBufferCreateInfo const & info)
{
  return internal::create_unique_handle<VkBuffer, vkCreateBuffer, vkDestroyBuffer>(_shared_instance,
                                                                                   _shared_device,
                                                                                   &info,
                                                                                   _shared_allocation_callbacks);
}

std::pair<vulkan::buffer_view, VkResult const> vulkan::device::create_buffer_view(VkBufferViewCreateInfo const & info)
{
  return internal::create_unique_handle<VkBufferView, vkCreateBufferView, vkDestroyBufferView>(_shared_instance,
                                                                                               _shared_device,
                                                                                               &info,
                                                                                               _shared_allocation_callbacks);
}

std::pair<vulkan::command_pool, VkResult const> vulkan::device::create_command_pool(VkCommandPoolCreateInfo const & info)
{
  return internal::create_shared_handle<VkCommandPool, vkCreateCommandPool, vkDestroyCommandPool>(_shared_instance,
                                                                                                  _shared_device,
                                                                                                  &info,
                                                                                                  _shared_allocation_callbacks,
                                                                                                  _registered_command_pools);
}

std::pair<std::vector<vulkan::command_buffer>, VkResult const> vulkan::device::allocate_command_buffers(VkCommandBufferAllocateInfo const & info)
{
  auto const registered_pool = _registered_command_pools.find(info.commandPool);

  if(not _shared_device or not _shared_device or registered_pool == _registered_command_pools.end() or registered_pool->second.expired())
    return {std::vector<command_buffer>(), VK_ERROR_UNKNOWN};

  auto       handles = std::make_unique_for_overwrite<VkCommandBuffer[]>(info.commandBufferCount);
  auto const result  = vkAllocateCommandBuffers(_shared_device.get(), &info, handles.get());

  if(static_cast<int>(result) < 0)
    return {std::vector<command_buffer>(), result};

  std::shared_ptr<VkCommandBuffer[]> const shared_command_buffers(
    handles.release(),
    [device = _shared_device, pool = registered_pool->second.lock(), count = info.commandBufferCount](auto const handles)
    {
      vkFreeCommandBuffers(device.get(), pool->get(), count, handles);
      delete[] handles;
    });

  std::vector<command_buffer> command_buffers;

  for(std::uint32_t array_index = {}; array_index < info.commandBufferCount; ++array_index)
  {
    command_buffer command_buffer;
    command_buffer._shared_command_buffers = shared_command_buffers;
    command_buffer._array_size             = info.commandBufferCount;
    command_buffer._array_index            = array_index;
    command_buffers.emplace_back(std::move(command_buffer));
  }

  return {std::move(command_buffers), result};
}

std::pair<vulkan::descriptor_set_layout, VkResult const> vulkan::device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const & info)
{
  return internal::create_unique_handle<VkDescriptorSetLayout, vkCreateDescriptorSetLayout, vkDestroyDescriptorSetLayout>(
    _shared_instance,
    _shared_device,
    &info,
    _shared_allocation_callbacks);
}

std::pair<vulkan::descriptor_pool, VkResult const> vulkan::device::create_descriptor_pool(VkDescriptorPoolCreateInfo const & info)
{
  return internal::create_shared_handle<VkDescriptorPool, vkCreateDescriptorPool, vkDestroyDescriptorPool>(_shared_instance,
                                                                                                           _shared_device,
                                                                                                           &info,
                                                                                                           _shared_allocation_callbacks,
                                                                                                           _registered_descriptor_pools);
}

std::pair<std::vector<vulkan::descriptor_set>, VkResult const> vulkan::device::allocate_descriptor_sets(VkDescriptorSetAllocateInfo const & info)
{
  auto const registered_pool = _registered_descriptor_pools.find(info.descriptorPool);

  if(not _shared_device or not _shared_device or registered_pool == _registered_descriptor_pools.end() or registered_pool->second.expired())
    return {std::vector<descriptor_set>(), VK_ERROR_UNKNOWN};

  auto       handles = std::make_unique_for_overwrite<VkDescriptorSet[]>(info.descriptorSetCount);
  auto const result  = vkAllocateDescriptorSets(_shared_device.get(), &info, handles.get());

  if(static_cast<int>(result) < 0)
    return {std::vector<descriptor_set>(), result};

  std::shared_ptr<VkDescriptorSet[]> const shared_descriptor_sets(
    handles.release(),
    [device = _shared_device, pool = registered_pool->second.lock(), count = info.descriptorSetCount](auto const handles)
    {
      vkFreeDescriptorSets(device.get(), pool->get(), count, handles);
      delete[] handles;
    });

  std::vector<descriptor_set> descriptor_sets;

  for(std::uint32_t array_index = {}; array_index < info.descriptorSetCount; ++array_index)
    descriptor_sets.emplace_back(internal::make_range_element_handle<VkDescriptorSet>(shared_descriptor_sets, info.descriptorSetCount, array_index));

  return {std::move(descriptor_sets), result};
}

std::pair<vulkan::device_memory, VkResult const> vulkan::device::allocate_device_memory(VkMemoryAllocateInfo const & info)
{
  return internal::create_unique_handle<VkDeviceMemory, vkAllocateMemory, vkFreeMemory>(_shared_instance,
                                                                                        _shared_device,
                                                                                        &info,
                                                                                        _shared_allocation_callbacks);
}

std::pair<vulkan::event, VkResult const> vulkan::device::create_event(VkEventCreateInfo const & info)
{
  return internal::create_unique_handle<VkEvent, vkCreateEvent, vkDestroyEvent>(_shared_instance,
                                                                                _shared_device,
                                                                                &info,
                                                                                _shared_allocation_callbacks);
}

std::pair<vulkan::fence, VkResult const> vulkan::device::create_fence(VkFenceCreateInfo const & info)
{
  return internal::create_unique_handle<VkFence, vkCreateFence, vkDestroyFence>(_shared_instance,
                                                                                _shared_device,
                                                                                &info,
                                                                                _shared_allocation_callbacks);
}

std::pair<vulkan::framebuffer, VkResult const> vulkan::device::create_framebuffer(VkFramebufferCreateInfo const & info)
{
  return internal::create_unique_handle<VkFramebuffer, vkCreateFramebuffer, vkDestroyFramebuffer>(_shared_instance,
                                                                                                  _shared_device,
                                                                                                  &info,
                                                                                                  _shared_allocation_callbacks);
}

std::pair<vulkan::image, VkResult const> vulkan::device::create_image(VkImageCreateInfo const & info)
{
  return internal::create_unique_handle<VkImage, vkCreateImage, vkDestroyImage>(_shared_instance,
                                                                                _shared_device,
                                                                                &info,
                                                                                _shared_allocation_callbacks);
}

std::pair<vulkan::image_view, VkResult const> vulkan::device::create_image_view(VkImageViewCreateInfo const & info)
{
  return internal::create_unique_handle<VkImageView, vkCreateImageView, vkDestroyImageView>(_shared_instance,
                                                                                            _shared_device,
                                                                                            &info,
                                                                                            _shared_allocation_callbacks);
}

std::pair<std::vector<vulkan::pipeline>, VkResult const> vulkan::device::create_pipelines(VkPipelineCache const                        cache,
                                                                                          std::span<VkComputePipelineCreateInfo> const infos)
{
  return internal::create_pipelines<vkCreateComputePipelines>(_shared_instance, _shared_device, cache, infos, _shared_allocation_callbacks);
}

std::pair<std::vector<vulkan::pipeline>, VkResult const> vulkan::device::create_pipelines(VkPipelineCache const                         cache,
                                                                                          std::span<VkGraphicsPipelineCreateInfo> const infos)
{
  return internal::create_pipelines<vkCreateGraphicsPipelines>(_shared_instance, _shared_device, cache, infos, _shared_allocation_callbacks);
}

std::pair<vulkan::pipeline_cache, VkResult const> vulkan::device::create_pipeline_cache(VkPipelineCacheCreateInfo const & info)
{
  return internal::create_unique_handle<VkPipelineCache, vkCreatePipelineCache, vkDestroyPipelineCache>(_shared_instance,
                                                                                                        _shared_device,
                                                                                                        &info,
                                                                                                        _shared_allocation_callbacks);
}

std::pair<vulkan::pipeline_layout, VkResult const> vulkan::device::create_pipeline_layout(VkPipelineLayoutCreateInfo const & info)
{
  return internal::create_unique_handle<VkPipelineLayout, vkCreatePipelineLayout, vkDestroyPipelineLayout>(_shared_instance,
                                                                                                           _shared_device,
                                                                                                           &info,
                                                                                                           _shared_allocation_callbacks);
}

std::pair<vulkan::query_pool, VkResult const> vulkan::device::create_query_pool(VkQueryPoolCreateInfo const & info)
{
  return internal::create_unique_handle<VkQueryPool, vkCreateQueryPool, vkDestroyQueryPool>(_shared_instance,
                                                                                            _shared_device,
                                                                                            &info,
                                                                                            _shared_allocation_callbacks);
}

std::pair<vulkan::render_pass, VkResult const> vulkan::device::create_render_pass(VkRenderPassCreateInfo const & info)
{
  return internal::create_unique_handle<VkRenderPass, vkCreateRenderPass, vkDestroyRenderPass>(_shared_instance,
                                                                                               _shared_device,
                                                                                               &info,
                                                                                               _shared_allocation_callbacks);
}

std::pair<vulkan::render_pass, VkResult const> vulkan::device::create_render_pass(VkRenderPassCreateInfo2 const & info)
{
  return internal::create_unique_handle<VkRenderPass, vkCreateRenderPass2, vkDestroyRenderPass>(_shared_instance,
                                                                                                _shared_device,
                                                                                                &info,
                                                                                                _shared_allocation_callbacks);
}

std::pair<vulkan::sampler, VkResult const> vulkan::device::create_sampler(VkSamplerCreateInfo const & info)
{
  return internal::create_unique_handle<VkSampler, vkCreateSampler, vkDestroySampler>(_shared_instance,
                                                                                      _shared_device,
                                                                                      &info,
                                                                                      _shared_allocation_callbacks);
}

std::pair<vulkan::semaphore, VkResult const> vulkan::device::create_semaphore(VkSemaphoreCreateInfo const & info)
{
  return internal::create_unique_handle<VkSemaphore, vkCreateSemaphore, vkDestroySemaphore>(_shared_instance,
                                                                                            _shared_device,
                                                                                            &info,
                                                                                            _shared_allocation_callbacks);
}

std::pair<vulkan::shader_module, VkResult const> vulkan::device::create_shader_module(VkShaderModuleCreateInfo const & info)
{
  return internal::create_unique_handle<VkShaderModule, vkCreateShaderModule, vkDestroyShaderModule>(_shared_instance,
                                                                                                     _shared_device,
                                                                                                     &info,
                                                                                                     _shared_allocation_callbacks);
}

std::pair<vulkan::khr::swapchain, VkResult const> vulkan::device::create_swapchain(VkSwapchainCreateInfoKHR const & info)
{
  return internal::create_unique_handle<VkSwapchainKHR, vkCreateSwapchainKHR, vkDestroySwapchainKHR>(_shared_instance,
                                                                                                     _shared_device,
                                                                                                     &info,
                                                                                                     _shared_allocation_callbacks);
}

void vulkan::device::reset() noexcept
{
  _shared_device.reset();
  _shared_device.reset();
  _shared_allocation_callbacks.reset();
  _registered_command_pools.clear();
  _registered_descriptor_pools.clear();
}

vulkan::device::device(nullhandle_t) noexcept(std::is_nothrow_default_constructible_v<registered_command_pools_type> and
                                              std::is_nothrow_default_constructible_v<registered_descriptor_pools_type>)
{
}

vulkan::device & vulkan::device::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

std::strong_ordering vulkan::device::operator<=>(device const & other) const noexcept
{
  return _shared_device <=> other._shared_device;
}

std::strong_ordering vulkan::device::operator<=>(nullhandle_t) const noexcept
{
  return _shared_device <=> nullptr;
}

vulkan::device::operator bool() const noexcept
{
  return static_cast<bool>(_shared_device);
}
