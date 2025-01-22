#include "display_window.hpp"

#include <GLFW/glfw3.h>

graphics::detail::display_window::display_window(std::string const & title, pixel const width, pixel const height)
: window((glfwDefaultWindowHints(),
          glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API),
          glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr)),
         glfwDestroyWindow)
{
  if(window)
    glfwSetWindowUserPointer(window.get(), this);
}

graphics::detail::display_window::display_window(display_window && other) noexcept
: window(std::move(other.window))
{
  if(window)
    glfwSetWindowUserPointer(window.get(), this);
}

graphics::detail::display_window & graphics::detail::display_window::operator=(display_window && other) noexcept
{
  window = std::move(other.window);

  if(window)
    glfwSetWindowUserPointer(window.get(), this);

  return *this;
}

GLFWwindow * graphics::detail::display_window::get() const noexcept
{
  return window.get();
}

std::shared_ptr<GLFWwindow> const & graphics::detail::display_window::get_shared() const noexcept
{
  return window;
}