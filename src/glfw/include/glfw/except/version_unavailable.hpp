#pragma once

#include <glfw/except/exception.hpp>

#include <stdexcept>

namespace glfw
{
class version_unavailable : public exception, public std::runtime_error
{
  public:
    using std::runtime_error::runtime_error;

    [[nodiscard]]
    char const * what() const noexcept override;
};
}