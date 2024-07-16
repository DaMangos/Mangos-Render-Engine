#include <glfw/except/bad_window_access.hpp>

#include <source_location>

glfw::bad_window_access::bad_window_access() noexcept
: _what_message(std::source_location::current().function_name())
{
}

char const * glfw::bad_window_access::what() const noexcept
{
  return _what_message;
}