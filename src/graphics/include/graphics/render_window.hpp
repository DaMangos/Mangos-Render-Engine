#pragma once

#include "pixel.hpp"

#include <memory>
#include <string>

namespace graphics
{
class render_window
{
  public:
    static std::ostream error_out;
    static std::ostream warning_out;
    static std::ostream info_out;
    static std::ostream verbose_out;

    render_window(std::string const & title, pixel const width, pixel const height);

  private:
    std::unique_ptr<class render_window_implementation, void (*)(render_window_implementation *)> underlying_implementation;
};
}
