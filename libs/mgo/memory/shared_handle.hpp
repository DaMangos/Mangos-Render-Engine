#pragma once

#include "handle_deleter.hpp"

#include <memory>

namespace mgo
{
template <std::size_t ptr_index, class... arg_types>
struct weak_handle;

template <std::size_t ptr_index, class... arg_types>
struct shared_handle
{
    using weak_type    = weak_handle<ptr_index, arg_types...>;
    using deleter_type = handle_deleter<ptr_index, arg_types...>;
    using element_type = typename deleter_type::element_type;
    using pointer      = typename deleter_type::pointer;

    shared_handle(void (*func)(arg_types...), auto &&...args) noexcept
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
      return *std::get_deleter<deleter_type>(_ptr);
    }

    operator std::shared_ptr<element_type>() const noexcept
    {
      return _ptr;
    }

    auto operator<=>(shared_handle const &) const noexcept = default;

  private:
    template <std::size_t, class...>
    friend struct unique_handle;
    template <std::size_t, class...>
    friend struct weak_handle;

    shared_handle(std::unique_ptr<element_type> &&_ptr) noexcept
    : _ptr(std::move(_ptr))
    {
    }

    shared_handle(std::weak_ptr<element_type> const &_ptr) noexcept
    : _ptr(_ptr)
    {
    }

    std::shared_ptr<element_type> _ptr;
};
}

template <std::size_t ptr_index, class... arg_types>
struct std::hash<mgo::shared_handle<ptr_index, arg_types...>>
{
    std::size_t operator()(mgo::shared_handle<ptr_index, arg_types...> const &handle) const noexcept
    {
      return std::hash<typename mgo::shared_handle<ptr_index, arg_types...>::pointer>()(handle.get());
    }
};