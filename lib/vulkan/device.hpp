#pragma once

#include "non_dispatchable_handles.hpp"
#include "ranges.hpp"

#include <algorithm>
#include <unordered_map>

namespace vulkan
{
struct non_dispatchable;
struct physical_device;
struct queue;

struct device final
{
    using pointer      = typename std::pointer_traits<VkDevice>::pointer;
    using element_type = typename std::pointer_traits<VkDevice>::element_type;

    [[nodiscard]]
    buffer create_buffer(VkBufferCreateInfo const &info) const;

    [[nodiscard]]
    buffer_view create_buffer_view(VkBufferViewCreateInfo const &info) const;

    [[nodiscard]]
    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo const &info) const;

    [[nodiscard]]
    command_pool create_command_pool(VkCommandPoolCreateInfo const &info) const;

    [[nodiscard]]
    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo const &info) const;

    [[nodiscard]]
    descriptor_set_layout create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const &info) const;

    [[nodiscard]]
    descriptor_sets allocate_descriptor_sets(VkDescriptorSetAllocateInfo const &info) const;

    [[nodiscard]]
    device_memory allocate_memory(VkMemoryAllocateInfo const &info) const;

    [[nodiscard]]
    event create_event(VkEventCreateInfo const &info) const;

    [[nodiscard]]
    fence create_fence(VkFenceCreateInfo const &info) const;

    [[nodiscard]]
    framebuffer create_framebuffer(VkFramebufferCreateInfo const &info) const;

    [[nodiscard]]
    image create_image(VkImageCreateInfo const &info) const;

    [[nodiscard]]
    image_view create_image_view(VkImageViewCreateInfo const &info) const;

    [[nodiscard]]
    pipeline_cache create_pipeline_cache(VkPipelineCacheCreateInfo const &info) const;

    [[nodiscard]]
    pipeline_layout create_pipeline_layout(VkPipelineLayoutCreateInfo const &info) const;

    [[nodiscard]]
    query_pool create_query_pool(VkQueryPoolCreateInfo const &info) const;

    [[nodiscard]]
    queue get_device_queue(VkDeviceQueueInfo2 const &queue_info) const noexcept;

    [[nodiscard]]
    render_pass create_render_pass(VkRenderPassCreateInfo2 const &info) const;

    [[nodiscard]]
    sampler create_sampler(VkSamplerCreateInfo const &info) const;

    [[nodiscard]]
    semaphore create_semaphore(VkSemaphoreCreateInfo const &info) const;

    [[nodiscard]]
    shader_module create_shader_module(VkShaderModuleCreateInfo const &info) const;

    [[nodiscard]]
    khr::swapchain create_swapchain(VkSwapchainCreateInfoKHR const &info) const;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult const> create_compute_pipelines(
      VkPipelineCache const                    &pipeline_cache,
      std::ranges::contiguous_range auto const &infos) const
    requires std::same_as<std::ranges::range_value_t<decltype(infos)>, VkComputePipelineCreateInfo>
    {
      return create_pipeline<vkCreateComputePipelines>(pipeline_cache, infos);
    }

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult const> create_graphics_pipelines(
      VkPipelineCache const                    &pipeline_cache,
      std::ranges::contiguous_range auto const &infos) const
    requires std::same_as<std::ranges::range_value_t<decltype(infos)>, VkGraphicsPipelineCreateInfo>
    {
      return create_pipeline<vkCreateGraphicsPipelines>(pipeline_cache, infos);
    }

    [[nodiscard]]
    constexpr VkDevice get() const noexcept
    {
      return _smart_ptr.get();
    }

    constexpr operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    constexpr bool operator==(device const &other) noexcept
    {
      return _smart_ptr == other._smart_ptr;
    }

    constexpr bool operator!=(device const &other) noexcept
    {
      return _smart_ptr != other._smart_ptr;
    }

    device(device &&)                 = default;
    device(device const &)            = delete;
    device &operator=(device &&)      = default;
    device &operator=(device const &) = delete;
    ~device()                         = default;

  private:
    template <auto create_fn>
    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult const> create_pipelines(
      VkPipelineCache const                    &pipeline_cache,
      std::ranges::contiguous_range auto const &infos,
      std::source_location                      location = std::source_location::current()) const
    {
      if(std::ranges::size(infos) > std::numeric_limits<std::uint32_t>::max())
        throw std::runtime_error(std::string(location.function_name()) +
                                 " :\033[1;31m error:\033[0m too many configurations given (" +
                                 std::to_string(std::ranges::size(infos)) + ")");
      auto ptrs         = std::vector<VkPipeline>(std::ranges::size(infos));
      auto return_value = std::make_pair<std::vector<pipeline>, VkResult const>(
        {},
        create_fn(get(), pipeline_cache, ranges::size(infos), ranges::data(infos), nullptr, ptrs.data()));
      if(std::to_underlying(return_value.second) < 0)
        throw std::runtime_error(std::string(location.function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult (" +
                                 std::to_string(return_value.second) + ")");
      std::ranges::transform(ptrs,
                             std::back_inserter(return_value.first),
                             [this](auto const &ptr) { return pipeline(_smart_ptr, ptr); });
      return return_value;
    }

    friend struct physical_device;

    device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice const ptr);

    std::unordered_map<VkCommandPool,
                       std::weak_ptr<std::pointer_traits<VkCommandPool>::element_type>> mutable _registered_command_pools;
    std::unordered_map<VkDescriptorPool,
                       std::weak_ptr<std::pointer_traits<VkDescriptorPool>::element_type>> mutable _registered_descriptor_pools;
    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _smart_ptr;
};
}

template <>
struct std::hash<vulkan::device>
{
    std::size_t operator()(vulkan::device const &device) const noexcept
    {
      return std::hash<VkDevice>()(device.get());
    }
};
