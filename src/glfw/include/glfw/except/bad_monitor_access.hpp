#pragma once

#include <glfw/except/exception.hpp>

#include <exception>

namespace glfw
{
class bad_monitor_access : public exception, public std::exception
{
  public:
    bad_monitor_access() noexcept;

    [[nodiscard]]
    char const * what() const noexcept override;

  private:
    char const * _what_message;
};
}