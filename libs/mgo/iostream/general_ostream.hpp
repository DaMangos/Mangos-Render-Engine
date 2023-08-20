#pragma once

#include "font.hpp"

#include <iostream>

namespace mgo
{
struct info_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cout << font::reset << input;
    }
};

struct warning_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::magenta << "warning: " << font::reset << input;
    }
};

struct error_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::red << "error: " << font::reset << input;
    }
};

extern info_ostream    cout_info;
extern warning_ostream cerr_warning;
extern error_ostream   cerr_error;
}