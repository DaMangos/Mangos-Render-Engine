#include "../structs/internal/to_modifiers.hpp"

#include <glfw/enums/action.hpp>
#include <glfw/enums/mouse_button.hpp>
#include <glfw/except/bad_window_access.hpp>
#include <glfw/handles/cursor.hpp>
#include <glfw/handles/library.hpp>
#include <glfw/handles/monitor.hpp>
#include <glfw/handles/window.hpp>

#include <source_location>
#include <string>

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

void mouse_button_callback(GLFWwindow * window, int mouse_button, int action, int mods)
{
  auto * const glfw_window = static_cast<glfw::window *>(glfwGetWindowUserPointer(window));
  if(glfw_window and glfw_window->on_mouse_button_action)
    glfw_window->on_mouse_button_action(*glfw_window,
                                        static_cast<glfw::mouse_button>(mouse_button),
                                        static_cast<glfw::action>(action),
                                        glfw::internal::to_modifiers(mods));
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
    glfw_window->on_key_action(*glfw_window,
                               scancode,
                               static_cast<glfw::key>(key),
                               static_cast<glfw::action>(action),
                               glfw::internal::to_modifiers(mods));
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

glfw::coordinates<int> glfw::window::get_position() const
{
  int xpos = {}, ypos = {};
  _window ? glfwGetWindowPos(_window.get(), &xpos, &ypos) : throw bad_window_access();
  return {xpos, ypos};
}

glfw::extent<int> glfw::window::get_size() const
{
  int width = {}, height = {};
  _window ? glfwGetWindowSize(_window.get(), &width, &height) : throw bad_window_access();
  return {width, height};
}

glfw::extent<glfw::pixel> glfw::window::get_framebuffer_size() const
{
  int width = {}, height = {};
  _window ? glfwGetFramebufferSize(_window.get(), &width, &height) : throw bad_window_access();
  return {static_cast<glfw::pixel>(width), static_cast<glfw::pixel>(height)};
}

glfw::scale<float> glfw::window::get_content_scale() const
{
  float xscale = {}, yscale = {};
  _window ? glfwGetWindowContentScale(_window.get(), &xscale, &yscale) : throw bad_window_access();
  return {xscale, yscale};
}

std::string glfw::window::get_title() const
{
  return _window ? glfwGetWindowTitle(_window.get()) : throw bad_window_access();
}

std::string glfw::window::get_clipboard() const
{
  return _window ? glfwGetClipboardString(_window.get()) : throw bad_window_access();
}

glfw::monitor glfw::window::get_monitor() const
{
  return _window ? monitor(glfwGetWindowMonitor(_window.get()), *_library) : throw bad_window_access();
}

float glfw::window::get_opacity() const
{
  return _window ? glfwGetWindowOpacity(_window.get()) : throw bad_window_access();
}

bool glfw::window::are_framebuffers_transparent() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_TRANSPARENT_FRAMEBUFFER) : throw bad_window_access();
}

bool glfw::window::is_closed() const noexcept
{
  return static_cast<bool>(_window);
}

bool glfw::window::is_maximized() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_MAXIMIZED) : throw bad_window_access();
}

bool glfw::window::is_minimized() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_ICONIFIED) : throw bad_window_access();
}

bool glfw::window::is_restored() const
{
  return not is_maximized() and not is_minimized();
}

bool glfw::window::is_visible() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_VISIBLE) : throw bad_window_access();
}

bool glfw::window::is_cursor_hovered() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_HOVERED) : throw bad_window_access();
}

bool glfw::window::is_resizeable() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_RESIZABLE) : throw bad_window_access();
}

bool glfw::window::is_decorated() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_DECORATED) : throw bad_window_access();
}

bool glfw::window::is_auto_iconify() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_AUTO_ICONIFY) : throw bad_window_access();
}

bool glfw::window::is_floating() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_FLOATING) : throw bad_window_access();
}

bool glfw::window::is_framebuffer_transparent() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_TRANSPARENT_FRAMEBUFFER) : throw bad_window_access();
}

bool glfw::window::is_focus_on_show() const
{
  return _window ? glfwGetWindowAttrib(_window.get(), GLFW_FOCUS_ON_SHOW) : throw bad_window_access();
}

bool glfw::window::should_close() const
{
  return _window ? glfwWindowShouldClose(_window.get()) : throw bad_window_access();
}

void glfw::window::close() noexcept
{
  reset();
}

void glfw::window::focus()
{
  return _window ? glfwFocusWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::hide()
{
  return _window ? glfwHideWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::maximize()
{
  return _window ? glfwMaximizeWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::iconify()
{
  return _window ? glfwIconifyWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::request_attention()
{
  return _window ? glfwRequestWindowAttention(_window.get()) : throw bad_window_access();
}

void glfw::window::reset_aspect_ratio()
{
  return _window ? glfwSetWindowAspectRatio(_window.get(), GLFW_DONT_CARE, GLFW_DONT_CARE) : throw bad_window_access();
}

void glfw::window::reset_size_limits()
{
  return _window ? glfwSetWindowSizeLimits(_window.get(), GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE) : throw bad_window_access();
}

void glfw::window::restore()
{
  return _window ? glfwRestoreWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::set_aspect_ratio(extent<int> const & aspect_ratio)
{
  return _window ? glfwSetWindowAspectRatio(_window.get(), aspect_ratio.width, aspect_ratio.height) : throw bad_window_access();
}

void glfw::window::set_cursor(cursor const & cursor)
{
  return _window ? glfwSetCursor(_window.get(), cursor.get()) : throw bad_window_access();
}

void glfw::window::set_icon(std::span<image> const icons)
{
  using namespace std::string_literals;

  if(_window)
    throw bad_window_access();

  if(icons.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
    throw std::length_error(std::source_location::current().function_name() + ": too many images"s);

  std::vector<GLFWimage> images;
  std::ranges::transform(icons,
                         std::back_inserter(images),
                         [](auto & icon)
                         { return GLFWimage{icon.size.width, icon.size.height, reinterpret_cast<unsigned char *>(icon.pixels.data())}; });

  glfwSetWindowIcon(_window.get(), static_cast<int>(images.size()), images.data());
}

void glfw::window::set_opacity(float const alpha)
{
  return _window ? glfwSetWindowOpacity(_window.get(), alpha) : throw bad_window_access();
}

void glfw::window::set_position(coordinates<int> const & position)
{
  return _window ? glfwSetWindowPos(_window.get(), position.x, position.y) : throw bad_window_access();
}

void glfw::window::set_size(extent<int> const & size)
{
  return _window ? glfwSetWindowSize(_window.get(), size.width, size.height) : throw bad_window_access();
}

void glfw::window::set_size_limits(extent<int> const & min_size, extent<int> const & max_size)
{
  return _window ? glfwSetWindowSizeLimits(_window.get(), min_size.width, min_size.height, max_size.width, max_size.height)
                 : throw bad_window_access();
}

void glfw::window::set_title(std::string const & title)
{
  return _window ? glfwSetWindowTitle(_window.get(), title.c_str()) : throw bad_window_access();
}

void glfw::window::set_clipboard(std::string const & clipboard)
{
  return _window ? glfwSetClipboardString(_window.get(), clipboard.c_str()) : throw bad_window_access();
}

void glfw::window::show()
{
  return _window ? glfwShowWindow(_window.get()) : throw bad_window_access();
}

void glfw::window::swap_buffers()
{
  return _window ? glfwSwapBuffers(_window.get()) : throw bad_window_access();
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
