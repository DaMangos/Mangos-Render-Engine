#pragma once

#include "shared_handle.hpp"

#include <memory>

namespace mgo
{
template <std::size_t ptr_index, class... arg_types>
struct unique_handle
{
    using shared_type  = shared_handle<ptr_index, arg_types...>;
    using deleter_type = handle_deleter<ptr_index, arg_types...>;
    using element_type = typename deleter_type::element_type;
    using pointer      = typename deleter_type::pointer;

    unique_handle(void (*func)(arg_types...), auto &&...args) noexcept
    : _ptr(std::get<ptr_index>(std::tuple(std::forward<decltype(args)>(args)...)),
           deleter_type(func, std::forward<decltype(args)>(args)...))
    {
    }

    pointer get() const noexcept
    {
      return _ptr.get();
    }

    deleter_type const &get_deleter() const noexcept
    {
      return _ptr.get_deleter();
    }

    operator std::unique_ptr<element_type, deleter_type>() && noexcept
    {
      return std::move(_ptr);
    }

    operator shared_type() && noexcept
    {
      return shared_type(std::move(_ptr));
    }

    auto operator<=>(unique_handle const &) const noexcept = default;

  private:
    std::unique_ptr<element_type, deleter_type> _ptr;
};
}

template <std::size_t ptr_index, class... arg_types>
struct std::hash<mgo::unique_handle<ptr_index, arg_types...>>
{
    std::size_t operator()(mgo::unique_handle<ptr_index, arg_types...> const &handle) const noexcept
    {
      return std::hash<typename mgo::unique_handle<ptr_index, arg_types...>::pointer>()(handle.get());
    }
};