#pragma once

#include <glfw/structs/library_hints.hpp>
#include <glfw/structs/window_hints.hpp>

namespace glfw::internal
{
void set_hints(window_hints const & hints) noexcept;

void set_hints(library_hints const & hints) noexcept;
}