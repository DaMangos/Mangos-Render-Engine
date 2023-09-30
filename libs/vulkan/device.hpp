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
    VkDevice get() const noexcept;

    [[nodiscard]]
    VkInstance get_instance() const noexcept;

    [[nodiscard]]
    buffer create_buffer(VkBufferCreateInfo create_info) const;

    [[nodiscard]]
    buffer_view create_buffer_view(VkBufferViewCreateInfo create_info) const;

    [[nodiscard]]
    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const;

    [[nodiscard]]
    command_pool create_command_pool(VkCommandPoolCreateInfo create_info) const;

    [[nodiscard]]
    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo create_info) const;

    [[nodiscard]]
    descriptor_set_layout create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo create_info) const;

    [[nodiscard]]
    descriptor_sets allocate_descriptor_sets(VkDescriptorSetAllocateInfo allocate_info) const;

    [[nodiscard]]
    device_memory allocate_memory(VkMemoryAllocateInfo allocate_info) const;

    [[nodiscard]]
    event create_event(VkEventCreateInfo create_info) const;

    [[nodiscard]]
    fence create_fence(VkFenceCreateInfo create_info) const;

    [[nodiscard]]
    framebuffer create_framebuffer(VkFramebufferCreateInfo create_info) const;

    [[nodiscard]]
    image create_image(VkImageCreateInfo create_info) const;

    [[nodiscard]]
    image_view create_image_view(VkImageViewCreateInfo create_info) const;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult>
    create_compute_pipeline(VkPipelineCache pipeline_cache, std::vector<VkComputePipelineCreateInfo> create_infos) const;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult>
    create_graphics_pipeline(VkPipelineCache pipeline_cache, std::vector<VkGraphicsPipelineCreateInfo> create_infos) const;

    [[nodiscard]]
    pipeline_cache create_pipeline_cache(VkPipelineCacheCreateInfo create_info) const;

    [[nodiscard]]
    pipeline_layout create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const;

    [[nodiscard]]
    query_pool create_query_pool(VkQueryPoolCreateInfo create_info) const;

    [[nodiscard]]
    queue get_device_queue(VkDeviceQueueInfo2 create_info) const;

    [[nodiscard]]
    render_pass create_render_pass(VkRenderPassCreateInfo2 create_info) const;

    [[nodiscard]]
    sampler create_sampler(VkSamplerCreateInfo create_info) const;

    [[nodiscard]]
    semaphore create_semaphore(VkSemaphoreCreateInfo create_info) const;

    [[nodiscard]]
    shader_module create_shader_module(VkShaderModuleCreateInfo create_info) const;

    [[nodiscard]]
    khr::swapchain create_swapchain(VkSwapchainCreateInfoKHR create_info) const;

    device(device &&)                 = default;
    device(device const &)            = delete;
    device &operator=(device &&)      = default;
    device &operator=(device const &) = delete;
    ~device()                         = default;

  private:
    friend struct physical_device;

    device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice ptr);

    std::unordered_map<VkCommandPool,
                       std::weak_ptr<std::pointer_traits<VkCommandPool>::element_type>> mutable _registered_command_pools;
    std::unordered_map<VkDescriptorPool,
                       std::weak_ptr<std::pointer_traits<VkDescriptorPool>::element_type>> mutable _registered_descriptor_pools;
    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _handle;
};
}