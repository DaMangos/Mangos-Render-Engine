#pragma once

#include <algorithm>
#include <iterator>
#include <mgo/iterator.hpp>
#include <numeric>
#include <ranges>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
requires std::is_arithmetic_v<arithmetic_type> and (M > 0) and (N > 0)
struct matrix_data
{
    [[nodiscard]]
    constexpr arithmetic_type *data() noexcept
    {
      return element;
    }

    [[nodiscard]]
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
    [[nodiscard]]
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    [[nodiscard]]
    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = {}, y = {}, z = {}, w = {};
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 3, 1>
{
    [[nodiscard]]
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    [[nodiscard]]
    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = {}, y = {}, z = {};
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 2, 1>
{
    [[nodiscard]]
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    [[nodiscard]]
    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = {}, y = {};
};

template <class arithmetic_type>
requires std::is_arithmetic_v<arithmetic_type>
struct matrix_data<arithmetic_type, 1, 1>
{
    [[nodiscard]]
    constexpr arithmetic_type *data() noexcept
    {
      return &x;
    }

    [[nodiscard]]
    constexpr arithmetic_type const *data() const noexcept
    {
      return &x;
    }

    arithmetic_type x = {};
};

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
    using reverse_iterator       = std::reverse_iterator<pointer>;
    using const_reverse_iterator = std::reverse_iterator<const_pointer>;

    using transpose_iterator               = bounded_iterator<pointer, N>;
    using const_transpose_iterator         = bounded_iterator<const_pointer, N>;
    using reverse_transpose_iterator       = std::reverse_iterator<transpose_iterator>;
    using const_reverse_transpose_iterator = std::reverse_iterator<const_transpose_iterator>;

    using diagonal_iterator               = jumping_iterator<pointer, N + 1>;
    using const_diagonal_iterator         = jumping_iterator<const_pointer, N + 1>;
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

    using column_type    = matrix<value_type, M, 1>;
    using row_type       = matrix<value_type, 1, M>;
    using transpose_type = matrix<value_type, N, M>;

    struct row_view : std::ranges::view_interface<row_view>
    {
        [[nodiscard]]
        matrix::column_iterator begin() noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::column_iterator end() noexcept
        {
          return std::next(first_, column_size());
        }

        explicit constexpr operator row_type() const & noexcept
        {
          return row_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::column_iterator first_;
    };

    struct const_row_view : std::ranges::view_interface<row_view>
    {
        [[nodiscard]]
        matrix::const_column_iterator begin() const noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::const_column_iterator end() const noexcept
        {
          return std::next(first_, column_size());
        }

        explicit constexpr operator row_type() const & noexcept
        {
          return row_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::const_column_iterator first_;
    };

    struct column_view : std::ranges::view_interface<column_view>
    {
        [[nodiscard]]
        matrix::row_iterator begin() noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::row_iterator end() noexcept
        {
          return std::next(first_, row_size());
        }

        explicit constexpr operator column_type() const & noexcept
        {
          return column_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::row_iterator first_;
    };

    struct const_column_view : std::ranges::view_interface<column_view>
    {
        [[nodiscard]]
        matrix::const_row_iterator begin() const noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::const_row_iterator end() const noexcept
        {
          return std::next(first_, row_size());
        }

        explicit constexpr operator column_type() const & noexcept
        {
          return column_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::const_row_iterator first_;
    };

    struct transpose_view : std::ranges::view_interface<transpose_view>
    {
        [[nodiscard]]
        matrix::transpose_iterator begin() noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::transpose_iterator end() noexcept
        {
          return std::next(first_, size());
        }

        explicit constexpr operator transpose_type() const & noexcept
        {
          return transpose_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::transpose_iterator first_;
    };

    struct const_transpose_view : std::ranges::view_interface<transpose_view>
    {
        [[nodiscard]]
        matrix::const_transpose_iterator begin() const noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::const_transpose_iterator end() const noexcept
        {
          return std::next(first_, size());
        }

        explicit constexpr operator transpose_type() const & noexcept
        {
          return transpose_type(begin(), end());
        }

      private:
        friend struct matrix;
        matrix::const_transpose_iterator first_;
    };

    struct diagonal_view : std::ranges::view_interface<diagonal_view>
    {
        [[nodiscard]]
        matrix::diagonal_iterator begin() const noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::diagonal_iterator end() const noexcept
        {
          return std::next(first_, column_size());
        }

      private:
        friend struct matrix;
        matrix::diagonal_iterator first_;
    };

    struct const_diagonal_view : std::ranges::view_interface<diagonal_view>
    {
        [[nodiscard]]
        matrix::const_diagonal_iterator begin() const noexcept
        {
          return first_;
        }

        [[nodiscard]]
        matrix::const_diagonal_iterator end() const noexcept
        {
          return std::next(first_, column_size());
        }

      private:
        friend struct matrix;
        matrix::const_diagonal_iterator first_;
    };

    [[nodiscard]]
    static constexpr size_type column_size() noexcept
    {
      return M;
    }

    [[nodiscard]]
    static constexpr size_type row_size() noexcept
    {
      return N;
    }

    [[nodiscard]]
    static constexpr size_type size() noexcept
    {
      return column_size() * row_size();
    }

    [[nodiscard]]
    static constexpr size_type max_size() noexcept
    {
      return size();
    }

    [[nodiscard]]
    static constexpr bool empty() noexcept
    {
      return false;
    }

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
      assign(value);
      return *this;
    }

    constexpr matrix &operator=(std::initializer_list<value_type> values) noexcept
    {
      assign(values);
      return *this;
    }

    constexpr matrix &operator=(std::initializer_list<column_type> values) noexcept
    {
      assign(values);
      return *this;
    }

    constexpr matrix &operator=(std::initializer_list<row_type> values) noexcept
    {
      assign(values);
      return *this;
    }

    constexpr void assign(value_type value) noexcept requires(size() == 1)
    {
      front() = value;
    }

    constexpr void assign(std::initializer_list<value_type> values) noexcept
    {
      static_assert(values.size() <= size(), "too many values in initializer list");
      assign(values.begin(), values.end());
    }

    constexpr void assign(std::initializer_list<column_type> values) noexcept
    {
      static_assert(values.size() <= row_size(), "too many values in initializer list");
      assign(transpose_iterator(values.begin(), begin(), std::prev(end())),
             transpose_iterator(values.end(), begin(), std::prev(end())));
    }

    constexpr void assign(std::initializer_list<row_type> values) noexcept
    {
      static_assert(values.size() <= column_size(), "too many values in initializer list");
      assign(iterator(values.begin()), iterator(values.end()));
    }

    constexpr void assign(std::forward_iterator auto const &first, std::forward_iterator auto const &last) noexcept
      requires std::same_as<decltype(*first), value_type> and std::same_as<decltype(*last), value_type>
    {
      std::copy_n(first, std::min(static_cast<size_type>(std::distance(first, last)), size()), begin());
    }

    [[nodiscard]]
    constexpr row_view row(size_type i) noexcept
    {
      return row_view{std::next(begin(), i * column_size())};
    }

    [[nodiscard]]
    constexpr const_row_view row(size_type i) const noexcept
    {
      return const_row_view{std::next(begin(), i * column_size())};
    }

    [[nodiscard]]
    constexpr row_view at_row(size_type i)
    {
      if(i >= row_size())
        throw std::out_of_range("row index out of range");
      return row(i);
    }

    [[nodiscard]]
    constexpr const_row_view at_row(size_type i) const
    {
      if(i >= row_size())
        throw std::out_of_range("row index out of range");
      return row(i);
    }

    [[nodiscard]]
    constexpr column_view column(size_type j) noexcept
    {
      return column_view{std::next(begin(), j)};
    }

    [[nodiscard]]
    constexpr const_column_view column(size_type j) const noexcept
    {
      return const_column_view{std::next(begin(), j)};
    }

    [[nodiscard]]
    constexpr column_view at_column(size_type j)
    {
      if(j >= column_size())
        throw std::out_of_range("column index out of range");
      return column(j);
    }

    [[nodiscard]]
    constexpr const_column_view at_column(size_type j) const
    {
      if(j >= column_size())
        throw std::out_of_range("column index out of range");
      return column(j);
    }

    [[nodiscard]]
    constexpr row_view at(size_type i)
    {
      if(i >= row_size())
        throw std::out_of_range("row index out of range");
      return row(i);
    }

    [[nodiscard]]
    constexpr const_row_view at(size_type i) const
    {
      if(i >= row_size())
        throw std::out_of_range("row index out of range");
      return row(i);
    }

    [[nodiscard]]
    constexpr row_view
    operator[](size_type i) noexcept
    {
      return row(i);
    }

    [[nodiscard]]
    constexpr const_row_view
    operator[](size_type i) const noexcept
    {
      return row(i);
    }

    [[nodiscard]]
    constexpr iterator begin() noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data();
    }

    [[nodiscard]]
    constexpr const_iterator begin() const noexcept
    {
      return matrix_data<arithmetic_type, M, N>::data();
    }

    [[nodiscard]]
    constexpr iterator end() noexcept
    {
      return std::next(begin(), size());
    }

    [[nodiscard]]
    constexpr const_iterator end() const noexcept
    {
      return std::next(begin(), size());
    }

    [[nodiscard]]
    constexpr reverse_iterator rbegin() noexcept
    {
      return std::make_reverse_iterator(end());
    }

    [[nodiscard]]
    constexpr const_reverse_iterator rbegin() const noexcept
    {
      return std::make_reverse_iterator(end());
    }

    [[nodiscard]]
    constexpr reverse_iterator rend() noexcept
    {
      return std::make_reverse_iterator(begin());
    }

    [[nodiscard]]
    constexpr const_reverse_iterator rend() const noexcept
    {
      return std::make_reverse_iterator(begin());
    }

    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept
    {
      return begin();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator crbegin() const noexcept
    {
      return rbegin();
    }

    [[nodiscard]]
    constexpr const_iterator cend() const noexcept
    {
      return end();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator crend() const noexcept
    {
      return rend();
    }

    [[nodiscard]]
    constexpr reference front() noexcept
    {
      return *begin();
    }

    [[nodiscard]]
    constexpr const_reference front() const noexcept
    {
      return *begin();
    }

    [[nodiscard]]
    constexpr reference back() noexcept
    {
      return *std::prev(end());
    }

    [[nodiscard]]
    constexpr const_reference back() const noexcept
    {
      return *std::prev(end());
    }

    [[nodiscard]]
    constexpr transpose_iterator transpose_begin() noexcept
    {
      return transpose_iterator(begin(), begin(), std::prev(end()));
    }

    [[nodiscard]]
    constexpr const_transpose_iterator transpose_begin() const noexcept
    {
      return const_transpose_iterator(begin(), begin(), std::prev(end()));
    }

    [[nodiscard]]
    constexpr transpose_iterator transpose_end() noexcept
    {
      return transpose_iterator(end(), begin(), std::prev(end()));
    }

    [[nodiscard]]
    constexpr const_transpose_iterator transpose_end() const noexcept
    {
      return const_transpose_iterator(end(), begin(), std::prev(end()));
    }

    [[nodiscard]]

    constexpr reverse_transpose_iterator transpose_rbegin() noexcept
    {
      return std::make_reverse_iterator(transpose_end());
    }

    [[nodiscard]]
    constexpr const_reverse_transpose_iterator transpose_rbegin() const noexcept
    {
      return std::make_reverse_iterator(transpose_end());
    }

    [[nodiscard]]
    constexpr reverse_transpose_iterator transpose_rend() noexcept
    {
      return std::make_reverse_iterator(transpose_begin());
    }

    [[nodiscard]]
    constexpr const_reverse_transpose_iterator transpose_rend() const noexcept
    {
      return std::make_reverse_iterator(transpose_begin());
    }

    [[nodiscard]]
    constexpr const_transpose_iterator transpose_cbegin() const noexcept
    {
      return transpose_begin();
    }

    [[nodiscard]]
    constexpr const_reverse_transpose_iterator transpose_crbegin() const noexcept
    {
      return transpose_rbegin();
    }

    [[nodiscard]]
    constexpr const_transpose_iterator transpose_cend() const noexcept
    {
      return transpose_end();
    }

    constexpr void swap_row(size_type x, size_type y) requires(column_size() > 1)
    {
      std::ranges::swap_ranges(at_row(x).begin(), at_row(x).end(), at_row(y).begin());
    }

    constexpr void swap_column(size_type x, size_type y) requires(column_size() > 1)
    {
      std::ranges::swap_ranges(at_column(x).begin(), at_column(x).end(), at_column(y).begin());
    }

    constexpr void mod(matrix<value_type, M, N> const &other) noexcept
    {
        std::transform(begin(), end(), other.begin(), begin(), std::fmod);
    }

    constexpr void row_echelon() noexcept
    {
      // using hermite form
    }

    constexpr void reduced_row_echelon() noexcept requires std::floating_point<arithmetic_type>
    {
    }

    constexpr void inverse() noexcept requires std::floating_point<arithmetic_type> and (column_size() == row_size())
    {
    }

    constexpr void transpose() noexcept
    {
      std::ranges::swap_ranges(begin(), end(), transpose_begin());
    }

    constexpr void fill(value_type value) noexcept
    {
      std::fill(begin(), end(), value);
    }

    constexpr void abs() noexcept
    {
      std::transform(begin(), end(), begin(), std::abs);
    }

    [[nodiscard]]
    constexpr value_type dot(matrix const &other) const noexcept requires(row_size() == 1)
    {
      return std::inner_product(begin(), end(), other.begin(), value_type{});
    }

    [[nodiscard]]
    constexpr matrix cross(matrix other) const noexcept requires(row_size() == 1)
    {
      // needed implementation
    }

    [[nodiscard]]
    constexpr value_type det() const noexcept requires(column_size() == row_size())
    {
      // using hermite form
    }

    [[nodiscard]]
    constexpr value_type length_squared() const noexcept requires(row_size() == 1)
    {
      return dot(*this);
    }

    [[nodiscard]]
    constexpr value_type length() const noexcept requires std::floating_point<arithmetic_type> and (row_size() == 1)
    {
      return std::sqrt(length_squared());
    }

    [[nodiscard]]
    constexpr value_type theta() const noexcept
      requires std::floating_point<arithmetic_type> and (row_size() == 1) and (column_size() >= 2)
    {
    }

    [[nodiscard]]
    constexpr value_type phi() const noexcept
      requires std::floating_point<arithmetic_type> and (row_size() == 1) and (column_size() >= 3)
    {
    }

    constexpr auto operator<=>(matrix const &) const noexcept = default;
};

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator+(matrix<arithmetic_type, M, N> const &lhs,
                                                  matrix<arithmetic_type, M, N>        rhs) noexcept
{
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), std::plus{});
  return rhs;
}

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator-(matrix<arithmetic_type, M, N> const &lhs,
                                                  matrix<arithmetic_type, M, N> const &rhs) noexcept
{
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), std::minus{});
  return rhs;
}

template <class arithmetic_type, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<arithmetic_type, M, P> operator*(matrix<arithmetic_type, M, N> const &lhs,
                                                  matrix<arithmetic_type, N, P> const &rhs) noexcept
{
  matrix<arithmetic_type, M, P> result;
  for(std::size_t i = 0; i < M; ++i)
    for(std::size_t j = 0; j < P; ++j)
      for(std::size_t k = 0; k < N; ++k)
        result[i][j] += lhs[i][k] * rhs[k][j];
  return result;
}

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator*(arithmetic_type lhs, matrix<arithmetic_type, M, N> const &rhs) noexcept
{
  std::transform(rhs.begin(), rhs.end(), rhs.begin(), [lhs](arithmetic_type value) { return lhs * value; });
  return rhs;
}

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator*(matrix<arithmetic_type, M, N> lhs, arithmetic_type rhs) noexcept
{
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [rhs](arithmetic_type value) { return value * rhs; });
  return lhs;
}

template <class arithmetic_type, std::size_t M, std::size_t N>
constexpr matrix<arithmetic_type, M, N> operator/(matrix<arithmetic_type, M, N> lhs, arithmetic_type rhs) noexcept
{
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [rhs](arithmetic_type value) { return value / rhs; });
  return lhs;
}
}