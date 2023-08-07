#pragma once

#include "font.hpp"

#include <iostream>

namespace mgo
{

struct general_info_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::reset << input;
    }
};

struct general_warning_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::magenta << "warning: " << font::reset << input;
    }
};

struct general_error_ostream
{
    std::ostream &operator<<(auto const &input) const
    {
      return std::cerr << font::bold << font::red << "error: " << font::reset << input;
    }
};

extern general_info_ostream    log_general_info;
extern general_warning_ostream log_general_warning;
extern general_error_ostream   log_general_error;
}