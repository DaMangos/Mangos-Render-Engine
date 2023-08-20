#pragma once

#include "fwd.hpp"

#include <unordered_map>
#include <vector>

namespace vulkan
{
struct device
{
    using element_type = typename device_handle::element_type;
    using pointer      = typename device_handle::pointer;

    VkDevice get() const noexcept;

    buffer create_buffer(VkBufferCreateInfo create_info) const;

    buffer_view create_buffer_view(VkBufferViewCreateInfo create_info) const;

    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const;

    command_pool create_command_pool(VkCommandPoolCreateInfo create_info);

    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo create_info);

    descriptor_set_layout create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo create_info) const;

    descriptor_sets allocate_descriptor_sets(VkDescriptorSetAllocateInfo allocate_info) const;

    device_memory allocate_memory(VkMemoryAllocateInfo allocate_info) const;

    event create_event(VkEventCreateInfo create_info) const;

    fence create_fence(VkFenceCreateInfo create_info) const;

    framebuffer create_framebuffer(VkFramebufferCreateInfo create_info) const;

    image create_image(VkImageCreateInfo create_info) const;

    image_view create_image_view(VkImageViewCreateInfo create_info) const;

    std::vector<pipeline> create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                  std::vector<VkComputePipelineCreateInfo> create_infos) const;

    std::vector<pipeline> create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                   std::vector<VkGraphicsPipelineCreateInfo> create_infos) const;

    pipeline_cache create_pipeline_cache(VkPipelineCacheCreateInfo create_info) const;

    pipeline_layout create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const;

    query_pool create_query_pool(VkQueryPoolCreateInfo create_info) const;

    queue get_device_queue(VkDeviceQueueInfo2 create_info) const;

    render_pass create_render_pass(VkRenderPassCreateInfo2 create_info) const;

    sampler create_sampler(VkSamplerCreateInfo create_info) const;

    semaphore create_semaphore(VkSemaphoreCreateInfo create_info) const;

    shader_module create_shader_module(VkShaderModuleCreateInfo create_info) const;

    khr::swapchain create_swapchain(VkSwapchainCreateInfoKHR create_info) const;

    device &operator=(device const &) = delete;
    device &operator=(device &&)      = default;
    device(device const &)            = delete;
    device(device &&)                 = default;
    ~device()                         = default;

  private:
    friend struct physical_device;

    device(device_handle device) noexcept;

    device_handle                                                                    _device;
    std::unordered_map<VkCommandPool, typename command_pool_handle::weak_type>       _registered_command_pools;
    std::unordered_map<VkDescriptorPool, typename descriptor_pool_handle::weak_type> _registered_descriptor_pools;
};
}