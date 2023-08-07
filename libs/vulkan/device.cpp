#include <vulkan/device.hpp>

namespace vulkan
{
device::device(mgo::unique_handle<VkDevice> device) noexcept
: _underling_device(std::move(device))
{
}

VkDevice device::get() const noexcept
{
  return _underling_device.get();
}

mgo::unique_vector<VkCommandBuffer> device::allocate_command_buffers(VkCommandPool               command_pool,
                                                                     VkCommandBufferAllocateInfo allocate_info) const
{
  std::vector<VkCommandBuffer> command_buffers(allocate_info.commandBufferCount);
  return return_or_throw(vkAllocateCommandBuffers(get(), &allocate_info, command_buffers.data()),
                         "vkAllocateCommandBuffers",
                         mgo::make_unique_vector(command_buffers, get(), command_pool));
}

mgo::unique_handle<VkCommandPool> device::create_command_pool(VkCommandPoolCreateInfo create_info) const
{
  VkCommandPool command_pool;
  return return_or_throw(vkCreateCommandPool(get(), &create_info, nullptr, &command_pool),
                         "vkCreateCommandPool",
                         mgo::make_unique_handle(command_pool, get()));
}

mgo::unique_handle<VkFence> device::create_fence(VkFenceCreateInfo create_info) const
{
  VkFence fence;
  return return_or_throw(vkCreateFence(get(), &create_info, nullptr, &fence),
                         "vkCreateFence",
                         mgo::make_unique_handle(fence, get()));
}

mgo::unique_handle<VkFramebuffer> device::create_framebuffer(VkFramebufferCreateInfo create_info) const
{
  VkFramebuffer framebuffer;
  return return_or_throw(vkCreateFramebuffer(get(), &create_info, nullptr, &framebuffer),
                         "vkCreateFramebuffer",
                         mgo::make_unique_handle(framebuffer, get()));
}

mgo::unique_handle<VkImageView> device::create_image_view(VkImageViewCreateInfo create_info) const
{
  VkImageView image_view;
  return return_or_throw(vkCreateImageView(get(), &create_info, nullptr, &image_view),
                         "vkCreateImageView",
                         mgo::make_unique_handle(image_view, get()));
}

mgo::unique_handle<VkPipelineLayout> device::create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const
{
  VkPipelineLayout pipeline_layout;
  return return_or_throw(vkCreatePipelineLayout(get(), &create_info, nullptr, &pipeline_layout),
                         "vkCreatePipelineLayout",
                         mgo::make_unique_handle(pipeline_layout, get()));
}

mgo::unique_vector<VkPipeline> device::create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                               std::vector<VkComputePipelineCreateInfo> create_infos) const
{
  std::vector<VkPipeline> pipelines(create_infos.size());
  return return_or_throw(
    vkCreateComputePipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, pipelines.data()),
    "vkCreateComputePipelines",
    mgo::make_unique_vector(pipelines, get()));
}

mgo::unique_vector<VkPipeline> device::create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                                std::vector<VkGraphicsPipelineCreateInfo> create_infos) const
{
  std::vector<VkPipeline> pipelines(create_infos.size());
  return return_or_throw(
    vkCreateGraphicsPipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, pipelines.data()),
    "vkCreateGraphicsPipelines",
    mgo::make_unique_vector(pipelines, get()));
}

mgo::unique_handle<VkRenderPass> device::create_render_pass(VkRenderPassCreateInfo create_info) const
{
  VkRenderPass render_pass;
  return return_or_throw(vkCreateRenderPass(get(), &create_info, nullptr, &render_pass),
                         "vkCreateRenderPass",
                         mgo::make_unique_handle(render_pass, get()));
}

mgo::unique_handle<VkRenderPass> device::create_render_pass(VkRenderPassCreateInfo2 create_info) const
{
  VkRenderPass render_pass;
  return return_or_throw(vkCreateRenderPass2(get(), &create_info, nullptr, &render_pass),
                         "vkCreateRenderPass2",
                         mgo::make_unique_handle(render_pass, get()));
}

mgo::unique_handle<VkSemaphore> device::create_semaphore(VkSemaphoreCreateInfo create_info) const
{
  VkSemaphore semaphore;
  return return_or_throw(vkCreateSemaphore(get(), &create_info, nullptr, &semaphore),
                         "vkCreateSemaphore",
                         mgo::make_unique_handle(semaphore, get()));
}

mgo::unique_handle<VkShaderModule> device::create_shader_module(VkShaderModuleCreateInfo create_info) const
{
  VkShaderModule shader_module;
  return return_or_throw(vkCreateShaderModule(get(), &create_info, nullptr, &shader_module),
                         "vkCreateShaderModule",
                         mgo::make_unique_handle(shader_module, get()));
}

mgo::unique_handle<VkSwapchainKHR> device::create_swapchain(VkSwapchainCreateInfoKHR create_info) const
{
  VkSwapchainKHR shader_module;
  return return_or_throw(vkCreateSwapchainKHR(get(), &create_info, nullptr, &shader_module),
                         "vkCreateSwapchainKHR",
                         mgo::make_unique_handle(shader_module, get()));
}
}