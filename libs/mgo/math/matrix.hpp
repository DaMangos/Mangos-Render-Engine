#pragma once

#include <algorithm>
#include <cstddef>
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
  private:
    template <class underlying_iterator, class convertible_type, std::size_t count>
    struct view final
    {
        using iterator = underlying_iterator;

        [[nodiscard]]
        constexpr iterator begin() const noexcept
        {
          return _first;
        }

        [[nodiscard]]
        constexpr iterator end() const noexcept
        {
          return std::next(_first, size);
        }

        [[nodiscard]]
        static constexpr std::size_t size() noexcept
        {
          return count;
        }

        constexpr decltype(auto) operator[](std::size_t j) const noexcept
        {
          return begin()[j];
        }

        constexpr explicit operator convertible_type() const & noexcept
        {
          return convertible_type(begin(), end());
        }

      private:
        constexpr view(auto &&...args) noexcept
        : _first(std::forward<decltype(args)>(args)...)
        {
        }

        friend struct matrix;
        iterator _first;
    };

  public:
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

    using column_type       = matrix<value_type, M, 1>;
    using column_view       = view<jumping_iterator<pointer, N>, column_type, M>;
    using const_column_view = view<jumping_iterator<const_pointer, N>, column_type, M>;

    using row_type       = matrix<value_type, 1, N>;
    using row_view       = view<pointer, row_type, N>;
    using const_row_view = view<const_pointer, row_type, N>;

    using transpose_type       = matrix<value_type, N, M>;
    using transpose_view       = view<bounded_iterator<pointer, N>, transpose_type, M * N>;
    using const_transpose_view = view<bounded_iterator<const_pointer, N>, transpose_type, M * N>;

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

    [[nodiscard]]
    constexpr row_view view_row(size_type i) noexcept
    {
      return row_view(std::next(begin(), i * row_size()));
    }

    [[nodiscard]]
    constexpr const_row_view view_row(size_type i) const noexcept
    {
      return const_row_view(std::next(begin(), i * row_size()));
    }

    [[nodiscard]]
    constexpr column_view view_column(size_type j) noexcept
    {
      return column_view(std::next(begin(), j));
    }

    [[nodiscard]]
    constexpr const_column_view view_column(size_type j) const noexcept
    {
      return const_column_view(std::next(begin(), j));
    }

    [[nodiscard]]
    constexpr transpose_view view_transpose() noexcept
    {
      return transpose_view(begin());
    }

    [[nodiscard]]
    constexpr const_transpose_view view_transpose() const noexcept
    {
      return const_transpose_view(begin(), begin(), std::prev(end()));
    }

    [[nodiscard]]
    constexpr reference at(size_type i, size_type j)
    {
      if(i >= column_size() or j >= row_size())
        throw std::out_of_range("mgo::matrix::at");
      return begin()[i * row_size() + j];
    }

    [[nodiscard]]
    constexpr const_reference at(size_type i, size_type j) const
    {
      if(i >= column_size() or j >= row_size())
        throw std::out_of_range("mgo::matrix::at");
      return begin()[i * row_size() + j];
    }

    constexpr pointer operator[](difference_type i) noexcept
    {
      return std::next(begin(), i * row_size());
    }

    constexpr const_pointer operator[](difference_type i) const noexcept
    {
      return std::next(begin(), i * row_size());
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

    constexpr void swap_rows(size_type x, size_type y) requires(column_size() > 1)
    {
      if(x != y)
        std::ranges::swap_ranges(view_row(x).begin(), view_row(x).end(), view_row(y).begin());
    }

    constexpr void swap_columns(size_type x, size_type y) requires(column_size() > 1)
    {
      if(x != y)
        std::ranges::swap_ranges(view_column(x).begin(), view_column(x).end(), view_column(y).begin());
    }

    constexpr void mod(matrix<value_type, M, N> const &other) noexcept
    {
      std::transform(begin(), end(), other.begin(), begin(), std::fmod);
    }

    constexpr void row_echelon() noexcept
    {
      for(size_type k = 0; k < column_size() and k < row_size(); ++k)
      {
        if((*this)[k][k] == 0)
          for(size_type i = k + 1; i < column_size(); ++i)
            if((*this)[i][k] != 0)
            {
              swap_row(k, i);
              break;
            }
        if((*this)[k][k] != 0)
          for(size_type i = k; i < column_size(); ++i)
          {
            (*this)[i][k] = 0;
            for(size_type j = k + 1; j < row_size(); ++j)
              (*this)[i][j] = (*this)[i][j] * (*this)[k][k] - (*this)[k][j] * (*this)[i][k];
          }
      }
    }

    constexpr void reduced_row_echelon() noexcept requires std::floating_point<arithmetic_type>
    {
    }

    constexpr void inverse() noexcept requires std::floating_point<arithmetic_type> and (column_size() == row_size())
    {
      // TODO: implement
    }

    constexpr void transpose() noexcept
    {
      // TODO: implement
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
      return std::inner_product(begin(), end(), other.begin(), 0);
    }

    [[nodiscard]]
    constexpr matrix cross(matrix other) const noexcept requires(row_size() == 1)
    {
      // TODO: implement
    }

    [[nodiscard]]
    constexpr value_type det() const noexcept requires(column_size() == row_size())
    {
      // TODO: implement
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
      // TODO: implement
    }

    [[nodiscard]]
    constexpr value_type phi() const noexcept
      requires std::floating_point<arithmetic_type> and (row_size() == 1) and (column_size() >= 3)
    {
      // TODO: implement
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