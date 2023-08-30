#pragma once

#include "matrix_data.hpp"
#include "matrix_view.hpp"
#include "two_dimensional_array.hpp"

#include <ranges>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
struct matrix : matrix_data<arithmetic_type, M, N>
{
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

    using column_type       = matrix<value_type, M, 1>;
    using column_view       = matrix_view<matrix, true>;
    using const_column_view = matrix_view<const matrix, true>;

    using row_type       = matrix<value_type, 1, M>;
    using row_view       = matrix_view<matrix, false>;
    using const_row_view = matrix_view<const matrix, false>;

    static constexpr size_type column_size() noexcept;
    static constexpr size_type row_size() noexcept;
    static constexpr size_type size() noexcept;
    static constexpr size_type max_size() noexcept;

    constexpr matrix() = default;

    constexpr matrix(value_type value) noexcept requires(size() == 1)
    {
      assign(value);
    }

    constexpr matrix(std::initializer_list<value_type> values) noexcept
    {
      assign(values);
    }

    constexpr matrix(std::initializer_list<column_type> values) noexcept
    {
      assign(values);
    }

    constexpr matrix(std::initializer_list<row_type> values) noexcept
    {
      assign(values);
    }

    constexpr matrix(std::input_iterator auto const &first, std::input_iterator auto const &last) noexcept
    {
      assign(first, last);
    }

    constexpr matrix &operator=(value_type value) noexcept requires(size() == 1)
    {
      return assign(value);
    }

    constexpr matrix &operator=(std::initializer_list<value_type> values) noexcept
    {
      return assign(values);
    }

    constexpr matrix &operator=(std::initializer_list<column_type> values) noexcept
    {
      return assign(values);
    }

    constexpr matrix &operator=(std::initializer_list<row_type> values) noexcept
    {
      return assign(values);
    }

    constexpr matrix &assign(value_type value) noexcept requires(size() == 1)
    {
      return assign({value});
    }

    constexpr matrix &assign(std::initializer_list<value_type> values) noexcept
    {
      return assign(values.begin(), values.end());
    }

    constexpr matrix &assign(std::initializer_list<column_type> values) noexcept
    {
      return assign(values.begin(), values.end());
    }

    constexpr matrix &assign(std::initializer_list<row_type> values) noexcept
    {
      return assign(values.begin(), values.end());
    }

    constexpr matrix &assign(std::forward_iterator auto const &first, std::forward_iterator auto const &last) noexcept
    {
      std::copy_n(first, std::min(static_cast<size_type>(std::distance(first, last)), size()), begin());
    }

    // constexpr transpose_view       transpose() noexcept;
    // constexpr const_transpose_view transpose() const noexcept;

    constexpr row_view row(size_type i) noexcept
    {
      return row_view(begin() + i * row_size());
    }

    constexpr const_row_view row(size_type i) const noexcept
    {
      return const_row_view(begin() + i * row_size());
    }

    constexpr row_view at_row(size_type i)
    {
      if(i >= row_size())
        throw std::out_of_range("matrix::at_row");
      return row(i);
    }

    constexpr const_row_view at_row(size_type i) const
    {
      if(i >= row_size())
        throw std::out_of_range("matrix::at_row");
      return row(i);
    }

    constexpr column_view column(size_type j) noexcept
    {
      return column_view(begin() + j);
    }

    constexpr const_column_view column(size_type j) const noexcept
    {
      return const_column_view(begin() + j);
    }

    constexpr column_view at_column(size_type j)
    {
      if(j >= column_size())
        throw std::out_of_range("matrix::at_column");
      return column(j);
    }

    constexpr const_column_view at_column(size_type j) const
    {
      if(j >= column_size())
        throw std::out_of_range("matrix::at_column");
      return column(j);
    }

    constexpr row_view at(size_type i)
    {
      return at_row(i);
    }

    constexpr const_row_view at(size_type i) const
    {
      return at_row(i);
    }

    constexpr row_view operator[](size_type i) noexcept
    {
      return row(i);
    }

    constexpr const_row_view operator[](size_type i) const noexcept
    {
      return row(i);
    }

    constexpr iterator begin() noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data();
    }

    constexpr const_iterator begin() const noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data();
    }

    constexpr iterator end() noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data() + size();
    }

    constexpr const_iterator end() const noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data() + size();
    }

    constexpr reverse_iterator rbegin() noexcept
    {
      return reverse_iterator(end());
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
      return const_reverse_iterator(end());
    }

    constexpr reverse_iterator rend() noexcept
    {
      return reverse_iterator(begin());
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
      return const_reverse_iterator(begin());
    }

    constexpr const_iterator cbegin() const noexcept
    {
      return begin();
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
      return rbegin();
    }

    constexpr const_iterator cend() const noexcept
    {
      return end();
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
      return rend();
    }

    constexpr reference front() noexcept
    {
      return begin()[0];
    }

    constexpr const_reference front() const noexcept
    {
      return begin()[0];
    }

    constexpr reference back() noexcept
    {
      return begin()[size() - 1];
    }

    constexpr const_reference back() const noexcept
    {
      return begin()[size() - 1];
    }

    constexpr matrix &swap(two_dimensional_array<value_type, M, N> auto &other) noexcept
    {
      std::swap(*this, other);
    }

    constexpr matrix &swap_row(size_type x, size_type y) noexcept requires(column_size() > 1)
    {
    }

    constexpr matrix &swap_column(size_type x, size_type y) noexcept requires(column_size() > 1);

    constexpr matrix &mod(two_dimensional_array<value_type, M, N> auto &other) noexcept;

    constexpr matrix &row_echelon() noexcept requires std::floating_point<arithmetic_type>;
    constexpr matrix &reduced_row_echelon() noexcept requires std::floating_point<arithmetic_type>;
    constexpr matrix &inverse() noexcept requires std::floating_point<arithmetic_type> and (column_size() == row_size());
    constexpr matrix &fill(value_type value) noexcept;
    constexpr matrix &abs() noexcept;

    constexpr value_type dot(two_dimensional_array<value_type, M, N> auto const &other) const noexcept
      requires std::same_as<matrix, column_type>;
    constexpr value_type det() const noexcept requires std::floating_point<arithmetic_type> and (column_size() == row_size());
    constexpr value_type length_squared() const noexcept requires std::same_as<matrix, column_type>;
    constexpr value_type length() const noexcept
      requires std::floating_point<arithmetic_type> and std::same_as<matrix, column_type>;
    constexpr value_type theta() const noexcept
      requires std::floating_point<arithmetic_type> and std::same_as<matrix, column_type> and (size() > 1);
    constexpr value_type phi() const noexcept
      requires std::floating_point<arithmetic_type> and std::same_as<matrix, column_type> and (size() > 2);

  private:
    friend constexpr auto operator<=>(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    friend constexpr matrix operator+(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    friend constexpr matrix operator-(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    template <std::size_t P>
    friend constexpr matrix<arithmetic_type, M, P>
    operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
              two_dimensional_array<arithmetic_type, N, P> auto const &rhs) noexcept;

    friend constexpr matrix operator*(arithmetic_type                                          lhs,
                                      two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    friend constexpr matrix operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      arithmetic_type                                          rhs) noexcept;

    friend constexpr matrix operator/(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      arithmetic_type                                          rhs) noexcept;

    constexpr reference get(size_type i, size_type j);

    constexpr const_reference get(size_type i, size_type j) const;
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