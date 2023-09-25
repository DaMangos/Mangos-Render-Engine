#pragma once

#include "data_types.hpp"

namespace glfw
{
struct monitor
{
  private:
    friend struct window;
    monitor(GLFWmonitor *&&monitor) noexcept;

    GLFWmonitor *monitor_;
};
}
