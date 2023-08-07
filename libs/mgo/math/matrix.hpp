#pragma once

#include "_matrix_data.hpp"
#include "_matrix_view.hpp"
#include "two_dimensional_array.hpp"

#include <mgo/iterator.hpp>
#include <ranges>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
struct matrix : _matrix_data<arithmetic_type, M, N>
{
    using _matrix_space::COLUMN;
    using _matrix_space::ROW;
    using _matrix_space::TRANSPOSE;

    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type      = arithmetic_type;
    using reference       = arithmetic_type &;
    using const_reference = arithmetic_type const &;
    using pointer         = arithmetic_type *;
    using const_pointer   = arithmetic_type const *;

    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using transpose_iterator               = bounded_iterator<pointer, N>;
    using const_transpose_iterator         = bounded_iterator<const_pointer, N>;
    using reverse_transpose_iterator       = std::reverse_iterator<transpose_iterator>;
    using const_reverse_transpose_iterator = std::reverse_iterator<const_transpose_iterator>;

    using diagonal_iterator               = jumping_iterator<pointer, N + 1>;
    using const_diagonal_iterator         = jumping_iterator<pointer, N + 1>;
    using reverse_diagonal_iterator       = std::reverse_iterator<diagonal_iterator>;
    using const_reverse_diagonal_iterator = std::reverse_iterator<const_diagonal_iterator>;

    using column_iterator               = jumping_iterator<pointer, N>;
    using const_column_iterator         = jumping_iterator<const_pointer, N>;
    using reverse_column_iterator       = std::reverse_iterator<column_iterator>;
    using const_reverse_column_iterator = std::reverse_iterator<const_column_iterator>;

    using row_iterator               = pointer;
    using const_row_iterator         = const_pointer;
    using reverse_row_iterator       = std::reverse_iterator<row_iterator>;
    using const_reverse_row_iterator = std::reverse_iterator<const_row_iterator>;

    using matrix_type            = matrix<value_type, M, N>;
    using matrix_reference       = matrix<value_type, M, N> &;
    using const_matrix_reference = matrix<value_type, M, N> const &;

    using transpose_type            = matrix<value_type, N, M>;
    using transpose_reference       = _matrix_view<matrix, TRANSPOSE>;
    using const_transpose_reference = _matrix_view<const matrix, TRANSPOSE>;

    using column_type            = matrix<value_type, M, 1>;
    using column_reference       = _matrix_view<matrix, COLUMN>;
    using const_column_reference = _matrix_view<const matrix, COLUMN>;

    using row_type            = matrix<value_type, 1, M>;
    using row_reference       = _matrix_view<matrix, ROW>;
    using const_row_reference = _matrix_view<const matrix, ROW>;

    static constexpr bool const is_column         = M > 1 and N == 1;
    static constexpr bool const is_row            = M == 1 and N > 1;
    static constexpr bool const is_square         = M == N;
    static constexpr bool const is_floating_point = std::floating_point<value_type>;

    static constexpr size_type column_size() noexcept;
    static constexpr size_type row_size() noexcept;
    static constexpr size_type size() noexcept;
    static constexpr size_type max_size() noexcept;

    constexpr matrix() = default;
    constexpr matrix(value_type value) noexcept requires(size() == 1);
    constexpr matrix(std::initializer_list<value_type> values) noexcept;
    constexpr matrix(std::initializer_list<column_type> values) noexcept;
    constexpr matrix(std::initializer_list<row_type> values) noexcept;
    constexpr matrix(std::forward_iterator auto const &first, std::forward_iterator auto const &last) noexcept;

    constexpr matrix_reference operator=(value_type value) noexcept requires(size() == 1);
    constexpr matrix_reference operator=(std::initializer_list<value_type> values) noexcept;
    constexpr matrix_reference operator=(std::initializer_list<column_type> values) noexcept;
    constexpr matrix_reference operator=(std::initializer_list<row_type> values) noexcept;

    constexpr matrix_reference assign(value_type value) noexcept requires(size() == 1);
    constexpr matrix_reference assign(std::initializer_list<value_type> values) noexcept;
    constexpr matrix_reference assign(std::initializer_list<column_type> values) noexcept;
    constexpr matrix_reference assign(std::initializer_list<row_type> values) noexcept;
    constexpr matrix_reference assign(std::forward_iterator auto const &first, std::forward_iterator auto const &last) noexcept;

    constexpr transpose_reference       transpose() noexcept;
    constexpr const_transpose_reference transpose() const noexcept;

    constexpr row_reference       row(size_type i) noexcept;
    constexpr const_row_reference row(size_type i) const noexcept;
    constexpr row_reference       at_row(size_type i);
    constexpr const_row_reference at_row(size_type i) const;

    constexpr column_reference       column(size_type j) noexcept;
    constexpr const_column_reference column(size_type j) const noexcept;
    constexpr column_reference       at_column(size_type j);
    constexpr const_column_reference at_column(size_type j) const;

    constexpr row_reference       at(size_type i);
    constexpr const_row_reference at(size_type i) const;
    constexpr reference           at(size_type i, size_type j);
    constexpr const_reference     at(size_type i, size_type j) const;

    constexpr row_reference       operator[](size_type i) noexcept;
    constexpr const_row_reference operator[](size_type i) const noexcept;

    constexpr pointer       data() noexcept;
    constexpr const_pointer data() const noexcept;

    constexpr iterator       begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr iterator       end() noexcept;
    constexpr const_iterator end() const noexcept;

    constexpr reverse_iterator       rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator       rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;

    constexpr const_iterator         cbegin() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_iterator         cend() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

    constexpr reference       front() noexcept;
    constexpr const_reference front() const noexcept;
    constexpr reference       back() noexcept;
    constexpr const_reference back() const noexcept;

    constexpr matrix_reference swap(two_dimensional_array<value_type, M, N> auto &other) noexcept;
    constexpr matrix_reference swap_row(size_type x, size_type y) noexcept requires(column_size() > 1);
    constexpr matrix_reference swap_column(size_type x, size_type y) noexcept requires(column_size() > 1);

    constexpr matrix_reference mod(two_dimensional_array<value_type, M, N> auto &other) noexcept;

    constexpr matrix_reference row_echelon() noexcept requires is_floating_point;
    constexpr matrix_reference reduced_row_echelon() noexcept requires is_floating_point;
    constexpr matrix_reference inverse() noexcept requires is_floating_point and is_square;
    constexpr matrix_reference fill(value_type value) noexcept;
    constexpr matrix_reference abs() noexcept;

    constexpr value_type dot(two_dimensional_array<value_type, M, N> auto const &other) const noexcept requires is_column;
    constexpr value_type det() const noexcept requires is_floating_point and is_square;
    constexpr value_type length_squared() const noexcept requires is_column;
    constexpr value_type length() const noexcept requires is_floating_point and is_column;
    constexpr value_type theta() const noexcept requires is_floating_point and is_column and (size() > 1);
    constexpr value_type phi() const noexcept requires is_floating_point and is_column and (size() > 2);
};

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr auto operator<=>(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                           two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator+(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                  two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator-(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                  two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<arithmetic_type, M, P> operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                  two_dimensional_array<arithmetic_type, N, P> auto const &rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator*(arithmetic_type                                          lhs,
                                                  two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                  arithmetic_type                                          rhs) noexcept;

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator/(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                  arithmetic_type                                          rhs) noexcept;
}