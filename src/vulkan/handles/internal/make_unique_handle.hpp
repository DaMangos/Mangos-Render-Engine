#pragma once

#include <vulkan/handles/unique_handle.hpp>

namespace vulkan::internal
{
struct make_unique_handle_t
{
    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static unique_handle<VkInstance, Handle, DeleteHandle> invoke(
      std::shared_ptr<VkInstance_T> const &                shared_instance,
      Handle const                                         handle,
      std::shared_ptr<VkAllocationCallbacks const> const & shared_allocation_callbacks) noexcept
    {
      unique_handle<VkInstance, Handle, DeleteHandle> result;
      result._shared_dispatcher.shared_instance = shared_instance;
      result._handle                            = handle;
      result._shared_allocation_callbacks       = shared_allocation_callbacks;
      return result;
    }

    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static unique_handle<VkDevice, Handle, DeleteHandle> invoke(
      std::shared_ptr<VkInstance_T> const &                shared_instance,
      std::shared_ptr<VkDevice_T> const &                  shared_device,
      Handle const                                         handle,
      std::shared_ptr<VkAllocationCallbacks const> const & shared_allocation_callbacks) noexcept
    {
      unique_handle<VkDevice, Handle, DeleteHandle> result;
      result._shared_dispatcher.shared_instance = shared_instance;
      result._shared_dispatcher.shared_device   = shared_device;
      result._handle                            = handle;
      result._shared_allocation_callbacks       = shared_allocation_callbacks;
      return result;
    }
};

template <class Handle, auto DeleteHandle>
[[nodiscard]]
decltype(auto) make_unique_handle(auto &&... args)
{
  return make_unique_handle_t::invoke<Handle, DeleteHandle>(std::forward<decltype(args)>(args)...);
}
}