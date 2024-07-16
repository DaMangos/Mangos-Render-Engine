#include "make_shared_string.hpp"

#include <cstring>
#include <limits>
#include <source_location>
#include <stdexcept>
#include <string>

std::shared_ptr<char const[]> glfw::internal::make_shared_string(char const * const str)
{
  using namespace std::string_literals;

  if(not str)
    throw std::invalid_argument(std::source_location::current().function_name() + ": input string is null"s);

  auto const size = std::strlen(str);

  if(size == std::numeric_limits<std::size_t>::max())
    throw std::length_error(std::source_location::current().function_name() + ": input string is too large"s);

  auto const ptr = std::make_shared<char[]>(size + 1);

  std::strcpy(ptr.get(), str);

  return ptr;
}