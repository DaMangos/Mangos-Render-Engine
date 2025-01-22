#include "render_window_impl.hpp"

graphics::detail::render_window_impl::render_window_impl(std::string const & title, pixel const width, pixel const height, bool const debug)
: display_window(title, width, height),
  graphics_pipeline(display_window.get_shared(), debug)
{
}
