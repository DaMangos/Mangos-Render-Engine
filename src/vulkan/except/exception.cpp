#include <vulkan/except/exception.hpp>

#include <source_location>

vulkan::exception::exception() noexcept
: _what_message(std::source_location::current().function_name())
{
}

char const * vulkan::exception::what() const noexcept
{
  return _what_message;
}