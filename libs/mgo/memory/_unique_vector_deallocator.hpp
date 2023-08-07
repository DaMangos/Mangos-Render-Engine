#pragma once

#include "_unique_vector_deallocator_data.hpp"

#include <concepts>
#include <memory>

namespace mgo
{
template <class value_type, class alloc_type>
struct _unique_vector_deallocator : _unique_vector_deallocator_data<value_type>
{
    constexpr _unique_vector_deallocator(std::size_t count, auto &&...deleter_args)
    : _unique_vector_deallocator_data<value_type>(std::forward<decltype(deleter_args)>(deleter_args)...),
      _count(count)
    {
    }

    constexpr void operator()(value_type *data) noexcept requires std::invocable<deleter<value_type>, value_type *, std::size_t>
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      std::invoke(_unique_vector_deallocator_data<value_type>::_deleter, data, _count);
      for(std::size_t i = 0; i < _count; i++)
        alloc_traits::destroy(alloc, data + i);
      alloc_traits::deallocate(alloc, data, _count);
    }

    constexpr void operator()(value_type *data) noexcept requires std::invocable<deleter<value_type>, value_type>
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      for(std::size_t i = 0; i < _count; i++)
      {
        std::invoke(_unique_vector_deallocator_data<value_type>::_deleter, data[i]);
        alloc_traits::destroy(alloc, data + i);
      }
      alloc_traits::deallocate(alloc, data, _count);
    }

    constexpr void operator()(value_type *data) noexcept
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      for(std::size_t i = 0; i < _count; i++)
        alloc_traits::destroy(alloc, data + i);
      alloc_traits::deallocate(alloc, data, _count);
    }

  private:
    std::size_t _count;
};
}