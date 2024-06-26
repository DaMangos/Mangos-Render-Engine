#include "internal.hpp"

#include <vulkan_wrapper/handles/device.hpp>

#include <exception>
#include <ranges>

namespace
{
template <class Handle>
[[nodiscard]]
std::vector<vulkan::range_element_handle<Handle>> transform_handles(std::shared_ptr<Handle[]> const & shared_handles, std::uint32_t const size)
{
  std::vector<vulkan::range_element_handle<Handle>> handles;
  std::ranges::transform(std::views::iota(std::uint32_t{0}, size),
                         std::back_inserter(handles),
                         [&shared_handles, size](auto const index)
                         { return vulkan::internal::make_range_element_handle<Handle>(shared_handles, size, index); });
  return handles;
}
}

VkDevice vulkan::device::get() const noexcept
{
  return _device.get();
}

VkAllocationCallbacks const * vulkan::device::get_allocation_callbacks() const noexcept
{
  return _allocation_callbacks.get();
}

std::pair<vulkan::buffer, VkResult const> vulkan::device::create_buffer(VkBufferCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkBuffer, vkCreateBuffer, vkDestroyBuffer>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::buffer_view, VkResult const> vulkan::device::create_buffer_view(VkBufferViewCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkBufferView, vkCreateBufferView, vkDestroyBufferView>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::command_pool, VkResult const> vulkan::device::create_command_pool(VkCommandPoolCreateInfo const & info) noexcept
{
  return internal::create_shared_handle<VkCommandPool, vkCreateCommandPool, vkDestroyCommandPool>(_instance,
                                                                                                  _device,
                                                                                                  &info,
                                                                                                  _allocation_callbacks,
                                                                                                  _registered_command_pools);
}

std::pair<std::vector<vulkan::command_buffer>, VkResult const> vulkan::device::allocate_command_buffers(
  VkCommandBufferAllocateInfo const & info) noexcept
{
  try
  {
    auto const registered_pool = _registered_command_pools.find(info.commandPool);

    if(not _instance or not _device or registered_pool == _registered_command_pools.end() or registered_pool->second.expired())
      return {std::vector<command_buffer>(), VK_ERROR_UNKNOWN};

    auto       handles = std::make_unique_for_overwrite<VkCommandBuffer[]>(info.commandBufferCount);
    auto const result  = vkAllocateCommandBuffers(_device.get(), &info, handles.get());

    if(static_cast<int>(result) < 0)
      return {std::vector<command_buffer>(), result};

    std::shared_ptr<VkCommandBuffer[]> const command_buffers(
      handles.release(),
      [device = _device, pool = registered_pool->second.lock(), count = info.commandBufferCount](auto const handles)
      {
        vkFreeCommandBuffers(device.get(), pool->get(), count, handles);
        delete[] handles;
      });

    return {transform_handles(command_buffers, info.commandBufferCount), result};
  }

  catch(std::exception const &)
  {
    return {std::vector<command_buffer>(), VK_ERROR_UNKNOWN};
  }
}

std::pair<vulkan::descriptor_set_layout, VkResult const> vulkan::device::create_descriptor_set_layout(
  VkDescriptorSetLayoutCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkDescriptorSetLayout, vkCreateDescriptorSetLayout, vkDestroyDescriptorSetLayout>(_instance,
                                                                                                                          _device,
                                                                                                                          &info,
                                                                                                                          _allocation_callbacks);
}

std::pair<vulkan::descriptor_pool, VkResult const> vulkan::device::create_descriptor_pool(VkDescriptorPoolCreateInfo const & info) noexcept
{
  return internal::create_shared_handle<VkDescriptorPool, vkCreateDescriptorPool, vkDestroyDescriptorPool>(_instance,
                                                                                                           _device,
                                                                                                           &info,
                                                                                                           _allocation_callbacks,
                                                                                                           _registered_descriptor_pools);
}

std::pair<std::vector<vulkan::descriptor_set>, VkResult const> vulkan::device::allocate_descriptor_sets(
  VkDescriptorSetAllocateInfo const & info) noexcept
{
  try
  {
    auto const registered_pool = _registered_descriptor_pools.find(info.descriptorPool);

    if(not _instance or not _device or registered_pool == _registered_descriptor_pools.end() or registered_pool->second.expired())
      return {std::vector<descriptor_set>(), VK_ERROR_UNKNOWN};

    auto       handles = std::make_unique_for_overwrite<VkDescriptorSet[]>(info.descriptorSetCount);
    auto const result  = vkAllocateDescriptorSets(_device.get(), &info, handles.get());

    if(static_cast<int>(result) < 0)
      return {std::vector<descriptor_set>(), result};

    std::shared_ptr<VkDescriptorSet[]> const descriptor_sets(
      handles.release(),
      [device = _device, pool = registered_pool->second.lock(), count = info.descriptorSetCount](auto const handles)
      {
        vkFreeDescriptorSets(device.get(), pool->get(), count, handles);
        delete[] handles;
      });

    return {transform_handles(descriptor_sets, info.descriptorSetCount), result};
  }
  catch(std::exception const &)
  {
    return {std::vector<descriptor_set>(), VK_ERROR_UNKNOWN};
  }
}

std::pair<vulkan::device_memory, VkResult const> vulkan::device::allocate_device_memory(VkMemoryAllocateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkDeviceMemory, vkAllocateMemory, vkFreeMemory>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::event, VkResult const> vulkan::device::create_event(VkEventCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkEvent, vkCreateEvent, vkDestroyEvent>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::fence, VkResult const> vulkan::device::create_fence(VkFenceCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkFence, vkCreateFence, vkDestroyFence>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::framebuffer, VkResult const> vulkan::device::create_framebuffer(VkFramebufferCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkFramebuffer, vkCreateFramebuffer, vkDestroyFramebuffer>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::image, VkResult const> vulkan::device::create_image(VkImageCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkImage, vkCreateImage, vkDestroyImage>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::image_view, VkResult const> vulkan::device::create_image_view(VkImageViewCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkImageView, vkCreateImageView, vkDestroyImageView>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<std::vector<vulkan::pipeline>, VkResult const> vulkan::device::create_pipelines(VkPipelineCache const                        cache,
                                                                                          std::span<VkComputePipelineCreateInfo> const infos) noexcept
{
  return internal::create_pipelines<vkCreateComputePipelines>(_instance, _device, cache, infos, _allocation_callbacks);
}

std::pair<std::vector<vulkan::pipeline>, VkResult const> vulkan::device::create_pipelines(
  VkPipelineCache const                         cache,
  std::span<VkGraphicsPipelineCreateInfo> const infos) noexcept
{
  return internal::create_pipelines<vkCreateGraphicsPipelines>(_instance, _device, cache, infos, _allocation_callbacks);
}

std::pair<vulkan::pipeline_cache, VkResult const> vulkan::device::create_pipeline_cache(VkPipelineCacheCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkPipelineCache, vkCreatePipelineCache, vkDestroyPipelineCache>(_instance,
                                                                                                        _device,
                                                                                                        &info,
                                                                                                        _allocation_callbacks);
}

std::pair<vulkan::pipeline_layout, VkResult const> vulkan::device::create_pipeline_layout(VkPipelineLayoutCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkPipelineLayout, vkCreatePipelineLayout, vkDestroyPipelineLayout>(_instance,
                                                                                                           _device,
                                                                                                           &info,
                                                                                                           _allocation_callbacks);
}

std::pair<vulkan::query_pool, VkResult const> vulkan::device::create_query_pool(VkQueryPoolCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkQueryPool, vkCreateQueryPool, vkDestroyQueryPool>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::render_pass, VkResult const> vulkan::device::create_render_pass(VkRenderPassCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkRenderPass, vkCreateRenderPass, vkDestroyRenderPass>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::render_pass, VkResult const> vulkan::device::create_render_pass(VkRenderPassCreateInfo2 const & info) noexcept
{
  return internal::create_unique_handle<VkRenderPass, vkCreateRenderPass2, vkDestroyRenderPass>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::sampler, VkResult const> vulkan::device::create_sampler(VkSamplerCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkSampler, vkCreateSampler, vkDestroySampler>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::semaphore, VkResult const> vulkan::device::create_semaphore(VkSemaphoreCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkSemaphore, vkCreateSemaphore, vkDestroySemaphore>(_instance, _device, &info, _allocation_callbacks);
}

std::pair<vulkan::shader_module, VkResult const> vulkan::device::create_shader_module(VkShaderModuleCreateInfo const & info) noexcept
{
  return internal::create_unique_handle<VkShaderModule, vkCreateShaderModule, vkDestroyShaderModule>(_instance,
                                                                                                     _device,
                                                                                                     &info,
                                                                                                     _allocation_callbacks);
}

std::pair<vulkan::khr::swapchain, VkResult const> vulkan::device::create_swapchain(VkSwapchainCreateInfoKHR const & info) noexcept
{
  return internal::create_unique_handle<VkSwapchainKHR, vkCreateSwapchainKHR, vkDestroySwapchainKHR>(_instance,
                                                                                                     _device,
                                                                                                     &info,
                                                                                                     _allocation_callbacks);
}

void vulkan::device::reset() noexcept
{
  _instance.reset();
  _device.reset();
  _allocation_callbacks.reset();
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
  return _device <=> other._device;
}

std::strong_ordering vulkan::device::operator<=>(nullhandle_t) const noexcept
{
  return _device <=> nullptr;
}

vulkan::device::operator bool() const noexcept
{
  return static_cast<bool>(_device);
}
