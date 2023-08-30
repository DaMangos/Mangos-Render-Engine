#pragma once

#include "matrix_data.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <mgo/iterator.hpp>
#include <type_traits>

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

    template <bool is_mutable, bool is_column>
    struct view
    {
        using iterator               = std::conditional_t<is_column, jumping_iterator<pointer, M>, pointer>;
        using const_iterator         = std::conditional_t<is_column, jumping_iterator<const_pointer, M>, const_pointer>;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static constexpr size_type column_size() noexcept
        {
          return is_column ? M : 1;
        }

        static constexpr size_type row_size() noexcept
        {
          return is_column ? 1 : N;
        }

        static constexpr size_type size() noexcept
        {
          return column_size() * row_size();
        }

        constexpr operator matrix<arithmetic_type, column_size(), row_size()>() const noexcept
        {
          return matrix<arithmetic_type, column_size(), row_size()>(begin(), end());
        }

        constexpr view &operator=(matrix<arithmetic_type, column_size(), row_size()> const &other) noexcept requires is_mutable
        {
          std::copy(first, std::min(static_cast<size_type>(std::distance(first, last)), size()), begin());
          return *this;
        }

        constexpr view &operator=(std::initializer_list<value_type> values) noexcept requires is_mutable
        {
          static_assert(values.size() <= size(), "");
          std::copy(values.begin(),
                    std::min(static_cast<size_type>(std::distance(values.begin(), values.end())), size()),
                    begin());
          return *this;
        }

        constexpr iterator begin() noexcept requires is_mutable
        {
          return _first;
        }

        constexpr const_iterator begin() const noexcept
        {
          return _first;
        }

        constexpr const_iterator cbegin() const noexcept
        {
          return _first;
        }

        constexpr iterator end() noexcept requires is_mutable
        {
          return std::next(_first, size());
        }

        constexpr const_iterator end() const noexcept
        {
          return std::next(_first, size());
        }

        constexpr const_iterator cend() const noexcept
        {
          return std::next(_first, size());
        }

        constexpr reverse_iterator rbegin() noexcept requires is_mutable
        {
          return std::make_reverse_iterator(end());
        }

        constexpr const_reverse_iterator rbegin() const noexcept
        {
          return std::make_reverse_iterator(end());
        }

        constexpr const_reverse_iterator crbegin() const noexcept
        {
          return std::make_reverse_iterator(end());
        }

        constexpr reverse_iterator rend() noexcept requires is_mutable
        {
          return std::make_reverse_iterator(begin());
        }

        constexpr const_reverse_iterator rend() const noexcept
        {
          return std::make_reverse_iterator(begin());
        }

        constexpr const_reverse_iterator crend() const noexcept
        {
          return std::make_reverse_iterator(begin());
        }

        constexpr reference operator[](size_type j) noexcept requires is_mutable
        {
          return (*this)[j];
        }

        constexpr const_reference operator[](size_type j) const noexcept
        {
          return (*this)[j];
        }

        constexpr reference at(size_type j) requires is_mutable
        {
          if(j >= size())
            throw std::out_of_range("matrix::view::at");
          return (*this)[j];
        }

        constexpr const_reference at(size_type j) const
        {
          if(j >= size())
            throw std::out_of_range("matrix::view::at");
          return (*this)[j];
        }

        constexpr reference front() noexcept requires is_mutable
        {
          return begin()[0];
        }

        constexpr const_reference front() const noexcept
        {
          return begin()[0];
        }

        constexpr reference back() noexcept requires is_mutable
        {
          return begin()[size() - 1];
        }

        constexpr const_reference back() const noexcept
        {
          return begin()[size() - 1];
        }

      private:
        constexpr view(std::conditional_t<is_mutable, pointer, const_pointer> first) noexcept
        : _first(first)
        {
        }

        std::conditional_t<is_mutable, iterator, const_iterator> _first;
    };
};
}