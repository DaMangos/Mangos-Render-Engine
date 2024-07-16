#include <glfw/except/invalid_value.hpp>

char const * glfw::invalid_value::what() const noexcept
{
  return std::invalid_argument::what();
}