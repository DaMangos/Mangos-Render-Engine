#include <glfw/except/bad_monitor_access.hpp>

#include <source_location>

glfw::bad_monitor_access::bad_monitor_access() noexcept
: _what_message(std::source_location::current().function_name())
{
}

char const * glfw::bad_monitor_access::what() const noexcept
{
  return _what_message;
}