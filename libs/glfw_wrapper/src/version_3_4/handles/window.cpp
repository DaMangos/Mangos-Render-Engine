#include "../enums/to_action.hpp"
#include "../enums/to_key.hpp"
#include "../enums/to_mouse_button.hpp"
#include "../structs/to_modifiers.hpp"

#include <glfw_wrapper/version_3_4/handles/cursor.hpp>
#include <glfw_wrapper/version_3_4/handles/library.hpp>
#include <glfw_wrapper/version_3_4/handles/monitor.hpp>
#include <glfw_wrapper/version_3_4/handles/window.hpp>

#include <cassert>
#include <exception>
#include <iterator>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
void window_pos_callback(GLFWwindow * window, int xpos, int ypos)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_position_update)
    glfw_window->on_position_update(*glfw_window, {xpos, ypos});
}

void window_size_callback(GLFWwindow * window, int width, int height)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_size_update)
    glfw_window->on_size_update(*glfw_window, {width, height});
}

void window_close_callback(GLFWwindow * window)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_close)
    glfw_window->on_close(*glfw_window);
}

void window_refresh_callback(GLFWwindow * window)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_refresh_required)
    glfw_window->on_refresh_required(*glfw_window);
}

void window_focus_callback(GLFWwindow * window, int focused)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_focus_update)
    glfw_window->on_focus_update(*glfw_window, focused == GLFW_TRUE ? glfw::window::focused_state::gained : glfw::window::focused_state::lost);
}

void window_iconify_callback(GLFWwindow * window, int iconified)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_iconify_update)
    glfw_window->on_iconify_update(*glfw_window,
                                   iconified == GLFW_TRUE ? glfw::window::iconified_state::iconified : glfw::window::iconified_state::restored);
}

void window_maximize_callback(GLFWwindow * window, int maximized)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_maximize_update)
    glfw_window->on_maximize_update(*glfw_window,
                                    maximized == GLFW_TRUE ? glfw::window::maximized_state::maximized : glfw::window::maximized_state::restored);
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_framebuffer_size_update)
    glfw_window->on_framebuffer_size_update(*glfw_window, {static_cast<glfw::pixel>(width), static_cast<glfw::pixel>(height)});
}

void window_content_scale_callback(GLFWwindow * window, float xscale, float yscale)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_content_scale_update)
    glfw_window->on_content_scale_update(*glfw_window, {xscale, yscale});
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_mouse_button_action)
    glfw_window->on_mouse_button_action(*glfw_window, glfw::to_mouse_button(button), glfw::to_action(action), glfw::to_modifiers(mods));
}

void cursor_pos_callback(GLFWwindow * window, double xpos, double ypos)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_cursor_position_update)
    glfw_window->on_cursor_position_update(*glfw_window, {xpos, ypos});
}

void cursor_enter_callback(GLFWwindow * window, int entered)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_cursor_location_update)
    glfw_window->on_cursor_location_update(*glfw_window,
                                           entered == GLFW_TRUE ? glfw::window::cursor_location_state::entered_window
                                                                : glfw::window::cursor_location_state::exited_window);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_scroll_update)
    glfw_window->on_scroll_update(*glfw_window, {xoffset, yoffset});
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_key_action)
    glfw_window->on_key_action(*glfw_window, scancode, glfw::to_key(key), glfw::to_action(action), glfw::to_modifiers(mods));
}

void char_callback(GLFWwindow * window, unsigned int codepoint)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_char_input)
    glfw_window->on_char_input(*glfw_window, codepoint);
}

void drop_callback(GLFWwindow * window, int path_count, char const ** paths)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_file_drop)
    glfw_window->on_file_drop(*glfw_window, std::vector<std::filesystem::path>(paths, std::ranges::next(paths, path_count)));
}
}

GLFWwindow * glfw::window::get() const noexcept
{
  return _window.get();
}

glfw::coordinates<int> glfw::window::get_position() const noexcept
{
  int xpos = {}, ypos = {};
  if(_window)
    glfwGetWindowPos(_window.get(), &xpos, &ypos);
  return {xpos, ypos};
}

glfw::extent<int> glfw::window::get_size() const noexcept
{
  int width = {}, height = {};
  if(_window)
    glfwGetWindowSize(_window.get(), &width, &height);
  return {width, height};
}

glfw::extent<glfw::pixel> glfw::window::get_framebuffer_size() const noexcept
{
  int width = {}, height = {};
  if(_window)
    glfwGetFramebufferSize(_window.get(), &width, &height);
  return {static_cast<glfw::pixel>(width), static_cast<glfw::pixel>(height)};
}

glfw::scale<float> glfw::window::get_content_scale() const noexcept
{
  float xscale = {}, yscale = {};
  if(_window)
    glfwGetWindowContentScale(_window.get(), &xscale, &yscale);
  return {xscale, yscale};
}

std::string glfw::window::get_title() const noexcept
{
  try
  {
    return _window ? glfwGetWindowTitle(_window.get()) : std::string();
  }
  catch(std::exception const &)
  {
    return {};
  }
}

