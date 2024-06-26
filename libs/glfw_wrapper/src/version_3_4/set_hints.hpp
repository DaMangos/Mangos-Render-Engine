#pragma once

#include <glfw_wrapper/version_3_4/library_hints.hpp>
#include <glfw_wrapper/version_3_4/window_hints.hpp>

namespace glfw
{
inline namespace version_3_4
{
void set_hints(window_hints const & hints) noexcept;

void set_hints(library_hints const & hints) noexcept;
}
}