#include <glfw/except/format_unavailable.hpp>

char const * glfw::format_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}