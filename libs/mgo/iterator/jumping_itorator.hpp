#pragma once

#include <iterator>

namespace mgo
{
template <class underling_pointer, typename std::iterator_traits<underling_pointer>::difference_type jump_size>
requires std::is_pointer_v<underling_pointer> and (jump_size > 0)
struct jumping_iterator
{
    using value_type        = typename std::iterator_traits<underling_pointer>::value_type;
    using difference_type   = typename std::iterator_traits<underling_pointer>::difference_type;
    using pointer           = typename std::iterator_traits<underling_pointer>::pointer;
    using reference         = typename std::iterator_traits<underling_pointer>::reference;
    using iterator_category = typename std::iterator_traits<underling_pointer>::iterator_category;
    using iterator_concept  = std::contiguous_iterator_tag;

    constexpr jumping_iterator() noexcept = default;

    constexpr jumping_iterator(pointer base)
    : _base(base)
    {
    }

    constexpr reference operator*() const noexcept
    {
      return *_base;
    }

    constexpr pointer operator->() const noexcept
    {
      return std::to_address(_base);
    }

    constexpr reference operator[](difference_type difference) const noexcept
    {
      return *(*this + difference);
    }

    constexpr jumping_iterator &operator+=(difference_type difference) noexcept
    {
      return *this = *this + difference;
    }

    constexpr jumping_iterator &operator-=(difference_type difference) noexcept
    {
      return *this = *this - difference;
    }

    constexpr jumping_iterator &operator++() noexcept
    {
      return (*this) += 1;
    }

    constexpr jumping_iterator operator++(int) noexcept
    {
      jumping_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    constexpr jumping_iterator &operator--() noexcept
    {
      return (*this) -= 1;
    }

    constexpr jumping_iterator operator--(int) noexcept
    {
      jumping_iterator tmp = *this;
      --(*this);
      return tmp;
    }

    constexpr jumping_iterator operator+(difference_type difference) const noexcept
    {
      return jumping_iterator(_base + difference * jump_size);
    }

    constexpr jumping_iterator operator-(difference_type difference) const noexcept
    {
      return jumping_iterator(_base - difference * jump_size);
    }

    constexpr difference_type operator-(jumping_iterator const &other) const noexcept
    {
      return reinterpret_cast<difference_type>((*this - reinterpret_cast<difference_type>(other._base))._base);
    }

    constexpr auto operator<=>(jumping_iterator const &other) const noexcept = default;

  private:
    pointer _base = nullptr;
};

template <class underling_pointer, typename std::iterator_traits<underling_pointer>::difference_type jump_size>
constexpr jumping_iterator<underling_pointer, jump_size>
operator+(typename jumping_iterator<underling_pointer, jump_size>::difference_type difference,
          jumping_iterator<underling_pointer, jump_size> const                    &iterator) noexcept
{
  return iterator + difference;
}
}