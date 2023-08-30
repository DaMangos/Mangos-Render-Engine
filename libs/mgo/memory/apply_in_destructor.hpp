#pragma once

#include <memory>
#include <tuple>

namespace mgo
{
template <auto func_pointer, class... arg_types>
requires std::invocable<decltype(func_pointer), std::add_rvalue_reference_t<arg_types>...>
struct apply_in_destructor
{
    template <std::size_t i>
    using arg_type = std::tuple_element_t<i, std::tuple<arg_types...>>;

    constexpr apply_in_destructor(auto &&...args) noexcept
    : _args(std::forward<decltype(args)>(args)...)
    {
    }

    constexpr ~apply_in_destructor()
    {
      std::apply(func_pointer, std::move(_args));
    }

    template <std::size_t i>
    constexpr arg_type<i> &get() noexcept
    {
      return std::get<i>(_args);
    }

    template <std::size_t i>
    constexpr arg_type<i> const &get() const noexcept
    {
      return std::get<i>(_args);
    }

    constexpr void swap(apply_in_destructor &other) noexcept
    {
      std::swap(_args, other._args);
    }

    constexpr apply_in_destructor(apply_in_destructor &&) noexcept                         = delete;
    constexpr apply_in_destructor(apply_in_destructor const &) noexcept                    = delete;
    constexpr apply_in_destructor &operator=(apply_in_destructor &&) noexcept              = delete;
    constexpr apply_in_destructor &operator=(apply_in_destructor const &) noexcept         = delete;
    constexpr auto                 operator<=>(apply_in_destructor const &) const noexcept = default;

  private:
    [[no_unique_address]] std::tuple<arg_types...> _args;
};
}

namespace std
{
template <auto func_pointer, class... arg_types>
constexpr void swap(mgo::apply_in_destructor<func_pointer, arg_types...> &lhs,
                    mgo::apply_in_destructor<func_pointer, arg_types...> &rhs) noexcept
{
  lhs.swap(rhs);
}
}