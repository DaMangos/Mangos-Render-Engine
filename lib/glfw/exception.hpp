#pragma once

#include <stdexcept>

namespace glfw
{
struct exception : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

struct bad_handle_access final : exception
{
    bad_handle_access();
};
}