#pragma once

#include <vulkan/handles/command_buffer.hpp>
#include <vulkan/handles/range_element_handle.hpp>

#include <concepts>

namespace vulkan::internal
{
struct make_range_element_handle_t
{
    template <class Handle>
    [[nodiscard]]
    static range_element_handle<Handle> invoke(std::shared_ptr<Handle[]> const & shared_handles,
                                               std::uint32_t const               array_size,
                                               std::uint32_t const               array_index) noexcept
    {
      range_element_handle<Handle> result;
      result._shared_handles = shared_handles;
      result._array_size     = array_size;
      result._array_index    = array_index;
      return result;
    }
};

template <class Handle>
[[nodiscard]]
decltype(auto) make_range_element_handle(auto &&... args)
{
  return make_range_element_handle_t::invoke<Handle>(std::forward<decltype(args)>(args)...);
}
}