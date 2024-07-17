#pragma once

#include <vulkan/handles/shared_handle.hpp>

#include "make_unique_handle.hpp"

namespace vulkan::internal
{
struct make_shared_handle_t
{
    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static shared_handle<VkDevice, Handle, DeleteHandle> invoke(std::shared_ptr<VkInstance_T> const &                shared_instance,
                                                                std::shared_ptr<VkDevice_T> const &                  shared_device,
                                                                Handle const                                         handle,
                                                                std::shared_ptr<VkAllocationCallbacks const> const & shared_allocation_callbacks)
    {
      shared_handle<VkDevice, Handle, DeleteHandle> result;
      result._underlying_handle = std::make_shared<unique_handle<VkDevice, Handle, DeleteHandle>>(
        make_unique_handle<Handle, DeleteHandle>(shared_instance, shared_device, handle, shared_allocation_callbacks));
      return result;
    }
};

template <class Handle, auto DeleteHandle>
[[nodiscard]]
decltype(auto) make_shared_handle(auto &&... args)
{
  return make_shared_handle_t::invoke<Handle, DeleteHandle>(std::forward<decltype(args)>(args)...);
}
}