#pragma once

#include "_unique_vector_deallocator.hpp"

#include <ranges>

namespace mgo
{
template <class value_type, class alloc_type = std::allocator<value_type>>
using unique_vector = std::unique_ptr<value_type[], _unique_vector_deallocator<value_type, alloc_type>>;

template <std::ranges::contiguous_range container, class alloc_type = std::allocator<typename container::value_type>>
constexpr unique_vector<typename container::value_type> make_unique_vector(container &values, auto &&...deleter_args)
{
  using unique_vector = unique_vector<typename container::value_type, alloc_type>;
  using deleter_type  = typename unique_vector::deleter_type;
  using alloc_traits  = std::allocator_traits<alloc_type>;
  alloc_type  alloc;
  std::size_t count = values.size();
  auto       *data  = alloc_traits::allocate(alloc, count);
  for(std::size_t i = 0; i < count; i++)
    alloc_traits::construct(alloc, data + i, std::move(values[i]));
  values.clear();
  return unique_vector(data, deleter_type(count, std::forward<decltype(deleter_args)>(deleter_args)...));
}
}
