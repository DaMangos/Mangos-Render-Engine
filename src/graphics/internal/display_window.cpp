#include "display_window.hpp"

#include <GLFW/glfw3.h>

graphics::internal::display_window::display_window(std::string const & title, pixel const width, pixel const height)
: _window((glfwDefaultWindowHints(),
           glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API),
           glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr)),
          glfwDestroyWindow)
{
  if(_window)
    glfwSetWindowUserPointer(_window.get(), this);
}

graphics::internal::display_window::display_window(display_window && other) noexcept
: _window(std::move(other._window))
{
  if(_window)
    glfwSetWindowUserPointer(_window.get(), this);
}

graphics::internal::display_window & graphics::internal::display_window::operator=(display_window && other) noexcept
{
  _window = std::move(other._window);

  if(_window)
    glfwSetWindowUserPointer(_window.get(), this);

  return *this;
}

GLFWwindow * graphics::internal::display_window::get() const noexcept
{
  return _window.get();
}

std::shared_ptr<GLFWwindow> const & graphics::internal::display_window::get_shared() const noexcept
{
  return _window;
}