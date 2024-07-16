#pragma once

#include <glfw/except/exception.hpp>

#include <exception>
#include <memory>

namespace glfw
{
class not_initialized : public exception, public std::exception
{
  public:
    not_initialized(char const * what_arg);

    [[nodiscard]]
    char const * what() const noexcept override;

  private:
    std::shared_ptr<char const[]> _what_message;
};
}