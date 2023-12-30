#pragma once

#include "queue.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace vulkan
{
template <class>
struct dispatchable_handle;

template <>
struct dispatchable_handle<VkDevice> final
{
    using value_type = VkDevice;

    [[nodiscard]]
    constexpr auto get() const
    {
      return _smart_ptr ? _smart_ptr.get() : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_buffer(VkBufferCreateInfo const &info) const
    {
      return _smart_ptr ? buffer(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_buffer_view(VkBufferViewCreateInfo const &info) const
    {
      return _smart_ptr ? buffer_view(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto allocate_command_buffers(VkCommandBufferAllocateInfo const &info) const
    {
      if(not _smart_ptr)
        throw bad_handle_access();
      auto const pool = _registered_command_pools.find(info.commandPool);
      if(pool == _registered_command_pools.end() or pool->second.expired())
        throw not_found("command pool");
      return command_buffers(_smart_ptr, pool->second.lock(), info.commandBufferCount, &info);
    }

    [[nodiscard]]
    auto create_command_pool(VkCommandPoolCreateInfo const &info) const
    {
      if(not _smart_ptr)
        throw bad_handle_access();
      auto pool = command_pool(_smart_ptr, &info);
      _registered_command_pools.emplace(pool.get(), pool._smart_ptr);
      return pool;
    }

    [[nodiscard]]
    auto create_descriptor_pool(VkDescriptorPoolCreateInfo const &info) const
    {
      if(not _smart_ptr)
        throw bad_handle_access();
      auto pool = descriptor_pool(_smart_ptr, &info);
      _registered_descriptor_pools.emplace(pool.get(), pool._smart_ptr);
      return pool;
    }

    [[nodiscard]]
    auto create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const &info) const
    {
      return descriptor_set_layout(_smart_ptr, &info);
    }

    [[nodiscard]]
    auto allocate_descriptor_sets(VkDescriptorSetAllocateInfo const &info) const
    {
      if(not _smart_ptr)
        throw bad_handle_access();
      auto const pool = _registered_descriptor_pools.find(info.descriptorPool);
      if(pool == _registered_descriptor_pools.end() or pool->second.expired())
        throw not_found("descriptor sets");
      return descriptor_sets(_smart_ptr, pool->second.lock(), info.descriptorSetCount, &info);
    }

    [[nodiscard]]
    auto allocate_memory(VkMemoryAllocateInfo const &info) const
    {
      return _smart_ptr ? device_memory(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_event(VkEventCreateInfo const &info) const
    {
      return _smart_ptr ? event(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_fence(VkFenceCreateInfo const &info) const
    {
      return _smart_ptr ? fence(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_framebuffer(VkFramebufferCreateInfo const &info) const
    {
      return _smart_ptr ? framebuffer(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_image(VkImageCreateInfo const &info) const
    {
      return _smart_ptr ? image(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_image_view(VkImageViewCreateInfo const &info) const
    {
      return _smart_ptr ? image_view(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_pipeline_cache(VkPipelineCacheCreateInfo const &info) const
    {
      return _smart_ptr ? pipeline_cache(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_pipeline_layout(VkPipelineLayoutCreateInfo const &info) const
    {
      return _smart_ptr ? pipeline_layout(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto get_device_queue(VkDeviceQueueInfo2 const &info) const
    {
      return _smart_ptr ? queue(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_query_pool(VkQueryPoolCreateInfo const &info) const
    {
      return _smart_ptr ? query_pool(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_render_pass(VkRenderPassCreateInfo2 const &info) const
    {
      return _smart_ptr ? render_pass(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_sampler(VkSamplerCreateInfo const &info) const
    {
      return _smart_ptr ? sampler(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_semaphore(VkSemaphoreCreateInfo const &info) const
    {
      return _smart_ptr ? semaphore(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_shader_module(VkShaderModuleCreateInfo const &info) const
    {
      return _smart_ptr ? shader_module(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_pipelines(std::ranges::contiguous_range auto const &infos, VkPipelineCache cache) const
    requires(std::same_as<std::ranges::range_value_t<decltype(infos)>, VkComputePipelineCreateInfo> or
             std::same_as<std::ranges::range_value_t<decltype(infos)>, VkGraphicsPipelineCreateInfo>)
    {
      auto ptrs         = std::vector<VkPipeline>(ranges::size(infos));
      auto return_value = std::pair<std::vector<pipeline>, VkResult>();
      if constexpr(std::same_as<std::ranges::range_value_t<decltype(infos)>, VkComputePipelineCreateInfo>)
        return_value.second = vkCreateComputePipelines(get(), cache, ranges::size(infos), ranges::data(infos), nullptr, ptrs.data());
      if constexpr(std::same_as<std::ranges::range_value_t<decltype(infos)>, VkGraphicsPipelineCreateInfo>)
        return_value.second = vkCreateGraphicsPipelines(get(), cache, ranges::size(infos), ranges::data(infos), nullptr, ptrs.data());
      if(std::to_underlying(return_value.second) < 0)
        throw bad_result(return_value.second);
      return_value.first.reserve(ranges::size(infos));
      std::ranges::transform(ptrs, std::back_inserter(return_value.first), [this](auto const ptr) { return graphical_pipeline(_smart_ptr, ptr); });
      return return_value;
    }

    [[nodiscard]]
    auto create_swapchain(VkSwapchainCreateInfoKHR const &info) const
    {
      return _smart_ptr ? khr::swapchain(_smart_ptr, &info) : throw bad_handle_access();
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    auto operator<=>(dispatchable_handle const &other) const noexcept
    {
      return _smart_ptr.get() <=> other._smart_ptr.get();
    }

    dispatchable_handle(dispatchable_handle &&)                 = default;
    dispatchable_handle(dispatchable_handle const &)            = delete;
    dispatchable_handle &operator=(dispatchable_handle &&)      = default;
    dispatchable_handle &operator=(dispatchable_handle const &) = delete;
    ~dispatchable_handle()                                      = default;

  private:
    friend struct dispatchable_handle<VkPhysicalDevice>;

    dispatchable_handle(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher,
                        VkPhysicalDevice const                                                physical_device,
                        auto                                                                &&info)
    : _dispatcher(dispatcher),
      _smart_ptr(
        [&physical_device, &info]()
        {
          value_type ptr;
          auto const result = vkCreateDevice(physical_device, std::forward<decltype(info)>(info), nullptr, &ptr);
          return std::to_underlying(result) >= 0 ? ptr : throw bad_result(result);
        }(),
        [](auto &&ptr) { vkDestroyDevice(std::forward<decltype(ptr)>(ptr), nullptr); })
    {
    }

    std::unordered_map<VkCommandPool, std::weak_ptr<std::pointer_traits<VkCommandPool>::element_type>> mutable _registered_command_pools;
    std::unordered_map<VkDescriptorPool, std::weak_ptr<std::pointer_traits<VkDescriptorPool>::element_type>> mutable _registered_descriptor_pools;
    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _dispatcher;
    std::shared_ptr<std::pointer_traits<value_type>::element_type> _smart_ptr;
};

using device = dispatchable_handle<VkDevice>;
}