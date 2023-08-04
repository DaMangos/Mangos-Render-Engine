#include "device.hpp"

namespace graphics::vulkan
{
device::device(unique_handle<VkDevice> device) noexcept
: _underling_device(std::move(device))
{
}

VkDevice device::get() const noexcept
{
  return _underling_device.get();
}

unique_handle<VkCommandBuffer[]> device::allocate_command_buffers(VkCommandPool               command_pool,
                                                                  VkCommandBufferAllocateInfo allocate_info) const
{
  std::vector<VkCommandBuffer> command_buffers(allocate_info.commandBufferCount);
  return return_or_throw(vkAllocateCommandBuffers(get(), &allocate_info, command_buffers.data()),
                         "vkAllocateCommandBuffers",
                         unique_handle<VkCommandBuffer[]>(command_buffers, get(), command_pool));
}

unique_handle<VkCommandPool> device::create_command_pool(VkCommandPoolCreateInfo create_info) const
{
  VkCommandPool command_pool;
  return return_or_throw(vkCreateCommandPool(get(), &create_info, nullptr, &command_pool),
                         "vkCreateCommandPool",
                         unique_handle<VkCommandPool>(command_pool, get()));
}

unique_handle<VkFence> device::create_fence(VkFenceCreateInfo create_info) const
{
  VkFence fence;
  return return_or_throw(vkCreateFence(get(), &create_info, nullptr, &fence),
                         "vkCreateFence",
                         unique_handle<VkFence>(fence, get()));
}

unique_handle<VkFramebuffer> device::create_framebuffer(VkFramebufferCreateInfo create_info) const
{
  VkFramebuffer framebuffer;
  return return_or_throw(vkCreateFramebuffer(get(), &create_info, nullptr, &framebuffer),
                         "vkCreateFramebuffer",
                         unique_handle<VkFramebuffer>(framebuffer, get()));
}

unique_handle<VkImageView> device::create_image_view(VkImageViewCreateInfo create_info) const
{
  VkImageView image_view;
  return return_or_throw(vkCreateImageView(get(), &create_info, nullptr, &image_view),
                         "vkCreateImageView",
                         unique_handle<VkImageView>(image_view, get()));
}

unique_handle<VkPipelineLayout> device::create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const
{
  VkPipelineLayout pipeline_layout;
  return return_or_throw(vkCreatePipelineLayout(get(), &create_info, nullptr, &pipeline_layout),
                         "vkCreatePipelineLayout",
                         unique_handle<VkPipelineLayout>(pipeline_layout, get()));
}

unique_handle<VkPipeline[]> device::create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                            std::vector<VkComputePipelineCreateInfo> create_infos) const
{
  std::vector<VkPipeline> pipelines(create_infos.size());
  return return_or_throw(
    vkCreateComputePipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, pipelines.data()),
    "vkCreateComputePipelines",
    unique_handle<VkPipeline[]>(pipelines, get()));
}

unique_handle<VkPipeline[]> device::create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                             std::vector<VkGraphicsPipelineCreateInfo> create_infos) const
{
  std::vector<VkPipeline> pipelines(create_infos.size());
  return return_or_throw(
    vkCreateGraphicsPipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, pipelines.data()),
    "vkCreateGraphicsPipelines",
    unique_handle<VkPipeline[]>(pipelines, get()));
}

unique_handle<VkRenderPass> device::create_render_pass(VkRenderPassCreateInfo create_info) const
{
  VkRenderPass render_pass;
  return return_or_throw(vkCreateRenderPass(get(), &create_info, nullptr, &render_pass),
                         "vkCreateRenderPass",
                         unique_handle<VkRenderPass>(render_pass, get()));
}

unique_handle<VkRenderPass> device::create_render_pass(VkRenderPassCreateInfo2 create_info) const
{
  VkRenderPass render_pass;
  return return_or_throw(vkCreateRenderPass2(get(), &create_info, nullptr, &render_pass),
                         "vkCreateRenderPass2",
                         unique_handle<VkRenderPass>(render_pass, get()));
}

unique_handle<VkSemaphore> device::create_semaphore(VkSemaphoreCreateInfo create_info) const
{
  VkSemaphore semaphore;
  return return_or_throw(vkCreateSemaphore(get(), &create_info, nullptr, &semaphore),
                         "vkCreateSemaphore",
                         unique_handle<VkSemaphore>(semaphore, get()));
}

unique_handle<VkShaderModule> device::create_shader_module(VkShaderModuleCreateInfo create_info) const
{
  VkShaderModule shader_module;
  return return_or_throw(vkCreateShaderModule(get(), &create_info, nullptr, &shader_module),
                         "vkCreateShaderModule",
                         unique_handle<VkShaderModule>(shader_module, get()));
}

unique_handle<VkSwapchainKHR> device::create_swapchain(VkSwapchainCreateInfoKHR create_info) const
{
  VkSwapchainKHR shader_module;
  return return_or_throw(vkCreateSwapchainKHR(get(), &create_info, nullptr, &shader_module),
                         "vkCreateSwapchainKHR",
                         unique_handle<VkSwapchainKHR>(shader_module, get()));
}
}