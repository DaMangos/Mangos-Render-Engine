#pragma once

#include <vulkan/handles/unique_handle.hpp>

namespace vulkan::internal
{
struct make_unique_handle_t
{
    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static unique_handle<VkInstance, Handle, DeleteHandle> invoke(std::shared_ptr<VkInstance_T> const &                instance,
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
    static unique_handle<VkDevice, Handle, DeleteHandle> invoke(std::shared_ptr<VkInstance_T> const &                instance,
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
};

template <class Handle, auto DeleteHandle>
[[nodiscard]]
decltype(auto) make_unique_handle(auto &&... args)
{
  return make_unique_handle_t::invoke<Handle, DeleteHandle>(std::forward<decltype(args)>(args)...);
}
}