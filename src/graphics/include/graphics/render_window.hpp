#pragma once

#include "pixel.hpp"

#include <memory>
#include <string>

namespace graphics
{
namespace detail
{
class render_window_impl;
}

class render_window
{
  public:
    static std::ostream error_out;
    static std::ostream warning_out;
    static std::ostream info_out;
    static std::ostream verbose_out;

    render_window(std::string const & title, pixel const width, pixel const height);

    render_window(std::string const & title, pixel const width, pixel const height, bool const debug);

  private:
    std::unique_ptr<detail::render_window_impl, void (*)(detail::render_window_impl * const)> underlying_implementation;
};
}
