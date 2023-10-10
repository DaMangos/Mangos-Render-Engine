#pragma once

#include "non_dispatchable.hpp"

#include <unordered_map>
#include <vector>

namespace vulkan
{
struct command_buffers;
struct descriptor_sets;
struct non_dispatchable;
struct physical_device;
struct queue;

struct device final
{
    [[nodiscard]]
    constexpr VkDevice get() const noexcept
    {
      return _handle.get();
    }

    [[nodiscard]]
    VkInstance get_instance() const noexcept;

    [[nodiscard]]
    buffer create_buffer(VkBufferCreateInfo const &create_info) const;

    [[nodiscard]]
    buffer_view create_buffer_view(VkBufferViewCreateInfo const &create_info) const;

    [[nodiscard]]
    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo const &allocate_info) const;

    [[nodiscard]]
    command_pool create_command_pool(VkCommandPoolCreateInfo const &create_info) const;

    [[nodiscard]]
    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo const &create_info) const;

    [[nodiscard]]
    descriptor_set_layout create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const &create_info) const;

    [[nodiscard]]
    descriptor_sets allocate_descriptor_sets(VkDescriptorSetAllocateInfo const &allocate_info) const;

    [[nodiscard]]
    device_memory allocate_memory(VkMemoryAllocateInfo const &allocate_info) const;

    [[nodiscard]]
    event create_event(VkEventCreateInfo const &create_info) const;

    [[nodiscard]]
    fence create_fence(VkFenceCreateInfo const &create_info) const;

    [[nodiscard]]
    framebuffer create_framebuffer(VkFramebufferCreateInfo const &create_info) const;

    [[nodiscard]]
    image create_image(VkImageCreateInfo const &create_info) const;

    [[nodiscard]]
    image_view create_image_view(VkImageViewCreateInfo const &create_info) const;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult>
    create_compute_pipelines(VkPipelineCache const                          &pipeline_cache,
                             std::vector<VkComputePipelineCreateInfo> const &create_infos) const;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult>
    create_graphics_pipelines(VkPipelineCache const                           &pipeline_cache,
                              std::vector<VkGraphicsPipelineCreateInfo> const &create_infos) const;

    [[nodiscard]]
    pipeline_cache create_pipeline_cache(VkPipelineCacheCreateInfo const &create_info) const;

    [[nodiscard]]
    pipeline_layout create_pipeline_layout(VkPipelineLayoutCreateInfo const &create_info) const;

    [[nodiscard]]
    query_pool create_query_pool(VkQueryPoolCreateInfo const &create_info) const;

    [[nodiscard]]
    queue get_device_queue(VkDeviceQueueInfo2 const &create_info) const;

    [[nodiscard]]
    render_pass create_render_pass(VkRenderPassCreateInfo2 const &create_info) const;

    [[nodiscard]]
    sampler create_sampler(VkSamplerCreateInfo const &create_info) const;

    [[nodiscard]]
    semaphore create_semaphore(VkSemaphoreCreateInfo const &create_info) const;

    [[nodiscard]]
    shader_module create_shader_module(VkShaderModuleCreateInfo const &create_info) const;

    [[nodiscard]]
    khr::swapchain create_swapchain(VkSwapchainCreateInfoKHR const &create_info) const;

    device(device &&)                 = default;
    device(device const &)            = delete;
    device &operator=(device &&)      = default;
    device &operator=(device const &) = delete;
    ~device()                         = default;

  private:
    friend struct physical_device;

    device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice const ptr);

    std::unordered_map<VkCommandPool,
                       std::weak_ptr<std::pointer_traits<VkCommandPool>::element_type>> mutable _registered_command_pools;
    std::unordered_map<VkDescriptorPool,
                       std::weak_ptr<std::pointer_traits<VkDescriptorPool>::element_type>> mutable _registered_descriptor_pools;
    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _handle;
};
}