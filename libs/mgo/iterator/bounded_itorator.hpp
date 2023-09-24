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
    : base_(base),
      lower_(lower),
      upper_(upper)
    {
      if(std::distance(lower_bound(), upper_bound()) <= 0)
        throw std::domain_error("lower bound cannot be greater than or equal to upper bound");
      if(std::gcd(jump_size, std::distance(lower_bound(), upper_bound())) != 1)
        throw std::domain_error("cannot iterate over every element between the lower and upper bound");
    }

    constexpr reference operator*() const noexcept
    {
      return *base();
    }

    constexpr pointer operator->() const noexcept
    {
      return base();
    }

    constexpr reference operator[](difference_type difference) const noexcept
    {
      return *std::next(*this, difference);
    }

    constexpr bounded_iterator &operator+=(difference_type difference) noexcept
    {
      return *this = std::next(*this, difference);
    }

    constexpr bounded_iterator &operator-=(difference_type difference) noexcept
    {
      return *this = std::prev(*this, difference);
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
      if(not is_bounded(-1, 0))
        return bounded_iterator(std::next(base(), difference), lower_bound(), upper_bound());

      if(is_upper_bounded(1 - difference * jump_size))
        return bounded_iterator(std::next(base(), difference * jump_size), lower_bound(), upper_bound());

      return bounded_iterator(std::next(lower_bound(),
                                        std::distance(upper_bound(), std::next(base(), difference * jump_size)) %
                                          std::distance(lower_bound(), upper_bound())),
                              lower_bound(),
                              upper_bound());
    }

    constexpr bounded_iterator operator-(difference_type difference) const noexcept
    {
      if(not is_bounded(0, 1))
        return bounded_iterator(std::prev(base(), difference), lower_bound(), upper_bound());

      if(is_lower_bounded(-1 + difference * jump_size))
        return bounded_iterator(std::prev(base(), difference * jump_size), lower_bound(), upper_bound());

      return bounded_iterator(std::next(upper_bound(),
                                        std::distance(lower_bound(), std::prev(base(), difference * jump_size)) %
                                          std::distance(lower_bound(), upper_bound())),
                              lower_bound(),
                              upper_bound());
    }

    constexpr difference_type operator-(bounded_iterator const &other) const noexcept
    {
      return std::distance(base(), other.base());
    }

    [[nodiscard]]
    constexpr pointer base() const noexcept
    {
      return base_;
    }

    [[nodiscard]]
    constexpr pointer lower_bound() const noexcept
    {
      return lower_;
    }

    [[nodiscard]]
    constexpr pointer upper_bound() const noexcept
    {
      return upper_;
    }

    constexpr auto operator<=>(bounded_iterator const &other) const noexcept = default;

  private:
    constexpr bool is_bounded(difference_type lower_difference, difference_type upper_difference) const noexcept
    {
      return is_lower_bounded(lower_difference) and is_upper_bounded(upper_difference);
    }

    constexpr bool is_upper_bounded(difference_type difference) const noexcept
    {
      return std::distance(base(), std::next(upper_bound(), difference)) > 0;
    }

    constexpr bool is_lower_bounded(difference_type difference) const noexcept
    {
      return std::distance(base(), std::next(lower_bound(), difference)) < 0;
    }

    pointer base_ = nullptr, lower_ = nullptr, upper_ = nullptr;
};

template <class underling_pointer, typename std::iterator_traits<underling_pointer>::difference_type jump_size>
constexpr bounded_iterator<underling_pointer, jump_size>
operator+(typename bounded_iterator<underling_pointer, jump_size>::difference_type difference,
          bounded_iterator<underling_pointer, jump_size> const                    &iterator) noexcept
{
  return std::next(iterator, difference);
}
}