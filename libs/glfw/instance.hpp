#pragma once

#include "fwd.hpp"

namespace glfw
{
struct instance
{
    instance();

    instance &operator=(instance &&) noexcept;

    instance(instance &&) noexcept;

    ~instance() noexcept;

    window glfwCreateWindow(int width, int height, char const *title, GLFWmonitor *monitor, GLFWwindow *share) const;

    instance &operator=(instance const &) = delete;
    instance(instance const &)            = delete;

  private:
    bool _initialized = false;
};
};