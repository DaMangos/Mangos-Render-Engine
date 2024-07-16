#include "internal/make_shared_string.hpp"
#include <glfw/except/out_of_memory.hpp>

glfw::out_of_memory::out_of_memory(char const * what_arg)
: _what_message(internal::make_shared_string(what_arg))
{
}

char const * glfw::out_of_memory::what() const noexcept
{
  return _what_message.get();
}
