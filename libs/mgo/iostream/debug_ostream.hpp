#pragma once

#include "empty_ostream.hpp"
#include "font.hpp"

#include <iostream>

namespace mgo::debug
{

struct info_ostream
{
#ifndef NDEBUG
    std::ostream &operator<<(auto const &input) const
    {
      return std::cout << font::reset << input;
    }
#else
    constexpr empty_ostream operator<<(auto const &) const noexcept
    {
      return empty_ostream();
    }
#endif
};

struct warning_ostream
{
#ifdef NDEBUG
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

struct error_ostream
{
#ifdef NDEBUG
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

extern info_ostream    cout_info;
extern warning_ostream cerr_warning;
extern error_ostream   cerr_error;
}