#pragma once

#include "make_unique_handle.hpp"

namespace vulkan::internal
{
struct create_unique_handle_t
{
    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<unique_handle<VkInstance, Handle, DestroyHandle>, VkResult const> invoke(
      std::shared_ptr<VkInstance_T> const &                instance,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & allocator)
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
    static std::pair<unique_handle<VkDevice, Handle, DestroyHandle>, VkResult const> invoke(
      std::shared_ptr<VkInstance_T> const &                instance,
      std::shared_ptr<VkDevice_T> const &                  device,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & allocator)
    {
      if(not instance or not device)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(device.get(), info, allocator.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      return {make_unique_handle<Handle, DestroyHandle>(instance, device, handle, allocator), result};
    }
};

template <class Handle, auto CreateHandle, auto DestroyHandle>
[[nodiscard]]
decltype(auto) create_unique_handle(auto &&... args)
{
  return create_unique_handle_t::invoke<Handle, CreateHandle, DestroyHandle>(std::forward<decltype(args)>(args)...);
}
}
