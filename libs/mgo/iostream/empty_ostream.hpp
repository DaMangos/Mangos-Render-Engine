#pragma once

#include <iosfwd>

namespace mgo
{
struct empty_ostream
{
    template <class input_type>
    constexpr empty_ostream operator<<(input_type const &) const noexcept
      requires requires(input_type input, std::ostream stream) { stream << input; }
    {
      return empty_ostream();
    }
};
}