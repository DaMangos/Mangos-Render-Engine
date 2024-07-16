#include <glfw/except/platform_unavailable.hpp>

char const * glfw::platform_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}