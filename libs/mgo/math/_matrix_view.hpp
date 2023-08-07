#pragma once

#include "_matrix_view_data.hpp"
#include "two_dimensional_array.hpp"

#include <type_traits>

namespace mgo
{
template <class matrix_type, _matrix_space space>
struct _matrix_view : _matrix_view_data<matrix_type, space>
{
    using matrix = std::remove_const_t<matrix_type>;
    using _matrix_space::COLUMN;
    using _matrix_space::ROW;
    using _matrix_space::TRANSPOSE;
    using typename _matrix_view_data<matrix_type, space>::size_type;
    using typename _matrix_view_data<matrix_type, space>::difference_type;
    using typename _matrix_view_data<matrix_type, space>::value_type;
    using typename _matrix_view_data<matrix_type, space>::reference;
    using typename _matrix_view_data<matrix_type, space>::const_reference;
    using typename _matrix_view_data<matrix_type, space>::pointer;
    using typename _matrix_view_data<matrix_type, space>::const_pointer;
    using typename _matrix_view_data<matrix_type, space>::iterator;
    using typename _matrix_view_data<matrix_type, space>::const_iterator;
    using typename _matrix_view_data<matrix_type, space>::reverse_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_reverse_iterator;
    using typename _matrix_view_data<matrix_type, space>::transpose_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_transpose_iterator;
    using typename _matrix_view_data<matrix_type, space>::reverse_transpose_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_reverse_transpose_iterator;
    using typename _matrix_view_data<matrix_type, space>::column_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_column_iterator;
    using typename _matrix_view_data<matrix_type, space>::reverse_column_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_reverse_column_iterator;
    using typename _matrix_view_data<matrix_type, space>::row_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_row_iterator;
    using typename _matrix_view_data<matrix_type, space>::reverse_row_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_reverse_row_iterator;
    using typename _matrix_view_data<matrix_type, space>::diagonal_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_diagonal_iterator;
    using typename _matrix_view_data<matrix_type, space>::reverse_diagonal_iterator;
    using typename _matrix_view_data<matrix_type, space>::const_reverse_diagonal_iterator;
    using typename _matrix_view_data<matrix_type, space>::transpose_type;
    using typename _matrix_view_data<matrix_type, space>::transpose_view;
    using typename _matrix_view_data<matrix_type, space>::const_transpose_view;
    using typename _matrix_view_data<matrix_type, space>::row_type;
    using typename _matrix_view_data<matrix_type, space>::row_view;
    using typename _matrix_view_data<matrix_type, space>::const_row_view;
    using typename _matrix_view_data<matrix_type, space>::column_type;
    using typename _matrix_view_data<matrix_type, space>::column_view;
    using typename _matrix_view_data<matrix_type, space>::const_column_view;

    static constexpr bool const is_column         = space == COLUMN;
    static constexpr bool const is_row            = space == ROW;
    static constexpr bool const is_square         = TRANSPOSE and matrix::is_square;
    static constexpr bool const is_not_const      = not std::is_const_v<matrix_type>;
    static constexpr bool const is_floating_point = std::floating_point<value_type>;

    static constexpr size_type column_size() noexcept;
    static constexpr size_type row_size() noexcept;
    static constexpr size_type size() noexcept;
    static constexpr size_type max_size() noexcept;

    constexpr matrix &operator=(value_type value) noexcept requires is_not_const and is_square and (size() == 1);
    constexpr matrix &operator=(std::initializer_list<value_type> values) noexcept requires is_not_const;
    constexpr matrix &operator=(std::initializer_list<column_type> values) noexcept requires is_not_const;
    constexpr matrix &operator=(std::initializer_list<row_type> values) noexcept requires is_not_const;

    constexpr matrix &assign(value_type value) noexcept requires is_not_const and is_square and (size() == 1);
    constexpr matrix &assign(std::initializer_list<value_type> values) noexcept requires is_not_const;
    constexpr matrix &assign(std::initializer_list<column_type> values) noexcept requires is_not_const;
    constexpr matrix &assign(std::initializer_list<row_type> values) noexcept requires is_not_const;
    constexpr matrix &assign(std::forward_iterator auto const &first, std::forward_iterator auto const &last) noexcept
      requires is_not_const;

