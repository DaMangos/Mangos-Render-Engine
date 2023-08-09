#pragma once

#include "non_dispatchable_handles.hpp"

#include <vector>

namespace vulkan
{
struct device
{
    friend physical_device;

    using pointer       = typename handle_traits<VkDevice>::pointer;
    using const_pointer = typename handle_traits<VkDevice>::const_pointer;
    using element_type  = typename handle_traits<VkDevice>::element_type;
    using deleter_type  = typename handle_traits<VkDevice>::deleter_type;
    using unique_type   = typename handle_traits<VkDevice>::unique_type;
    using shared_type   = typename handle_traits<VkDevice>::shared_type;

    pointer get() const noexcept;

    buffer create_buffer(VkBufferCreateInfo create_info) const;

    image create_image(VkImageCreateInfo create_info) const;

    semaphore create_semaphore(VkSemaphoreCreateInfo create_info) const;

    fence create_fence(VkFenceCreateInfo create_info) const;

    device_memory allocate_device_memory(VkMemoryAllocateInfo allocate_info) const;

    event create_event(VkEventCreateInfo create_info) const;

    query_pool create_query_pool(VkQueryPoolCreateInfo create_info) const;

    buffer_view create_buffer_view(VkBufferViewCreateInfo create_info) const;

    image_view create_image_view(VkImageViewCreateInfo create_info) const;

    shader_module create_shader_module(VkShaderModuleCreateInfo create_info) const;

    pipeline_cache create_pipeline_cache(VkPipelineCacheCreateInfo create_info) const;

    pipeline_layout create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const;

    render_pass create_render_pass(VkRenderPassCreateInfo create_info) const;

    descriptor_set_layout create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo create_info) const;

    sampler create_sampler(VkSamplerCreateInfo create_info) const;

    descriptor_sets allocate_descriptor_sets(VkDescriptorSetAllocateInfo allocate_info) const;

    descriptor_pool create_descriptor_pool(VkDescriptorPoolCreateInfo create_info) const;

    framebuffer create_framebuffer(VkFramebufferCreateInfo create_info) const;

    command_pool create_command_pool(VkCommandPoolCreateInfo create_info) const;

    command_buffers allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const;

    queue get_device_queue(VkDeviceQueueInfo2 queue_info) const;

    std::vector<pipeline> create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                  std::vector<VkComputePipelineCreateInfo> create_infos) const;

    std::vector<pipeline> create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                   std::vector<VkGraphicsPipelineCreateInfo> create_infos) const;

    khr::swapchain create_swapchain(VkSwapchainCreateInfoKHR create_info) const;

    khr::video_session create_video_session(VkVideoSessionCreateInfoKHR create_info) const;

    // khr::video_session_parameters create_video_session_parameters(VkVideoSessionParametersCreateInfoKHR create_info) const;

    // khr::deferred_operation create_deferred_operation() const;

    // khr::acceleration_structure create_acceleration_structure(VkAccelerationStructureCreateInfoKHR create_info) const;

    // ext::validation_cache create_validation_cache(VkValidationCacheCreateInfoEXT create_info) const;

    // ext::micromap create_micromap(VkMicromapCreateInfoEXT create_info) const;

    // std::vector<ext::shader> create_shader(std::vector<VkShaderCreateInfoEXT> create_infos) const;

  private:
    device(pointer device, deleter_type &&deleter);

    unique_type _device;
};
}