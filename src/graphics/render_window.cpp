#include "detail/render_window_impl.hpp"

#include <graphics/render_window.hpp>

#include <iostream>

std::ostream graphics::render_window::error_out(nullptr);
std::ostream graphics::render_window::warning_out(nullptr);
std::ostream graphics::render_window::info_out(nullptr);
std::ostream graphics::render_window::verbose_out(nullptr);

graphics::render_window::render_window(std::string const & title, graphics::pixel const width, graphics::pixel const height)
: render_window(title, width, height, error_out.rdbuf() or warning_out.rdbuf() or info_out.rdbuf() or verbose_out.rdbuf())
{
}

graphics::render_window::render_window(std::string const & title, graphics::pixel const width, graphics::pixel const height, bool const debug)
: underlying_implementation(new detail::render_window_impl(title, width, height, debug), [](auto * const ptr) { delete ptr; })
{
}
