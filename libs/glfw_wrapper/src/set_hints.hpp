#include <glfw_wrapper/handles/hints/library_hints.hpp>
#include <glfw_wrapper/handles/hints/window_hints.hpp>

namespace glfw
{
inline namespace version_3_4
{
void set_hints(window_hints const & hints) noexcept;

void set_hints(library_hints const & hints) noexcept;
}
}