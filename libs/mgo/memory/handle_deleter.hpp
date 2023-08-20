#pragma once

#include <concepts>
#include <memory>
#include <tuple>

namespace mgo
{
template <std::size_t ptr_index, class... arg_types>
struct handle_deleter
{
    template <std::size_t arg_index>
    using arg_type     = std::tuple_element_t<arg_index, std::tuple<arg_types...>>;
    using pointer      = arg_type<ptr_index>;
    using element_type = typename std::pointer_traits<pointer>::element_type;

    constexpr void operator()(pointer ptr) noexcept requires std::move_constructible<std::tuple<arg_types...>>
    {
      std::get<ptr_index>(_args) = ptr;
      std::apply(_func, std::move(_args));
    }

    constexpr void operator()(pointer ptr) noexcept requires std::copy_constructible<std::tuple<arg_types...>>
    {
      std::get<ptr_index>(_args) = ptr;
      std::apply(_func, _args);
    }

    template <std::size_t arg_index>
    constexpr arg_type<arg_index> const &get_arg() const noexcept
    {
      static_assert(arg_index != ptr_index, "cannot access pointer argument");
      return std::get<arg_index>(_args);
    }

    constexpr auto operator<=>(handle_deleter const &) const noexcept = default;

  private:
    template <std::size_t, class...>
    friend struct unique_handle;
    template <std::size_t, class...>
    friend struct shared_handle;

    constexpr handle_deleter(void (*func)(arg_types...), arg_types... args) noexcept
    : _func(func),
      _args(std::forward<arg_types>(args)...)
    {
    }

    void (*_func)(arg_types...);
    std::tuple<arg_types...> _args;
};
}