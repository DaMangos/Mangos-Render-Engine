#pragma once

#include <vulkan/handles/range_element_handle.hpp>

namespace vulkan::internal
{
struct make_range_element_handle_t
{
    template <class Handle>
    [[nodiscard]]
    static range_element_handle<Handle> invoke(std::shared_ptr<Handle[]> const & handles,
                                               std::uint32_t const               size,
                                               std::uint32_t const               index) noexcept
    {
      range_element_handle<Handle> result;
      result._handles = handles;
      result._size    = size;
      result._index   = index;
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