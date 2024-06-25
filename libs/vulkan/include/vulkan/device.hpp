#pragma once

#include "def.hpp"
#include "non_dispatchable_handles.hpp"

#include <compare>
#include <memory>
#include <span>
#include <unordered_map>
#include <vector>

namespace vulkan
{
class device
{
  public:
    [[nodiscard]]
    VkDevice get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    [[nodiscard]]
    std::pair<buffer, VkResult const> create_buffer(VkBufferCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<buffer_view, VkResult const> create_buffer_view(VkBufferViewCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<command_pool, VkResult const> create_command_pool(VkCommandPoolCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<std::vector<command_buffer>, VkResult const> allocate_command_buffers(VkCommandBufferAllocateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<descriptor_set_layout, VkResult const> create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<descriptor_pool, VkResult const> create_descriptor_pool(VkDescriptorPoolCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<std::vector<descriptor_set>, VkResult const> allocate_descriptor_sets(VkDescriptorSetAllocateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<device_memory, VkResult const> allocate_device_memory(VkMemoryAllocateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<event, VkResult const> create_event(VkEventCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<fence, VkResult const> create_fence(VkFenceCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<framebuffer, VkResult const> create_framebuffer(VkFramebufferCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<image, VkResult const> create_image(VkImageCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<image_view, VkResult const> create_image_view(VkImageViewCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult const> create_pipelines(VkPipelineCache const                        cache,
                                                                      std::span<VkComputePipelineCreateInfo> const infos) noexcept;
    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult const> create_pipelines(VkPipelineCache const                         cache,
                                                                      std::span<VkGraphicsPipelineCreateInfo> const infos) noexcept;
    [[nodiscard]]
    std::pair<pipeline_cache, VkResult const> create_pipeline_cache(VkPipelineCacheCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<pipeline_layout, VkResult const> create_pipeline_layout(VkPipelineLayoutCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<query_pool, VkResult const> create_query_pool(VkQueryPoolCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<render_pass, VkResult const> create_render_pass(VkRenderPassCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<render_pass, VkResult const> create_render_pass(VkRenderPassCreateInfo2 const & info) noexcept;

    [[nodiscard]]
    std::pair<sampler, VkResult const> create_sampler(VkSamplerCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<semaphore, VkResult const> create_semaphore(VkSemaphoreCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<shader_module, VkResult const> create_shader_module(VkShaderModuleCreateInfo const & info) noexcept;

    [[nodiscard]]
    std::pair<khr::swapchain, VkResult const> create_swapchain(VkSwapchainCreateInfoKHR const & info) noexcept;

    void reset() noexcept;

    device() noexcept(std::is_nothrow_default_constructible_v<registered_command_pools_type> and
                      std::is_nothrow_default_constructible_v<registered_descriptor_pools_type>) = default;

    device(nullhandle_t) noexcept(std::is_nothrow_default_constructible_v<registered_command_pools_type> and
                                  std::is_nothrow_default_constructible_v<registered_descriptor_pools_type>);

    device(device &&) noexcept(std::is_nothrow_move_constructible_v<registered_command_pools_type> and
                               std::is_nothrow_move_constructible_v<registered_descriptor_pools_type>) = default;

    device(device const &) = delete;

    device & operator=(nullhandle_t) noexcept;

    device & operator=(device &&) noexcept(std::is_nothrow_move_assignable_v<registered_command_pools_type> and
                                           std::is_nothrow_move_assignable_v<registered_descriptor_pools_type>) = default;

    device & operator=(device const &) = delete;

    ~device() noexcept = default;

    std::strong_ordering operator<=>(device const & other) const noexcept;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    explicit operator bool() const noexcept;

  private:
    using registered_command_pools_type =
      std::unordered_map<VkCommandPool, std::weak_ptr<unique_handle<VkDevice, VkCommandPool, vkDestroyCommandPool>>>;

    using registered_descriptor_pools_type =
      std::unordered_map<VkDescriptorPool, std::weak_ptr<unique_handle<VkDevice, VkDescriptorPool, vkDestroyDescriptorPool>>>;

    std::shared_ptr<VkInstance_T>                _instance;
    std::shared_ptr<VkDevice_T>                  _device;
    std::shared_ptr<VkAllocationCallbacks const> _allocation_callbacks;
    registered_command_pools_type                _registered_command_pools;
    registered_descriptor_pools_type             _registered_descriptor_pools;

    friend struct internal;
};
}