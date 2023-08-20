#pragma once

#include "fwd.hpp"

namespace glfw
{
struct window
{
    using element_type = typename window_handle::element_type;
    using pointer      = typename window_handle::pointer;

    GLFWwindow *get() const noexcept;

    bool should_close() const noexcept;

    bool has_framebuffer_resized() noexcept;

    VkExtent2D get_framebuffer_size() const noexcept;

  private:
    window(window_handle window) noexcept;

    window_handle _window;
};
}