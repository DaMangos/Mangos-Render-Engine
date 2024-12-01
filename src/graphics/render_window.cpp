#include "include/graphics/render_window.hpp"

#include "internal/display_window.hpp"
#include "internal/graphics_pipeline.hpp"

#include <iostream>

namespace graphics
{
std::ostream render_window::error_out(nullptr);
std::ostream render_window::warning_out(nullptr);
std::ostream render_window::info_out(nullptr);
std::ostream render_window::verbose_out(nullptr);

class render_window_implementation
{
  public:
    render_window_implementation(std::string const & title, pixel const width, pixel const height)
    : display_window(title, width, height),
      graphics_pipeline(display_window.get_shared())
    {
    }

    internal::display_window    display_window;
    internal::graphics_pipeline graphics_pipeline;
};
}

graphics::render_window::render_window(std::string const & title, pixel const width, pixel const height)
: underlying_implementation(new render_window_implementation(title, width, height), [](auto * const ptr) { delete ptr; })
{
}
