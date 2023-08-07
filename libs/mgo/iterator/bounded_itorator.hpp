#pragma once

#include <iterator>
#include <numeric>
#include <stdexcept>

namespace mgo
{
template <class underling_pointer, typename std::iterator_traits<underling_pointer>::difference_type jump_size>
requires std::is_pointer_v<underling_pointer> and (jump_size > 0)
struct bounded_iterator
{
    using value_type        = typename std::iterator_traits<underling_pointer>::value_type;
    using difference_type   = typename std::iterator_traits<underling_pointer>::difference_type;
    using pointer           = typename std::iterator_traits<underling_pointer>::pointer;
    using reference         = typename std::iterator_traits<underling_pointer>::reference;
    using iterator_category = typename std::iterator_traits<underling_pointer>::iterator_category;
    using iterator_concept  = std::contiguous_iterator_tag;

    constexpr bounded_iterator() noexcept = default;

    constexpr bounded_iterator(pointer base, pointer lower, pointer upper)
    : _base(base),
      _lower(lower),
      _upper(upper)
    {
      if(std::distance(_lower, _upper) <= 0)
        throw std::domain_error("lower bound cannot be greater than or equal to upper bound");
      if(std::gcd(jump_size, std::distance(_lower, _upper)) != 1)
        throw std::domain_error("cannot iterate over every element between the lower and upper bound");
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

    constexpr bounded_iterator &operator+=(difference_type difference) noexcept
    {
      return *this = *this + difference;
    }

    constexpr bounded_iterator &operator-=(difference_type difference) noexcept
    {
      return *this = *this - difference;
    }

    constexpr bounded_iterator &operator++() noexcept
    {
      return (*this) += 1;
    }

    constexpr bounded_iterator operator++(int) noexcept
    {
      bounded_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    constexpr bounded_iterator &operator--() noexcept
    {
      return (*this) -= 1;
    }

    constexpr bounded_iterator operator--(int) noexcept
    {
      bounded_iterator tmp = *this;
      --(*this);
      return tmp;
    }

    constexpr bounded_iterator operator+(difference_type difference) const noexcept
    {
      if(not _is_bounded(-1, 0))
        return bounded_iterator(_base + difference, _lower, _upper);

      if(_is_upper_bounded(1 - difference * jump_size))
        return bounded_iterator(_base + difference * jump_size, _lower, _upper);

      return bounded_iterator(_lower + std::distance(_upper, _base + difference * jump_size) % std::distance(_lower, _upper),
                              _lower,
                              _upper);
    }

    constexpr bounded_iterator operator-(difference_type difference) const noexcept
    {
      if(not _is_bounded(0, 1))
        return bounded_iterator(_base - difference, _lower, _upper);

      if(_is_lower_bounded(-1 + difference * jump_size))
        return bounded_iterator(_base - difference * jump_size, _lower, _upper);

      return bounded_iterator(_upper + std::distance(_lower, _base - difference * jump_size) % std::distance(_lower, _upper),
                              _lower,
                              _upper);
    }

    constexpr difference_type operator-(bounded_iterator const &other) const noexcept
    {
      return reinterpret_cast<difference_type>((*this - reinterpret_cast<difference_type>(other._base))._base);
    }

    constexpr auto operator<=>(bounded_iterator const &other) const noexcept = default;

  private:
    constexpr bool _is_bounded(difference_type lower_difference, difference_type upper_difference) const noexcept
    {
      return _is_lower_bounded(lower_difference) and _is_upper_bounded(upper_difference);
    }

    constexpr bool _is_upper_bounded(difference_type difference) const noexcept
    {
      return std::distance(_base, _upper + difference) > 0;
    }

    constexpr bool _is_lower_bounded(difference_type difference) const noexcept
    {
      return std::distance(_base, _lower + difference) < 0;
    }

    pointer _base = nullptr, _lower = nullptr, _upper = nullptr;
};

template <class underling_pointer, typename std::iterator_traits<underling_pointer>::difference_type jump_size>
constexpr bounded_iterator<underling_pointer, jump_size>
operator+(typename bounded_iterator<underling_pointer, jump_size>::difference_type difference,
          bounded_iterator<underling_pointer, jump_size> const                    &iterator) noexcept
{
  return iterator + difference;
}
}