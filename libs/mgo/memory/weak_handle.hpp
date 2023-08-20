#pragma once

#include "shared_handle.hpp"
#include "unique_handle.hpp"

namespace mgo
{
template <std::size_t ptr_index, class... arg_types>
struct weak_handle
{
    using shared_type  = shared_handle<ptr_index, arg_types...>;
    using deleter_type = handle_deleter<ptr_index, arg_types...>;
    using element_type = typename deleter_type::element_type;
    using pointer      = typename deleter_type::pointer;

    weak_handle(shared_type const &other) noexcept
    : _ptr(other._ptr)
    {
    }

    bool expired() const noexcept
    {
      return _ptr.expired();
    }

    void reset() noexcept
    {
      _ptr.reset();
    }

    operator std::weak_ptr<element_type>() const noexcept
    {
      return _ptr;
    }

    operator shared_type() const noexcept
    {
      return shared_type(_ptr);
    }

    shared_type lock() const noexcept
    {
      return shared_type(_ptr);
    }

    auto operator<=>(weak_handle const &) const noexcept = default;

  private:
    std::weak_ptr<element_type> _ptr;
};
}