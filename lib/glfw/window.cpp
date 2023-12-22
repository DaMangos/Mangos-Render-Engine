#include "window.hpp"

namespace
{
constexpr std::size_t const should_closed_index              = 0;
constexpr std::size_t const should_refresh_index             = 1;
constexpr std::size_t const has_moved_index                  = 2;
constexpr std::size_t const has_resized_index                = 3;
constexpr std::size_t const has_framebuffer_resized_index    = 4;
constexpr std::size_t const has_content_scale_changed_index  = 5;
constexpr std::size_t const has_iconified_index              = 6;
constexpr std::size_t const has_restored_from_iconify_index  = 7;
constexpr std::size_t const has_maximized_index              = 8;
constexpr std::size_t const has_restored_from_maximize_index = 9;
constexpr std::size_t const has_gained_focus_index           = 10;
constexpr std::size_t const has_lost_focus_index             = 11;
}

namespace glfw
{
window::window(dimensions const &size, std::string const &title)
: _handle(
    [&size, &title]()
    {
      if(auto *const ptr =
           glfwCreateWindow(static_cast<int>(size.width), static_cast<int>(size.height), title.c_str(), nullptr, nullptr))
        return ptr;
      throw std::runtime_error("failed to create GLFWwindow");
    }())
{
  glfwSetWindowUserPointer(get(), this);
  glfwSetWindowCloseCallback(
    get(),
    [](GLFWwindow *window)
    { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(should_closed_index, true); });

  glfwSetWindowRefreshCallback(
    get(),
    [](GLFWwindow *window)
    { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(should_refresh_index, true); });

  glfwSetWindowPosCallback(get(),
                           [](GLFWwindow *const window, int const, int const) {
                             static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_moved_index, true);
                           });

  glfwSetWindowSizeCallback(
    get(),
    [](GLFWwindow *const window, int const, int const)
    { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_resized_index, true); });

  glfwSetFramebufferSizeCallback(
    get(),
    [](GLFWwindow *const window, int const, int const)
    { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_framebuffer_resized_index, true); });

  glfwSetWindowContentScaleCallback(
    get(),
    [](GLFWwindow *const window, float const, float const)
    { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->_flags.set(has_content_scale_changed_index, true); });

  glfwSetWindowIconifyCallback(
    get(),
    [](GLFWwindow *window, int has_iconified)
    {
      static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
        ->_flags.set(has_iconified == GLFW_TRUE ? has_iconified_index : has_restored_from_iconify_index, true);
    });

  glfwSetWindowMaximizeCallback(
    get(),
    [](GLFWwindow *const window, int const has_maximized)
    {
      static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
        ->_flags.set(has_maximized == GLFW_TRUE ? has_maximized_index : has_restored_from_maximize_index, true);
    });

  glfwSetWindowFocusCallback(get(),
                             [](GLFWwindow *const window, int const has_gained_focus)
                             {
                               static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                 ->_flags.set(has_gained_focus == GLFW_TRUE ? has_gained_focus_index : has_lost_focus_index,
                                              true);
                             });
}

attribute window::get_attrib(attribute attribute) const noexcept
{
  return glfwGetWindowAttrib(get(), attribute);
}

scale window::get_content_scale() const noexcept
{
  float x = 0.f, y = 0.f;
  glfwGetWindowContentScale(get(), &x, &y);
  return scale{x, y};
}

dimensions window::get_framebuffer_size() const noexcept
{
  int x = 0, y = 0;
  glfwGetFramebufferSize(get(), &x, &y);
  return dimensions{static_cast<std::uint16_t>(y), static_cast<std::uint32_t>(y)};
}

distance window::get_frame_size() const noexcept
{
  int left = 0, top = 0, right = 0, bottom = 0;
  glfwGetWindowFrameSize(get(), &left, &top, &right, &bottom);
  return distance{static_cast<std::uint32_t>(left),
                  static_cast<std::uint32_t>(top),
                  static_cast<std::uint32_t>(right),
                  static_cast<std::uint32_t>(bottom)};
}

