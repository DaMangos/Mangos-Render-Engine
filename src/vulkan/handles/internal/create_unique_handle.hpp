#pragma once

#include "make_unique_handle.hpp"

namespace vulkan::internal
{
struct create_unique_handle_t
{
    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<unique_handle<VkInstance, Handle, DestroyHandle>, VkResult const> invoke(
      std::shared_ptr<VkInstance_T> const &                shared_instance,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & shared_allocation_callback)
    {
      if(not shared_instance)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(shared_instance.get(), info, shared_allocation_callback.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      return {make_unique_handle<Handle, DestroyHandle>(shared_instance, handle, shared_allocation_callback), result};
    }

    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<unique_handle<VkDevice, Handle, DestroyHandle>, VkResult const> invoke(
      std::shared_ptr<VkInstance_T> const &                shared_instance,
      std::shared_ptr<VkDevice_T> const &                  shared_device,
      auto const &                                         info,
      std::shared_ptr<VkAllocationCallbacks const> const & shared_allocation_callback)
    {
      if(not shared_instance or not shared_device)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(shared_device.get(), info, shared_allocation_callback.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      return {make_unique_handle<Handle, DestroyHandle>(shared_instance, shared_device, handle, shared_allocation_callback), result};
    }
};

template <class Handle, auto CreateHandle, auto DestroyHandle>
[[nodiscard]]
decltype(auto) create_unique_handle(auto &&... args)
{
  return create_unique_handle_t::invoke<Handle, CreateHandle, DestroyHandle>(std::forward<decltype(args)>(args)...);
}
}
