#include <glfw/except/platform_error.hpp>

char const * glfw::platform_error::what() const noexcept
{
  return std::runtime_error::what();
}