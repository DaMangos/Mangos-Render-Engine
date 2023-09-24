#pragma once

#include "command_buffers.hpp"
#include "descriptor_sets.hpp"
#include "non_dispatchable.hpp"
#include "queue.hpp"

#include <list>
#include <vector>

namespace vulkan
{
struct device final
{
    [[nodiscard]]
    VkDevice get() const noexcept;

    [[nodiscard]]
    buffer create_buffer(VkBufferCreateInfo create_info) const;

    [[nodiscard]]
    buffer_view create_buffer_view(VkBufferViewCreateInfo create_info) const;

    [[nodiscard]]
    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const;

    [[nodiscard]]
    command_pool create_command_pool(VkCommandPoolCreateInfo create_info);

    [[nodiscard]]
    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo create_info);

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
    std::list<pipeline> create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                std::vector<VkComputePipelineCreateInfo> create_infos) const;

    [[nodiscard]]
    std::list<pipeline> create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                 std::vector<VkGraphicsPipelineCreateInfo> create_infos) const;

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

  private:
    friend struct physical_device;

    device(VkDevice &&device) noexcept;

    mgo::apply_in_destructor<[](VkDevice device) { vkDestroyDevice(device, nullptr); }, VkDevice> device_;
};
}