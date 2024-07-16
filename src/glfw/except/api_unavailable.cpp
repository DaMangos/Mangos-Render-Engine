#include <glfw/except/api_unavailable.hpp>

char const * glfw::api_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}