float window::get_opacity() const noexcept
{
  return glfwGetWindowOpacity(get());
}

coordinates window::get_position() const noexcept
{
  int x = 0, y = 0;
  glfwGetWindowPos(get(), &x, &y);
  return coordinates{static_cast<std::int32_t>(y), static_cast<std::int32_t>(y)};
}

dimensions window::get_size() const noexcept
{
  int x = 0, y = 0;
  glfwGetWindowSize(get(), &x, &y);
  return dimensions{static_cast<std::uint32_t>(y), static_cast<std::uint32_t>(y)};
}

bool window::has_content_scale_changed() const noexcept
{
  return _flags[has_content_scale_changed_index] ? (_flags.set(has_content_scale_changed_index, false), true) : false;
}

bool window::has_framebuffer_resized() const noexcept
{
  return _flags[has_framebuffer_resized_index] ? (_flags.set(has_framebuffer_resized_index, false), true) : false;
}

bool window::has_gained_focus() const noexcept
{
  return _flags[has_gained_focus_index] ? (_flags.set(has_gained_focus_index, false), true) : false;
}

bool window::has_iconified() const noexcept
{
  return _flags[has_iconified_index] ? (_flags.set(has_iconified_index, false), true) : false;
}

bool window::has_lost_focus() const noexcept
{
  return _flags[has_lost_focus_index] ? (_flags.set(has_lost_focus_index, false), true) : false;
}

bool window::has_maximized() const noexcept
{
  return _flags[has_maximized_index] ? (_flags.set(has_maximized_index, false), true) : false;
}

bool window::has_moved() const noexcept
{
  return _flags[has_moved_index] ? (_flags.set(has_moved_index, false), true) : false;
}

bool window::has_resized() const noexcept
{
  return _flags[has_resized_index] ? (_flags.set(has_resized_index, false), true) : false;
}

bool window::has_restored_from_iconify() const noexcept
{
  return _flags[has_restored_from_iconify_index] ? (_flags.set(has_restored_from_iconify_index, false), true) : false;
}

bool window::has_restored_from_maximize() const noexcept
{
  return _flags[has_restored_from_maximize_index] ? (_flags.set(has_restored_from_maximize_index, false), true) : false;
}

bool window::should_close() const noexcept
{
  return _flags[should_closed_index] ? (_flags.set(should_closed_index, false), true) : false;
}

bool window::should_refresh() const noexcept
{
  return _flags[should_refresh_index] ? (_flags.set(should_refresh_index, false), true) : false;
}

void window::close() noexcept
{
  _handle.reset();
}

void window::focus() noexcept
{
  glfwFocusWindow(get());
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

void window::show() noexcept
{
  glfwShowWindow(get());
}

void window::set_aspect_ratio(dimensions const &ratio) noexcept
{
  glfwSetWindowAspectRatio(get(), static_cast<int>(ratio.width), static_cast<int>(ratio.height));
}

void window::set_attrib(attribute const attribute, value const value) noexcept
{
  glfwSetWindowAttrib(get(), attribute, value);
}

void window::set_opacity(float const opacity) noexcept
{
  glfwSetWindowOpacity(get(), opacity);
}

void window::set_position(coordinates const &position) noexcept
{
  glfwSetWindowPos(get(), static_cast<int>(position.x), static_cast<int>(position.y));
}

void window::set_size(dimensions const &size) noexcept
{
  glfwSetWindowSize(get(), static_cast<int>(size.width), static_cast<int>(size.height));
}

void window::set_size_limits(dimensions const &min_size, dimensions const &max_size) noexcept
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
}

bool operator==(glfw::window const &lhs, glfw::window const &rhs) noexcept
{
  return lhs.get() == rhs.get();
}

bool operator!=(glfw::window const &lhs, glfw::window const &rhs) noexcept
{
  return !(lhs == rhs);
}
