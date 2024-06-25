#pragma once

#include "../include/vulkan/device.hpp"
#include "../include/vulkan/instance.hpp"
#include "../include/vulkan/physical_device.hpp"
#include "../include/vulkan/range_element_handle.hpp"
#include "../include/vulkan/shared_handle.hpp"
#include "../include/vulkan/unique_handle.hpp"

namespace vulkan
{
struct internal
{
    [[nodiscard]]
    static instance make_instance(std::shared_ptr<VkInstance_T> const &                instance,
                                  std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept;

    [[nodiscard]]
    static physical_device make_physical_device(std::shared_ptr<VkInstance_T> const &                instance,
                                                VkPhysicalDevice const                               physical_device,
                                                std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept;
    [[nodiscard]]
    static device make_device(
      std::shared_ptr<VkInstance_T> const &                instance,
      std::shared_ptr<VkDevice_T> const &                  device,
      std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept(std::is_nothrow_default_constructible_v<::vulkan::device>);

    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static unique_handle<VkInstance, Handle, DeleteHandle> make_unique_handle(
      std::shared_ptr<VkInstance_T> const &                instance,
      Handle const                                         handle,
      std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept
    {
      unique_handle<VkInstance, Handle, DeleteHandle> result;
      result._dispatcher.instance  = instance;
      result._handle               = handle;
      result._allocation_callbacks = allocation_callbacks;
      return result;
    }

    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static unique_handle<VkDevice, Handle, DeleteHandle> make_unique_handle(
      std::shared_ptr<VkInstance_T> const &                instance,
      std::shared_ptr<VkDevice_T> const &                  device,
      Handle const                                         handle,
      std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept
    {
      unique_handle<VkDevice, Handle, DeleteHandle> result;
      result._dispatcher.instance  = instance;
      result._dispatcher.device    = device;
      result._handle               = handle;
      result._allocation_callbacks = allocation_callbacks;
      return result;
    }

    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static shared_handle<VkDevice, Handle, DeleteHandle> make_shared_handle(std::shared_ptr<VkInstance_T> const &                instance,
                                                                            std::shared_ptr<VkDevice_T> const &                  device,
                                                                            Handle const                                         handle,
                                                                            std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks)
    {
      shared_handle<VkDevice, Handle, DeleteHandle> result;
      result._shared = std::make_shared<unique_handle<VkDevice, Handle, DeleteHandle>>(
        make_unique_handle<Handle, DeleteHandle>(instance, device, handle, allocation_callbacks));
      return result;
    }

    template <class Handle>
    [[nodiscard]]
    static range_element_handle<Handle> make_range_element_handle(std::shared_ptr<Handle[]> const & handles,
                                                                  std::uint32_t const               size,
                                                                  std::uint32_t const               index) noexcept
    {
      range_element_handle<Handle> result;
      result._handles = handles;
      result._size    = size;
      result._index   = index;
      return result;
    }

    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<unique_handle<VkInstance, Handle, DestroyHandle>, VkResult const> create_unique_handle(
      std::shared_ptr<VkInstance_T> const &                instance,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & allocator) noexcept
    {
      if(not instance)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(instance.get(), info, allocator.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      return {make_unique_handle<Handle, DestroyHandle>(instance, handle, allocator), result};
    }

    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<unique_handle<VkDevice, Handle, DestroyHandle>, VkResult const> create_unique_handle(
      std::shared_ptr<VkInstance_T> const &                instance,
      std::shared_ptr<VkDevice_T> const &                  device,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & allocator) noexcept
    {
      if(not instance or not device)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(device.get(), info, allocator.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      return {make_unique_handle<Handle, DestroyHandle>(instance, device, handle, allocator), result};
    }

    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<shared_handle<VkDevice, Handle, DestroyHandle>, VkResult const> create_shared_handle(
      std::shared_ptr<VkInstance_T> const &                                                       instance,
      std::shared_ptr<VkDevice_T> const &                                                         device,
      auto const &                                                                                info,
      std::shared_ptr<VkAllocationCallbacks const> const &                                        allocator,
      std::unordered_map<Handle, std::weak_ptr<unique_handle<VkDevice, Handle, DestroyHandle>>> & registered) noexcept
    {
      try
      {
        if(not instance or not device)
          return {nullhandle, VK_ERROR_UNKNOWN};

        Handle     handle = VK_NULL_HANDLE;
        auto const result = CreateHandle(device.get(), info, allocator.get(), &handle);

        if(static_cast<int>(result) < 0)
          return {nullhandle, result};

        auto shared_handle = make_shared_handle<Handle, DestroyHandle>(instance, device, handle, allocator);
        registered.emplace(handle, shared_handle._shared);

        return std::pair(std::move(shared_handle), result);
      }
      catch(std::exception const &)
      {
        return {nullhandle, VK_ERROR_UNKNOWN};
      }
    }

    template <auto CreatePipeline>
    [[nodiscard]]
    static std::pair<std::vector<pipeline>, VkResult const> create_pipelines(std::shared_ptr<VkInstance_T> const &                instance,
                                                                             std::shared_ptr<VkDevice_T> const &                  device,
                                                                             VkPipelineCache const                                cache,
                                                                             std::ranges::contiguous_range auto const &           infos,
                                                                             std::shared_ptr<VkAllocationCallbacks const> const & allocator) noexcept
    {
      try
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
      catch(std::exception const &)
      {
        return {std::vector<pipeline>(), VK_ERROR_UNKNOWN};
      }
    }
};
}