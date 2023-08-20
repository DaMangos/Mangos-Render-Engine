#pragma once

#include "handles.hpp"

namespace vulkan
{
template <class dispatchable_handle_type, class handle_type>
struct non_dispatchable
{
    using element_type = typename handle_type::element_type;
    using pointer      = typename handle_type::pointer;

    pointer get() const noexcept
    {
      return _handle.get();
    }

    VkDevice get_device() const noexcept requires std::same_as<typename dispatchable_handle_type::pointer, VkDevice>
    {
      return _dispatcher.get();
    }

    VkInstance get_instance() const noexcept requires std::same_as<typename dispatchable_handle_type::pointer, VkInstance>
    {
      return _dispatcher.get();
    }

    non_dispatchable &operator=(non_dispatchable const &) = delete;
    non_dispatchable &operator=(non_dispatchable &&)      = default;
    non_dispatchable(non_dispatchable const &)            = delete;
    non_dispatchable(non_dispatchable &&)                 = default;
    ~non_dispatchable()                                   = default;

  private:
    friend struct device;
    friend struct instance;

    non_dispatchable(dispatchable_handle_type dispatcher, handle_type handle) noexcept
    : _dispatcher(dispatcher),
      _handle(std::move(handle))
    {
    }

    dispatchable_handle_type _dispatcher;
    handle_type              _handle;
};
}