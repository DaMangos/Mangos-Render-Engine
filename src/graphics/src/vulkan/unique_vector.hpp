#pragma once

#include <memory>
#include <type_traits>

namespace graphics::vulkan
{
template <class value_type>
struct deleter;

template <class value_type, class alloc_type = std::allocator<value_type>>
struct _unique_vector_deallocator;

template <class value_type, class alloc_type = std::allocator<value_type>>
using unique_vector = std::unique_ptr<value_type[], _unique_vector_deallocator<value_type, alloc_type>>;

template <class value_type, bool has_deleter>
struct _unique_vector_deallocator_data;

template <class value_type>
struct _unique_vector_deallocator_data<value_type, true>
{
  protected:
    constexpr _unique_vector_deallocator_data(auto &&...deleter_args)
    : _deleter(std::forward<decltype(deleter_args)>(deleter_args)...)
    {
    }

    deleter<value_type> _deleter;
};

template <class value_type>
struct _unique_vector_deallocator_data<value_type, false>
{
  protected:
    constexpr _unique_vector_deallocator_data() noexcept = default;
};

template <class value_type, class alloc_type>
struct _unique_vector_deallocator
: _unique_vector_deallocator_data<value_type,
                                  std::invocable<deleter<value_type>, value_type *, std::size_t> or
                                    std::invocable<deleter<value_type>, value_type>>
{
    constexpr _unique_vector_deallocator(std::size_t count, auto &&...deleter_args)
    : _deallocator_data(std::forward<decltype(deleter_args)>(deleter_args)...),
      _count(count)
    {
    }

    constexpr void operator()(value_type *data) const noexcept
      requires std::invocable<deleter<value_type>, value_type *, std::size_t>
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      std::invoke(_deallocator_data::_deleter, data, _count);
      for(std::size_t i = 0; i < _count; i++)
        alloc_traits::destroy(alloc, data + i);
      alloc_traits::deallocate(alloc, data, _count);
    }

    constexpr void operator()(value_type *data) const noexcept requires std::invocable<deleter<value_type>, value_type>
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      for(std::size_t i = 0; i < _count; i++)
      {
        std::invoke(_deallocator_data::_deleter, data[i]);
        alloc_traits::destroy(alloc, data + i);
      }
      alloc_traits::deallocate(alloc, data, _count);
    }

    constexpr void operator()(value_type *data) const noexcept
    {
      using alloc_traits = std::allocator_traits<alloc_type>;
      alloc_type alloc;
      for(std::size_t i = 0; i < _count; i++)
        alloc_traits::destroy(alloc, data + i);
      alloc_traits::deallocate(alloc, data, _count);
    }

  private:
    using _deallocator_data = _unique_vector_deallocator_data<value_type,
                                                              std::invocable<deleter<value_type>, value_type *, std::size_t> or
                                                                std::invocable<deleter<value_type>, value_type>>;
    std::size_t _count;
};

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
