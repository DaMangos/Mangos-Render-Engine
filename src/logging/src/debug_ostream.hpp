#pragma once

#include "empty_ostream.hpp"
#include "font.hpp"

#include <iostream>

namespace logging
{

struct debug_info_ostream
{
    std::ostream &operator<<([[maybe_unused]] auto const &input) const
    {
#ifdef DEBUG
      return std::cerr << font::reset << input;
#else
      return empty_ostream();
#endif
    }
};

struct debug_warning_ostream
{
    std::ostream &operator<<([[maybe_unused]] auto const &input) const
    {
#ifdef DEBUG
      return std::cerr << font::bold << font::magenta << "warning: " << font::reset << input;
#else
      return empty_ostream();
#endif
    }
};

struct debug_error_ostream
{
#ifdef DEBUG
    std::ostream &operator<<([[maybe_unused]] auto const &input) const
    {
      return std::cerr << font::bold << font::red << "error: " << font::reset << input;
#else
    return empty_ostream();
#endif
    }
};

extern debug_info_ostream    debug_info;
extern debug_warning_ostream debug_warning;
extern debug_error_ostream   debug_error;
}