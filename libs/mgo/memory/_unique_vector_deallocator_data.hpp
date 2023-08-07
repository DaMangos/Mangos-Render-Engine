#pragma once

#include "deleter.hpp"

#include <functional>
#include <utility>

namespace mgo
{
template <class value_type,
          bool has_deleter =
            std::invocable<deleter<value_type>, value_type *, std::size_t> or std::invocable<deleter<value_type>, value_type>>
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
}