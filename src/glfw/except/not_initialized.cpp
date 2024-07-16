#include "internal/make_shared_string.hpp"
#include <glfw/except/not_initialized.hpp>

glfw::not_initialized::not_initialized(char const * what_arg)
: _what_message(internal::make_shared_string(what_arg))
{
}

char const * glfw::not_initialized::what() const noexcept
{
  return _what_message.get();
}
