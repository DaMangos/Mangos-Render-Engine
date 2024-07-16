#include <glfw/except/exception.hpp>

#include <source_location>

glfw::exception::exception() noexcept
: _what_message(std::source_location::current().function_name())
{
}

char const * glfw::exception::what() const noexcept
{
  return "glfw::exception";
}