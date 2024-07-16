#pragma once

#include <glfw/except/exception.hpp>

#include <memory>
#include <new>

namespace glfw
{
class out_of_memory : public exception, public std::bad_alloc
{
  public:
    out_of_memory(char const * what_arg);

    [[nodiscard]]
    char const * what() const noexcept override;

  private:
    std::shared_ptr<char const[]> _what_message;
};
}