#include "display_window.hpp"
#include "graphics_pipeline.hpp"

namespace graphics::detail
{
class render_window_impl
{
  public:
    render_window_impl(std::string const & title, pixel const width, pixel const height, bool const debug);

    display_window    display_window;
    graphics_pipeline graphics_pipeline;
};
}
