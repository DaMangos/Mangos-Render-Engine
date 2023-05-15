#include <handling.hpp>

namespace graphics::vk
{
class device final
{
  public:
    constexpr explicit device(unique_handle<VkDevice> device);

    [[nodiscard]]
    constexpr common_handle<VkDevice> get() const noexcept;

    [[nodiscard]]
    unique_handle<VkCommandBuffer> allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const;

    [[nodiscard]]
    unique_handle<VkCommandPool> create_command_pool(VkCommandPoolCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkFence> create_fence(VkFenceCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkFramebuffer> create_framebuffer(VkFramebufferCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkImageView> create_image_view(VkImageViewCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkPipelineLayout> create_pipeline_layout(VkPipelineLayoutCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkPipeline> create_compute_pipeline(VkComputePipelineCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkPipeline> create_graphics_pipeline(VkGraphicsPipelineCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkRenderPass> create_render_pass(VkRenderPassCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkSemaphore> create_semaphore(VkSemaphoreCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkShaderModule> create_shader_module(VkShaderModuleCreateInfo info) const;

    [[nodiscard]]
    unique_handle<VkSwapchainKHR> create_swapchain(VkSwapchainCreateInfoKHR info) const;

  private:
    unique_handle<VkDevice> _underling_device;
};
}