#pragma once

#include <glfw/except/exception.hpp>

#include <stdexcept>

namespace glfw
{
class invalid_value : public exception, public std::invalid_argument
{
  public:
    using std::invalid_argument::invalid_argument;

    [[nodiscard]]
    char const * what() const noexcept override;
};
}