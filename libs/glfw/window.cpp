#include "window.hpp"

#include "GLFW/glfw3.h"
#include "monitor.hpp"

#include <stdexcept>

namespace glfw
{
constexpr const std::size_t should_closed_index              = 0;
constexpr const std::size_t should_refresh_index             = 1;
constexpr const std::size_t has_moved_index                  = 2;
constexpr const std::size_t has_resized_index                = 3;
constexpr const std::size_t has_framebuffer_resized_index    = 4;
constexpr const std::size_t has_content_scale_changed_index  = 5;
constexpr const std::size_t has_iconified_index              = 6;
constexpr const std::size_t has_restored_from_iconify_index  = 7;
constexpr const std::size_t has_maximized_index              = 8;
constexpr const std::size_t has_restored_from_maximize_index = 9;
constexpr const std::size_t has_gained_focus_index           = 10;
constexpr const std::size_t has_lost_focus_index             = 11;

void window::close() noexcept
{
  _window.reset();
}

void window::focus() noexcept
{
  glfwFocusWindow(get());
}

GLFWwindow *window::get() const noexcept
{
  return _window.get();
}

attribute window::get_attrib(attribute attribute) const noexcept
{
  return glfwGetWindowAttrib(get(), attribute);
}

scale window::get_content_scale() const noexcept
{
  float x, y;
  glfwGetWindowContentScale(get(), &x, &y);
  return scale{x, y};
}

dimensions window::get_framebuffer_size() const noexcept
{
  int x, y;
  glfwGetFramebufferSize(get(), &x, &y);
  return dimensions{static_cast<std::uint32_t>(y), static_cast<std::uint32_t>(y)};
}

distance window::get_frame_size() const noexcept
{
  int left, top, right, bottom;
  glfwGetWindowFrameSize(get(), &left, &top, &right, &bottom);
  return distance{static_cast<std::uint32_t>(left),
                  static_cast<std::uint32_t>(top),
                  static_cast<std::uint32_t>(right),
                  static_cast<std::uint32_t>(bottom)};
}

monitor window::get_monitor() const
{
  if(GLFWmonitor *ptr = glfwGetWindowMonitor(get()))
    return monitor(std::move(ptr));
  throw std::runtime_error("failed to get GLFWmonitor: window is not full-screen");
}

float window::get_opacity() const noexcept
{
  return glfwGetWindowOpacity(get());
}

coordinates window::get_position() const noexcept
{
  int x, y;
  glfwGetWindowPos(get(), &x, &y);
  return coordinates{static_cast<std::int32_t>(y), static_cast<std::int32_t>(y)};
}

dimensions window::get_size() const noexcept
{
  int x, y;
  glfwGetWindowSize(get(), &x, &y);
  return dimensions{static_cast<std::uint32_t>(y), static_cast<std::uint32_t>(y)};
}

bool window::has_content_scale_changed() noexcept
{
  return _flags[has_content_scale_changed_index] ? (_flags.set(has_content_scale_changed_index, false), true) : false;
}

bool window::has_framebuffer_resized() noexcept
{
  return _flags[has_framebuffer_resized_index] ? (_flags.set(has_framebuffer_resized_index, false), true) : false;
}

bool window::has_gained_focus() noexcept
{
  return _flags[has_gained_focus_index] ? (_flags.set(has_gained_focus_index, false), true) : false;
}

bool window::has_iconified() noexcept
{
  return _flags[has_iconified_index] ? (_flags.set(has_iconified_index, false), true) : false;
}

bool window::has_lost_focus() noexcept
{
  return _flags[has_lost_focus_index] ? (_flags.set(has_lost_focus_index, false), true) : false;
}

bool window::has_maximized() noexcept
{
  return _flags[has_maximized_index] ? (_flags.set(has_maximized_index, false), true) : false;
}

bool window::has_moved() noexcept
{
  return _flags[has_moved_index] ? (_flags.set(has_moved_index, false), true) : false;
}

bool window::has_resized() noexcept
{
  return _flags[has_resized_index] ? (_flags.set(has_resized_index, false), true) : false;
}

bool window::has_restored_from_iconify() noexcept
{
  return _flags[has_restored_from_iconify_index] ? (_flags.set(has_restored_from_iconify_index, false), true) : false;
}

bool window::has_restored_from_maximizes() noexcept
{
  return _flags[has_restored_from_maximize_index] ? (_flags.set(has_restored_from_maximize_index, false), true) : false;
}

void window::hide() noexcept
{
  glfwHideWindow(get());
}

void window::iconify() noexcept
{
  glfwIconifyWindow(get());
}

void window::maximize() noexcept
{
  glfwMaximizeWindow(get());
}

void window::request_attention() noexcept
{
  glfwRequestWindowAttention(get());
}

void window::restore() noexcept
{
  glfwRestoreWindow(get());
}

void window::set_aspect_ratio(dimensions ratio) noexcept
{
  glfwSetWindowAspectRatio(get(), static_cast<int>(ratio.width), static_cast<int>(ratio.height));
}

void window::set_attrib(attribute attribute, value value) noexcept
{
  glfwSetWindowAttrib(get(), attribute, value);
}

void window::set_icon(std::vector<GLFWimage> images)
{
  if(images.size() > std::numeric_limits<int>::max())
    throw std::out_of_range("failed to set icon: too many images");
  glfwSetWindowIcon(get(), static_cast<int>(images.size()), images.data());
}

void window::set_monitor(GLFWmonitor *monitor, coordinates position, dimensions size, int refreshRate) noexcept
{
  glfwSetWindowMonitor(get(),
                       monitor,
                       static_cast<int>(position.x),
                       static_cast<int>(position.y),
                       static_cast<int>(size.width),
                       static_cast<int>(size.height),
                       refreshRate);
}

void window::set_opacity(float opacity) noexcept
{
  glfwSetWindowOpacity(get(), opacity);
}

void window::set_position(coordinates position) noexcept
{
  glfwSetWindowPos(get(), static_cast<int>(position.x), static_cast<int>(position.y));
}

void window::set_size(dimensions size) noexcept
{
  glfwSetWindowSize(get(), static_cast<int>(size.width), static_cast<int>(size.height));
}

void window::set_size_limits(dimensions min_size, dimensions max_size) noexcept
{
  glfwSetWindowSizeLimits(get(),
                          static_cast<int>(min_size.width),
                          static_cast<int>(min_size.height),
                          static_cast<int>(max_size.width),
                          static_cast<int>(max_size.height));
}

void window::set_title(std::string const &title) noexcept
{
  glfwSetWindowTitle(get(), title.c_str());
}

bool window::should_close() noexcept
{
  return _flags[should_closed_index] ? (_flags.set(should_closed_index, false), true) : false;
}

bool window::should_refresh() noexcept
{
  return _flags[should_refresh_index] ? (_flags.set(should_refresh_index, false), true) : false;
}

void window::show() noexcept
{
}

window::window(GLFWwindow *&&window) noexcept
: _window(std::move(window))
{
  glfwSetWindowUserPointer(get(), this);

  glfwSetWindowCloseCallback(
    get(),
    [](GLFWwindow *window)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(should_closed_index, true); });

