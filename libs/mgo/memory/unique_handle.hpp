#pragma once

#include "deleter.hpp"

#include <memory>
#include <utility>

namespace mgo
{
template <class value_type>
using unique_handle = std::unique_ptr<typename std::pointer_traits<value_type>::element_type, deleter<value_type>>;

template <class value_type>
constexpr unique_handle<value_type> make_unique_handle(value_type value, auto &&...deleter_args)
{
  return unique_handle<value_type>(value, deleter<value_type>(std::forward<decltype(deleter_args)>(deleter_args)...));
}
}
