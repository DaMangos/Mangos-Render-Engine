#include <glfw/except/no_window_context.hpp>

char const * glfw::no_window_context::what() const noexcept
{
  return std::logic_error::what();
}