  glfwSetWindowRefreshCallback(
    get(),
    [](GLFWwindow *window)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(should_refresh_index, true); });

  glfwSetWindowPosCallback(
    get(),
    [](GLFWwindow *window, int, int)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_moved_index, true); });

  glfwSetWindowSizeCallback(
    get(),
    [](GLFWwindow *window, int, int)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_resized_index, true); });

  glfwSetFramebufferSizeCallback(
    get(),
    [](GLFWwindow *window, int, int)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_framebuffer_resized_index, true); });

  glfwSetWindowContentScaleCallback(
    get(),
    [](GLFWwindow *window, float, float)
    { reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_content_scale_changed_index, true); });

  glfwSetWindowIconifyCallback(
    get(),
    [](GLFWwindow *window, int has_iconified)
    {
      reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))
        ->_flags.set(has_iconified == GLFW_TRUE ? has_iconified_index : has_restored_from_iconify_index, true);
    });

  glfwSetWindowMaximizeCallback(
    get(),
    [](GLFWwindow *window, int has_maximized)
    {
      reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))
        ->_flags.set(has_maximized == GLFW_TRUE ? has_maximized_index : has_restored_from_maximize_index, true);
    });

  glfwSetWindowFocusCallback(get(),
                             [](GLFWwindow *window, int has_gained_focus)
                             {
                               reinterpret_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                 ->_flags.set(has_gained_focus == GLFW_TRUE ? has_gained_focus_index : has_lost_focus_index,
                                              true);
                             });
}
}
