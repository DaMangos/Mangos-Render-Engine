#pragma once

#include "non_dispatchable.hpp"

#include <string>
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
    create_compute_pipelines(VkPipelineCache const                    &pipeline_cache,
                             std::ranges::contiguous_range auto const &create_infos) const
      requires std::same_as<std::ranges::range_value_t<decltype(create_infos)>, VkComputePipelineCreateInfo>
    {
      return create_pipeline<vkCreateComputePipelines, "VkComputePipelineCreateInfo">(pipeline_cache, create_infos);
    }

    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult>
    create_graphics_pipelines(VkPipelineCache const                    &pipeline_cache,
                              std::ranges::contiguous_range auto const &create_infos) const
      requires std::same_as<std::ranges::range_value_t<decltype(create_infos)>, VkGraphicsPipelineCreateInfo>
    {
      return create_pipeline<vkCreateGraphicsPipelines, "VkGraphicsPipelineCreateInfo">(pipeline_cache, create_infos);
    }

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
    template <auto const create_function, char const *const create_info_name>
    [[nodiscard]]
    std::pair<std::vector<pipeline>, VkResult> create_pipelines(VkPipelineCache const                    &pipeline_cache,
                                                                std::ranges::contiguous_range auto const &create_infos) const
    {
      if(std::cmp_greater(std::ranges::size(create_infos), std::numeric_limits<std::uint32_t>::max()))
        throw std::runtime_error(std::string("failed to create VkPipeline: too many ") + create_info_name);
      auto ptrs      = std::vector<VkPipeline>(std::ranges::size(create_infos));
      auto pipelines = std::vector<pipeline>();
      pipelines.reserve(std::ranges::size(create_infos));
      switch(VkResult result = create_function(get(),
                                               pipeline_cache,
                                               static_cast<std::uint32_t>(std::ranges::size(create_infos)),
                                               std::ranges::data(create_infos),
                                               nullptr,
                                               ptrs.data()))
      {
        case VK_SUCCESS | VK_PIPELINE_COMPILE_REQUIRED_EXT :
        {
          std::ranges::transform(ptrs,
                                 std::back_inserter(pipelines),
                                 [this](auto const &ptr) { return pipeline(_handle, ptr); });
          return std::make_pair(std::move(pipelines), result);
        }
        case VK_ERROR_OUT_OF_HOST_MEMORY :
          throw std::runtime_error("failed to create VkPipeline: out of host memory");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY :
          throw std::runtime_error("failed to create VkPipeline: out of device memory");
        case VK_ERROR_INVALID_SHADER_NV :
          throw std::runtime_error("failed to create VkPipeline: invalid shader");
        default :
          throw std::runtime_error("failed to create VkPipeline: unknown error");
      }
    }

    friend struct physical_device;

    device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkDevice const ptr);

    std::unordered_map<VkCommandPool,
                       std::weak_ptr<std::pointer_traits<VkCommandPool>::element_type>> mutable _registered_command_pools;
    std::unordered_map<VkDescriptorPool,
                       std::weak_ptr<std::pointer_traits<VkDescriptorPool>::element_type>> mutable _registered_descriptor_pools;
    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _handle;
};
}