#pragma once

#include "deleter.hpp"
#include "unique_handle.hpp"
#include "unique_vector.hpp"

namespace graphics::vulkan
{
struct device
{
    device(unique_handle<VkDevice> device) noexcept;

    VkDevice get() const noexcept;

    unique_vector<VkCommandBuffer> allocate_command_buffers(VkCommandPool               command_pool,
                                                            VkCommandBufferAllocateInfo allocate_info) const;

    unique_handle<VkCommandPool> create_command_pool(VkCommandPoolCreateInfo create_info) const;

    unique_handle<VkFence> create_fence(VkFenceCreateInfo create_info) const;

    unique_handle<VkFramebuffer> create_framebuffer(VkFramebufferCreateInfo create_info) const;

    unique_handle<VkImageView> create_image_view(VkImageViewCreateInfo create_info) const;

    unique_handle<VkPipelineLayout> create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const;

    unique_vector<VkPipeline> create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                      std::vector<VkComputePipelineCreateInfo> create_infos) const;

    unique_vector<VkPipeline> create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                       std::vector<VkGraphicsPipelineCreateInfo> create_infos) const;

    unique_handle<VkRenderPass> create_render_pass(VkRenderPassCreateInfo create_info) const;

    unique_handle<VkRenderPass> create_render_pass(VkRenderPassCreateInfo2 create_info) const;

    unique_handle<VkSemaphore> create_semaphore(VkSemaphoreCreateInfo create_info) const;

    unique_handle<VkShaderModule> create_shader_module(VkShaderModuleCreateInfo create_info) const;

    unique_handle<VkSwapchainKHR> create_swapchain(VkSwapchainCreateInfoKHR create_info) const;

  private:
    unique_handle<VkDevice> _underling_device;
};
}