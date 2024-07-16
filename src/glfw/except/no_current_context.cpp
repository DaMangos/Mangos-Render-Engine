#include <glfw/except/no_current_context.hpp>

char const * glfw::no_current_context::what() const noexcept
{
  return std::logic_error::what();
}