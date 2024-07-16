#pragma once

#include <vulkan/handles/device.hpp>
#include <vulkan/handles/instance.hpp>
#include <vulkan/handles/physical_device.hpp>
#include <vulkan/handles/range_element_handle.hpp>
#include <vulkan/handles/shared_handle.hpp>

#include "make_unique_handle.hpp"

namespace vulkan::internal
{
struct create_pipelines_t
{
    template <auto CreatePipeline>
    [[nodiscard]]
    static std::pair<std::vector<pipeline>, VkResult const> invoke(std::shared_ptr<VkInstance_T> const &                instance,
                                                                   std::shared_ptr<VkDevice_T> const &                  device,
                                                                   VkPipelineCache const                                cache,
                                                                   std::ranges::contiguous_range auto const &           infos,
                                                                   std::shared_ptr<VkAllocationCallbacks const> const & allocator)
    {
      if(not instance or not device or std::ranges::size(infos) > static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()))
        return {std::vector<pipeline>(), VK_ERROR_UNKNOWN};

      std::vector<pipeline> pipelines;

      pipelines.reserve(std::ranges::size(infos));

      std::vector<VkPipeline> handles(std::ranges::size(infos), VK_NULL_HANDLE);

      auto const result = CreatePipeline(device.get(),
                                         cache,
                                         static_cast<std::uint32_t>(std::ranges::size(infos)),
                                         std::ranges::data(infos),
                                         allocator.get(),
                                         handles.data());

      if(static_cast<int>(result) < 0)
        return {std::vector<pipeline>(), result};

      for(auto const handle : handles)
        pipelines.emplace_back(make_unique_handle<VkPipeline, vkDestroyPipeline>(instance, device, handle, allocator));

      return {std::move(pipelines), result};
    }
};

template <auto CreatePipeline>
[[nodiscard]]
decltype(auto) create_pipelines(auto &&... args)
{
  return create_pipelines_t::invoke<CreatePipeline>(std::forward<decltype(args)>(args)...);
}
}