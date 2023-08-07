#pragma once

#include "empty_ostream.hpp"
#include "font.hpp"

#include <iostream>

namespace mgo
{

struct debug_info_ostream
{
#ifdef DEBUG
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::reset << input;
    }
#else
    constexpr empty_ostream operator<<(auto const &) const noexcept
    {
      return empty_ostream();
    }
#endif
};

struct debug_warning_ostream
{
#ifdef DEBUG
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::magenta << "warning: " << font::reset << input;
    }
#else
    constexpr empty_ostream operator<<(auto const &) const noexcept
    {
      return empty_ostream();
    }
#endif
};

struct debug_error_ostream
{
#ifdef DEBUG
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::red << "error: " << font::reset << input;
    }
#else
    constexpr empty_ostream operator<<(auto const &) const noexcept
    {
      return empty_ostream();
    }
#endif
};

extern debug_info_ostream    log_debug_info;
extern debug_warning_ostream log_debug_warning;
extern debug_error_ostream   log_debug_error;
}