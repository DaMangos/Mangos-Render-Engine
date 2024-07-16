#include <glfw/except/version_unavailable.hpp>

char const * glfw::version_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}