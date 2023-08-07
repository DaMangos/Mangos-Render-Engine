#pragma once

#include <ranges>

namespace mgo
{
template <class array_type, class arithmetic_type, std::size_t M, std::size_t N>
concept two_dimensional_array = std::ranges::contiguous_range<array_type> and array_type::column_size() and
                                array_type::row_size() == N and std::same_as<typename array_type::value_type, arithmetic_type>;
}