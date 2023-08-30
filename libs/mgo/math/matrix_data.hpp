#pragma once

#include <concepts>
#include <type_traits>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
requires std::is_arithmetic_v<arithmetic_type> and (M > 0) and (N > 0)
struct matrix_data
{
    constexpr arithmetic_type *data() noexcept
    {
      return element;
    }

    constexpr arithmetic_type const *data() const noexcept
    {
      return element;
    }

    arithmetic_type element[M * N] = {};
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 4, 1>
{
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = 0, y = 0, z = 0, w = 0;
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 3, 1>
{
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = 0, y = 0, z = 0;
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 2, 1>
{
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = 0, y = 0;
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 1, 1>
{
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = 0;
};
}