#pragma once

#include <vulkan/handles/shared_handle.hpp>

#include "make_unique_handle.hpp"

namespace vulkan::internal
{
struct make_shared_handle_t
{
    template <class Handle, auto DeleteHandle>
    [[nodiscard]]
    static shared_handle<VkDevice, Handle, DeleteHandle> invoke(std::shared_ptr<VkInstance_T> const &                instance,
                                                                std::shared_ptr<VkDevice_T> const &                  device,
                                                                Handle const                                         handle,
                                                                std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks)
    {
      shared_handle<VkDevice, Handle, DeleteHandle> result;
      result._shared = std::make_shared<unique_handle<VkDevice, Handle, DeleteHandle>>(
        make_unique_handle<Handle, DeleteHandle>(instance, device, handle, allocation_callbacks));
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