std::string glfw::window::get_clipboard() const noexcept
{
  try
  {
    return _window ? glfwGetClipboardString(_window.get()) : std::string();
  }
  catch(std::exception const &)
  {
    return {};
  }
}

glfw::monitor glfw::window::get_monitor() const noexcept
{
  return _window ? monitor(glfwGetWindowMonitor(_window.get()), *_library) : nullhandle;
}

float glfw::window::get_opacity() const noexcept
{
  return _window ? glfwGetWindowOpacity(_window.get()) : 0.0f;
}

bool glfw::window::are_framebuffers_transparent() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_TRANSPARENT_FRAMEBUFFER) : false;
}

bool glfw::window::is_closed() const noexcept
{
  return static_cast<bool>(_window);
}

bool glfw::window::is_maximized() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_MAXIMIZED) : false;
}

bool glfw::window::is_minimized() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_ICONIFIED) : false;
}

bool glfw::window::is_restored() const noexcept
{
  return not is_maximized() and not is_minimized();
}

bool glfw::window::is_visible() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_VISIBLE) : false;
}

bool glfw::window::is_cursor_hovered() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_HOVERED) : false;
}

bool glfw::window::is_resizeable() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_RESIZABLE) : false;
}

bool glfw::window::is_decorated() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_DECORATED) : false;
}

bool glfw::window::is_auto_iconify() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_AUTO_ICONIFY) : false;
}

bool glfw::window::is_floating() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_FLOATING) : false;
}

bool glfw::window::is_framebuffer_transparent() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_TRANSPARENT_FRAMEBUFFER) : false;
}

bool glfw::window::is_focus_on_show() const noexcept
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_FOCUS_ON_SHOW) : false;
}

bool glfw::window::should_close() const noexcept
{
  return _window ? glfwWindowShouldClose(_window.get()) : false;
}

void glfw::window::close() noexcept
{
  reset();
}

void glfw::window::focus() noexcept
{
  if(_window)
    glfwFocusWindow(_window.get());
}

void glfw::window::hide() noexcept
{
  if(_window)
    glfwHideWindow(_window.get());
}

void glfw::window::maximize() noexcept
{
  if(_window)
    glfwMaximizeWindow(_window.get());
}

void glfw::window::iconify() noexcept
{
  if(_window)
    glfwIconifyWindow(_window.get());
}

void glfw::window::request_attention() noexcept
{
  if(_window)
    glfwRequestWindowAttention(_window.get());
}

