#pragma once

#include "make_shared_handle.hpp"
#include <unordered_map>

namespace vulkan::internal
{
struct create_shared_handle_t
{
    template <class Handle, auto CreateHandle, auto DestroyHandle>
    [[nodiscard]]
    static std::pair<shared_handle<VkDevice, Handle, DestroyHandle>, VkResult const> invoke(
      std::shared_ptr<VkInstance_T> const &                                                       shared_instance,
      std::shared_ptr<VkDevice_T> const &                                                         shared_device,
      auto const &                                                                                info,
      std::shared_ptr<VkAllocationCallbacks const> const &                                        shared_allocation_callback,
      std::unordered_map<Handle, std::weak_ptr<unique_handle<VkDevice, Handle, DestroyHandle>>> & registered)
    {
      if(not shared_instance or not shared_device)
        return {nullhandle, VK_ERROR_UNKNOWN};

      Handle     handle = VK_NULL_HANDLE;
      auto const result = CreateHandle(shared_device.get(), info, shared_allocation_callback.get(), &handle);

      if(static_cast<int>(result) < 0)
        return {nullhandle, result};

      auto shared_handle = make_shared_handle<Handle, DestroyHandle>(shared_instance, shared_device, handle, shared_allocation_callback);
      registered.emplace(handle, shared_handle._underlying_handle);

      return std::pair(std::move(shared_handle), result);
    }
};

template <class Handle, auto CreateHandle, auto DestroyHandle>
[[nodiscard]]
decltype(auto) create_shared_handle(auto &&... args)
{
  return create_shared_handle_t::invoke<Handle, CreateHandle, DestroyHandle>(std::forward<decltype(args)>(args)...);
}
}
