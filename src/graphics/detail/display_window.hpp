#pragma once

#include <graphics/pixel.hpp>

#include <GLFW/glfw3.h>

#include <memory>
#include <string>

namespace graphics::detail
{
class display_window
{
  public:
    display_window(std::string const & title, pixel const width, pixel const height);

    [[nodiscard]]
    GLFWwindow * get() const noexcept;

    std::shared_ptr<GLFWwindow> const & get_shared() const noexcept;

    display_window(display_window && other) noexcept;

    display_window(display_window const &) noexcept = delete;

    display_window & operator=(display_window const &) noexcept = delete;

    display_window & operator=(display_window && other) noexcept;

    ~display_window() = default;

  private:
    std::shared_ptr<GLFWwindow> window;
};
}