    constexpr transpose_view       transpose() noexcept requires is_not_const;
    constexpr const_transpose_view transpose() const noexcept;

    constexpr reference       diagonal(size_type k) noexcept requires is_not_const and is_square;
    constexpr const_reference diagonal(size_type k) const noexcept requires is_square;
    constexpr reference       at_diagonal(size_type k) requires is_not_const and is_square;
    constexpr const_reference at_diagonal(size_type k) const requires is_square;

    constexpr auto row(size_type i) noexcept requires is_not_const;
    constexpr auto row(size_type i) const noexcept;
    constexpr auto at_row(size_type i) requires is_not_const;
    constexpr auto at_row(size_type i) const;

    constexpr auto column(size_type j) noexcept requires is_not_const;
    constexpr auto column(size_type j) const noexcept;
    constexpr auto at_column(size_type j) requires is_not_const;
    constexpr auto at_column(size_type j) const;

    constexpr auto at(size_type i) requires is_not_const;
    constexpr auto at(size_type i) const;
    constexpr auto at(size_type i, size_type j) requires is_not_const;
    constexpr auto at(size_type i, size_type j) const;

    constexpr auto operator[](size_type i) noexcept requires is_not_const;
    constexpr auto operator[](size_type i) const noexcept;

    constexpr pointer       data() noexcept requires is_not_const;
    constexpr const_pointer data() const noexcept;

    constexpr iterator       begin() noexcept requires is_not_const;
    constexpr const_iterator begin() const noexcept;
    constexpr iterator       end() noexcept requires is_not_const;
    constexpr const_iterator end() const noexcept;

    constexpr reverse_iterator       rbegin() noexcept requires is_not_const;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator       rend() noexcept requires is_not_const;
    constexpr const_reverse_iterator rend() const noexcept;

    constexpr const_iterator         cbegin() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_iterator         cend() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

    constexpr reference       front() noexcept requires is_not_const;
    constexpr const_reference front() const noexcept;
    constexpr reference       back() noexcept requires is_not_const;
    constexpr const_reference back() const noexcept;

    constexpr matrix &
    swap(two_dimensional_array<value_type, matrix_type::row_size(), matrix_type::column_size()> auto &other) noexcept
      requires is_not_const;
    constexpr matrix &swap(transpose_view other) noexcept requires is_not_const;
    constexpr matrix &swap(column_view other) noexcept requires is_not_const and is_column;
    constexpr matrix &swap(row_view other) noexcept requires is_not_const and is_row;
    constexpr matrix &swap_row(size_type x, size_type y) noexcept requires is_not_const and (column_size() > 1);
    constexpr matrix &swap_column(size_type x, size_type y) noexcept requires is_not_const and (column_size() > 1);

    constexpr matrix &mod(matrix other) noexcept requires is_not_const;
    constexpr matrix &mod(const_transpose_view other) noexcept requires is_not_const;
    constexpr matrix &mod(const_column_view other) noexcept requires is_not_const and is_column;
    constexpr matrix &mod(const_row_view other) noexcept requires is_not_const and is_row;

    constexpr matrix &row_echelon() noexcept requires is_not_const and is_floating_point;
    constexpr matrix &reduced_row_echelon() noexcept requires is_not_const and is_floating_point;
    constexpr matrix &inverse() noexcept requires is_not_const and is_floating_point and is_square;
    constexpr matrix &fill(value_type value) noexcept requires is_not_const;
    constexpr matrix &abs() noexcept requires is_not_const;

    constexpr value_type det() const noexcept requires is_floating_point and is_square;
    constexpr value_type dot(matrix const &other) const noexcept requires is_column;
    constexpr value_type dot(const_column_view other) const noexcept requires is_column;
    constexpr value_type length_squared() const noexcept requires is_column;
    constexpr value_type length() const noexcept requires is_floating_point and is_column;
    constexpr value_type theta() const noexcept requires is_floating_point and is_column and (size() > 1);
    constexpr value_type phi() const noexcept requires is_floating_point and is_column and (size() > 2);
};
}