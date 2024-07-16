#include <glfw/except/feature_unavailable.hpp>

char const * glfw::feature_unavailable::what() const noexcept
{
  return std::runtime_error::what();
}