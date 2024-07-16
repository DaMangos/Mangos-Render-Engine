#include <glfw/except/cursor_unavailable.hpp>

char const * glfw::cursor_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}