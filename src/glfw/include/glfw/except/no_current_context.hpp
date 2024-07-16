#pragma once

#include <glfw/except/exception.hpp>

#include <stdexcept>

namespace glfw
{
class no_current_context : public exception, public std::logic_error
{
  public:
    using std::logic_error::logic_error;

    [[nodiscard]]
    char const * what() const noexcept override;
};
}