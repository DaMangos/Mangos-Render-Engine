#pragma once
#include <concepts>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
requires(M > 0) and (N > 0) and (std::integral<arithmetic_type> or std::floating_point<arithmetic_type>)
struct _matrix_data
{
    arithmetic_type element[M * N] = {};
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
struct _matrix_data<arithmetic_type, 4, 1>
{
    arithmetic_type x = 0, y = 0, z = 0, w = 0;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
struct _matrix_data<arithmetic_type, 3, 1>
{
    arithmetic_type x = 0, y = 0, z = 0;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
struct _matrix_data<arithmetic_type, 2, 1>
{
    arithmetic_type x = 0, y = 0;
};

template <class arithmetic_type>
requires std::integral<arithmetic_type> or std::floating_point<arithmetic_type>
struct _matrix_data<arithmetic_type, 1, 1>
{
    arithmetic_type x = 0;
};
}