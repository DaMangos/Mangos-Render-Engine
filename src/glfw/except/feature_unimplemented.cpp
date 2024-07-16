#include <glfw/except/feature_unimplemented.hpp>

char const * glfw::feature_unimplemented::what() const noexcept
{
  return std::runtime_error::what();
}