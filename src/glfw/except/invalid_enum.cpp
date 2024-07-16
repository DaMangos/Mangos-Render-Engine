#include <glfw/except/invalid_enum.hpp>

char const * glfw::invalid_enum::what() const noexcept
{
  return std::invalid_argument::what();
}