void glfw::window::reset_aspect_ratio() noexcept
{
  if(_window)
    glfwSetWindowAspectRatio(_window.get(), GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void glfw::window::reset_size_limits() noexcept
{
  if(_window)
    glfwSetWindowSizeLimits(_window.get(), GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void glfw::window::restore() noexcept
{
  if(_window)
    glfwRestoreWindow(_window.get());
}

void glfw::window::set_aspect_ratio(extent<int> const & aspect_ratio) noexcept
{
  if(_window)
    glfwSetWindowAspectRatio(_window.get(), aspect_ratio.width, aspect_ratio.height);
}

void glfw::window::set_cursor(cursor const & cursor) noexcept
{
  if(_window)
    glfwSetCursor(_window.get(), cursor.get());
}

void glfw::window::set_icon(std::span<image> const icons) noexcept
{
  try
  {
    std::vector<GLFWimage> images;
    std::ranges::transform(icons,
                           std::back_inserter(images),
                           [](auto & icon)
                           { return GLFWimage{icon.size.width, icon.size.height, reinterpret_cast<unsigned char *>(icon.pixels.data())}; });

    if(_window and images.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()))
      glfwSetWindowIcon(_window.get(), static_cast<int>(images.size()), images.data());
  }
  catch(std::exception const &)
  {
  }
}

void glfw::window::set_opacity(float const alpha) noexcept
{
  if(_window)
    glfwSetWindowOpacity(_window.get(), alpha);
}

void glfw::window::set_position(coordinates<int> const & position) noexcept
{
  if(_window)
    glfwSetWindowPos(_window.get(), position.x, position.y);
}

void glfw::window::set_size(extent<int> const & size) noexcept
{
  if(_window)
    glfwSetWindowSize(_window.get(), size.width, size.height);
}

void glfw::window::set_size_limits(extent<int> const & min_size, extent<int> const & max_size) noexcept
{
  if(_window)
    glfwSetWindowSizeLimits(_window.get(), min_size.width, min_size.height, max_size.width, max_size.height);
}

void glfw::window::set_title(std::string const & title) noexcept
{
  if(_window)
    glfwSetWindowTitle(_window.get(), title.c_str());
}

void glfw::window::set_clipboard(std::string const & clipboard) noexcept
{
  if(_window)
    glfwSetClipboardString(_window.get(), clipboard.c_str());
}

void glfw::window::show() noexcept
{
  if(_window)
    glfwShowWindow(_window.get());
}

void glfw::window::swap_buffers() noexcept
{
  if(_window)
    glfwSwapBuffers(_window.get());
}

void glfw::window::reset() noexcept
{
  on_position_update         = nullptr;
  on_size_update             = nullptr;
  on_close                   = nullptr;
  on_refresh_required        = nullptr;
  on_focus_update            = nullptr;
  on_iconify_update          = nullptr;
  on_maximize_update         = nullptr;
  on_framebuffer_size_update = nullptr;
  on_content_scale_update    = nullptr;
  on_mouse_button_action     = nullptr;
  on_cursor_position_update  = nullptr;
  on_cursor_location_update  = nullptr;
  on_scroll_update           = nullptr;
  on_key_action              = nullptr;
  on_char_input              = nullptr;
  on_file_drop               = nullptr;
  _window.reset();
}

glfw::window::window() noexcept
: _library(std::nullopt),
  _window(nullptr, glfwDestroyWindow)
{
}

glfw::window::window(nullhandle_t) noexcept
: _library(std::nullopt),
  _window(nullptr, glfwDestroyWindow)
{
}

glfw::window::window(window && other) noexcept
: on_position_update(std::move(other.on_position_update)),
  on_size_update(std::move(other.on_size_update)),
  on_close(std::move(other.on_close)),
  on_refresh_required(std::move(other.on_refresh_required)),
  on_focus_update(std::move(other.on_focus_update)),
  on_iconify_update(std::move(other.on_iconify_update)),
  on_maximize_update(std::move(other.on_maximize_update)),
  on_framebuffer_size_update(std::move(other.on_framebuffer_size_update)),
  on_content_scale_update(std::move(other.on_content_scale_update)),
  on_mouse_button_action(std::move(other.on_mouse_button_action)),
  on_cursor_position_update(std::move(other.on_cursor_position_update)),
  on_cursor_location_update(std::move(other.on_cursor_location_update)),
  on_scroll_update(std::move(other.on_scroll_update)),
  on_key_action(std::move(other.on_key_action)),
  on_char_input(std::move(other.on_char_input)),
  on_file_drop(std::move(other.on_file_drop)),
  _library(std::move(other._library)),
  _window(std::move(other._window))
{
  if(_window)
    glfwSetWindowUserPointer(_window.get(), this);
}

glfw::window & glfw::window::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

glfw::window & glfw::window::operator=(window && other) noexcept
{
  on_position_update         = std::move(other.on_position_update);
  on_size_update             = std::move(other.on_size_update);
  on_close                   = std::move(other.on_close);
  on_refresh_required        = std::move(other.on_refresh_required);
  on_focus_update            = std::move(other.on_focus_update);
  on_iconify_update          = std::move(other.on_iconify_update);
  on_maximize_update         = std::move(other.on_maximize_update);
  on_framebuffer_size_update = std::move(other.on_framebuffer_size_update);
  on_content_scale_update    = std::move(other.on_content_scale_update);
  on_mouse_button_action     = std::move(other.on_mouse_button_action);
  on_cursor_position_update  = std::move(other.on_cursor_position_update);
  on_cursor_location_update  = std::move(other.on_cursor_location_update);
  on_scroll_update           = std::move(other.on_scroll_update);
  on_key_action              = std::move(other.on_key_action);
  on_char_input              = std::move(other.on_char_input);
  on_file_drop               = std::move(other.on_file_drop);
  _library                   = std::move(other._library);
  _window                    = std::move(other._window);

  if(_window)
    glfwSetWindowUserPointer(_window.get(), this);

  return *this;
}

std::strong_ordering glfw::window::operator<=>(nullhandle_t) const noexcept
{
  return _window <=> nullptr;
}

std::strong_ordering glfw::window::operator<=>(window const & other) const noexcept
{
  return _window <=> other._window;
}

glfw::window::operator bool() const noexcept
{
  return static_cast<bool>(_window);
}

glfw::window::window(GLFWwindow * const window, library const library) noexcept
: _library(std::nullopt),
  _window(window, glfwDestroyWindow)
{
  if(_window)
  {
    _library.emplace(library);
    glfwSetWindowUserPointer(_window.get(), this);
    glfwSetWindowPosCallback(_window.get(), &window_pos_callback);
    glfwSetWindowSizeCallback(_window.get(), &window_size_callback);
    glfwSetWindowCloseCallback(_window.get(), &window_close_callback);
    glfwSetWindowRefreshCallback(_window.get(), &window_refresh_callback);
    glfwSetWindowFocusCallback(_window.get(), &window_focus_callback);
    glfwSetWindowIconifyCallback(_window.get(), &window_iconify_callback);
    glfwSetWindowMaximizeCallback(_window.get(), &window_maximize_callback);
    glfwSetFramebufferSizeCallback(_window.get(), &framebuffer_size_callback);
    glfwSetWindowContentScaleCallback(_window.get(), &window_content_scale_callback);
    glfwSetMouseButtonCallback(_window.get(), &mouse_button_callback);
    glfwSetCursorPosCallback(_window.get(), &cursor_pos_callback);
    glfwSetCursorEnterCallback(_window.get(), &cursor_enter_callback);
    glfwSetScrollCallback(_window.get(), &scroll_callback);
    glfwSetKeyCallback(_window.get(), &key_callback);
    glfwSetCharCallback(_window.get(), &char_callback);
    glfwSetDropCallback(_window.get(), &drop_callback);
  }
}
