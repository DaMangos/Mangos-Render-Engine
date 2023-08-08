#pragma once

#include "deleter.hpp"
#include "handle_traits.hpp"

#include <memory>
#include <utility>

namespace mgo
{
template <class handling_type>
using unique_handle = std::unique_ptr<typename handle_traits<handling_type>::handle_type, deleter<handling_type>>;

template <class handling_type>
constexpr unique_handle<handling_type> make_unique_handle(typename handle_traits<handling_type>::pointer value,
                                                          auto &&...deleter_args)
{
  return unique_handle<handling_type>(value, deleter<handling_type>(std::forward<decltype(deleter_args)>(deleter_args)...));
}
}
