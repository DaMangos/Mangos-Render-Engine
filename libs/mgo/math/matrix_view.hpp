#pragma once

#include "mgo/iterator.hpp"
#include "two_dimensional_array.hpp"

#include <algorithm>
#include <type_traits>

namespace mgo
{
template <class arithmetic_type, std::size_t M, std::size_t N>
struct matrix;

template <class matrix_type, bool is_column>
struct matrix_view
{
    using size_type       = typename matrix_type::size_type;
    using difference_type = typename matrix_type::difference_type;
    using value_type      = typename matrix_type::value_type;
    using reference       = typename matrix_type::reference;
    using const_reference = typename matrix_type::const_reference;
    using pointer         = typename matrix_type::pointer;
    using const_pointer   = typename matrix_type::const_pointer;

    using iterator = std::conditional_t<is_column, jumping_iterator<pointer, matrix_type::row_size()>, pointer>;
    using const_iterator =
      std::conditional_t<is_column, jumping_iterator<const_pointer, matrix_type::row_size()>, const_pointer>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr bool const is_not_const = not std::is_const_v<matrix_type>;

    static constexpr size_type column_size() noexcept
    {
      return is_column ? matrix_type::column_size() : 1;
    }

    static constexpr size_type row_size() noexcept
    {
      return is_column ? 1 : matrix_type::row_size();
    }

    static constexpr size_type size() noexcept
    {
      return column_size() * row_size();
    }

    constexpr matrix_type &operator=(std::initializer_list<value_type> values) noexcept requires is_not_const
    {
      return assign(values);
    }

    constexpr matrix_type &assign(std::initializer_list<value_type> values) noexcept requires is_not_const
    {
      return assign(values.begin(), values.end());
    }

    constexpr matrix_type &assign(std::input_iterator auto const &first, std::input_iterator auto const &last) noexcept
      requires is_not_const
    {
      std::copy_n(first, std::min(static_cast<size_type>(std::distance(first, last)), size()), begin());
    }

    constexpr reference at(size_type j) requires is_not_const
    {
      if(j >= size())
        throw std::out_of_range("matrix_view::at");
      return _first[j];
    }

    constexpr const_reference at(size_type j) const
    {
      if(j >= size())
        throw std::out_of_range("matrix_view::at");
      return _first[j];
    }

    constexpr reference operator[](size_type j) noexcept requires is_not_const
    {
      return _first[j];
    }

    constexpr const_reference operator[](size_type j) const noexcept
    {
      return _first[j];
    }

    constexpr iterator begin() noexcept requires is_not_const
    {
      return _first;
    }

    constexpr const_iterator begin() const noexcept
    {
      return _first;
    }

    constexpr iterator end() noexcept requires is_not_const
    {
      return _first + size();
    }

    constexpr const_iterator end() const noexcept
    {
      return _first + size();
    }

    constexpr reverse_iterator rbegin() noexcept requires is_not_const
    {
      return reverse_iterator(end());
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
      return const_reverse_iterator(end());
    }

    constexpr reverse_iterator rend() noexcept requires is_not_const
    {
      return reverse_iterator(begin());
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
      return const_reverse_iterator(begin());
    }

    constexpr const_iterator cbegin() const noexcept
    {
      return _first;
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
      return const_reverse_iterator(end());
    }

    constexpr const_iterator cend() const noexcept
    {
      return _first + size();
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
      return const_reverse_iterator(begin());
    }

    constexpr reference front() noexcept requires is_not_const
    {
      return (*this)[0];
    }

    constexpr const_reference front() const noexcept
    {
      return begin()[0];
    }

    constexpr reference back() noexcept requires is_not_const
    {
      return begin()[size() - 1];
    }

    constexpr const_reference back() const noexcept
    {
      return begin()[size() - 1];
    }

  private:
    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend struct matrix;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr auto operator<=>(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                      two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr matrix<arithmetic_type, M, N>
    operator+(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
              two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr matrix<arithmetic_type, M, N>
    operator-(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
              two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N, std::size_t P>
    friend constexpr matrix<arithmetic_type, M, P>
    operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
              two_dimensional_array<arithmetic_type, N, P> auto const &rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr matrix<arithmetic_type, M, N>
    operator*(arithmetic_type lhs, two_dimensional_array<arithmetic_type, M, N> auto const &rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr matrix<arithmetic_type, M, N> operator*(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                             arithmetic_type rhs) noexcept;

    template <class arithmetic_type, std::size_t M, std::size_t N>
    friend constexpr matrix<arithmetic_type, M, N> operator/(two_dimensional_array<arithmetic_type, M, N> auto const &lhs,
                                                             arithmetic_type rhs) noexcept;

    constexpr reference get(size_type i, size_type j) requires is_not_const
    {
      return _first[is_column ? i : j];
    }

    constexpr const_reference get(size_type i, size_type j) const
    {
      return _first[is_column ? i : j];
    }

    matrix_view(std::conditional_t<is_not_const, pointer, const_pointer> first)
    : _first(first)
    {
    }

    std::conditional_t<is_not_const, iterator, const_iterator> _first;
};
}