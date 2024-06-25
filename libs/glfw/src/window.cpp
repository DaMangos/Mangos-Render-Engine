#include <glfw/handles/library.hpp>
#include <glfw/handles/monitor.hpp>
#include <glfw/handles/window.hpp>
#include <glfw/input/action.hpp>

#include <cassert>
#include <exception>
#include <iterator>
#include <limits>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
[[nodiscard]]
constexpr glfw::key to_key(int const key)
{
  switch(key)
  {
    case(GLFW_KEY_SPACE) :
      return glfw::key::Space;
    case(GLFW_KEY_APOSTROPHE) :
      return glfw::key::Apostrophe;
    case(GLFW_KEY_COMMA) :
      return glfw::key::Comma;
    case(GLFW_KEY_MINUS) :
      return glfw::key::Minus;
    case(GLFW_KEY_PERIOD) :
      return glfw::key::Period;
    case(GLFW_KEY_SLASH) :
      return glfw::key::Slash;
    case(GLFW_KEY_0) :
      return glfw::key::Number_0;
    case(GLFW_KEY_1) :
      return glfw::key::Number_1;
    case(GLFW_KEY_2) :
      return glfw::key::Number_2;
    case(GLFW_KEY_3) :
      return glfw::key::Number_3;
    case(GLFW_KEY_4) :
      return glfw::key::Number_4;
    case(GLFW_KEY_5) :
      return glfw::key::Number_5;
    case(GLFW_KEY_6) :
      return glfw::key::Number_6;
    case(GLFW_KEY_7) :
      return glfw::key::Number_7;
    case(GLFW_KEY_8) :
      return glfw::key::Number_8;
    case(GLFW_KEY_9) :
      return glfw::key::Number_9;
    case(GLFW_KEY_SEMICOLON) :
      return glfw::key::Semicolon;
    case(GLFW_KEY_EQUAL) :
      return glfw::key::Equal;
    case(GLFW_KEY_A) :
      return glfw::key::A;
    case(GLFW_KEY_B) :
      return glfw::key::B;
    case(GLFW_KEY_C) :
      return glfw::key::C;
    case(GLFW_KEY_D) :
      return glfw::key::D;
    case(GLFW_KEY_E) :
      return glfw::key::E;
    case(GLFW_KEY_F) :
      return glfw::key::F;
    case(GLFW_KEY_G) :
      return glfw::key::G;
    case(GLFW_KEY_H) :
      return glfw::key::H;
    case(GLFW_KEY_I) :
      return glfw::key::I;
    case(GLFW_KEY_J) :
      return glfw::key::J;
    case(GLFW_KEY_K) :
      return glfw::key::K;
    case(GLFW_KEY_L) :
      return glfw::key::L;
    case(GLFW_KEY_M) :
      return glfw::key::M;
    case(GLFW_KEY_N) :
      return glfw::key::N;
    case(GLFW_KEY_O) :
      return glfw::key::O;
    case(GLFW_KEY_P) :
      return glfw::key::P;
    case(GLFW_KEY_Q) :
      return glfw::key::Q;
    case(GLFW_KEY_R) :
      return glfw::key::R;
    case(GLFW_KEY_S) :
      return glfw::key::S;
    case(GLFW_KEY_T) :
      return glfw::key::T;
    case(GLFW_KEY_U) :
      return glfw::key::U;
    case(GLFW_KEY_V) :
      return glfw::key::V;
    case(GLFW_KEY_W) :
      return glfw::key::W;
    case(GLFW_KEY_X) :
      return glfw::key::X;
    case(GLFW_KEY_Y) :
      return glfw::key::Y;
    case(GLFW_KEY_Z) :
      return glfw::key::Z;
    case(GLFW_KEY_LEFT_BRACKET) :
      return glfw::key::Left_Bracket;
    case(GLFW_KEY_BACKSLASH) :
      return glfw::key::Backslash;
    case(GLFW_KEY_RIGHT_BRACKET) :
      return glfw::key::Right_Bracket;
    case(GLFW_KEY_GRAVE_ACCENT) :
      return glfw::key::Grave_Accent;
    case(GLFW_KEY_WORLD_1) :
      return glfw::key::World_1;
    case(GLFW_KEY_WORLD_2) :
      return glfw::key::World_2;
    case(GLFW_KEY_ESCAPE) :
      return glfw::key::Escape;
    case(GLFW_KEY_ENTER) :
      return glfw::key::Enter;
    case(GLFW_KEY_TAB) :
      return glfw::key::Tab;
    case(GLFW_KEY_BACKSPACE) :
      return glfw::key::Backspace;
    case(GLFW_KEY_INSERT) :
      return glfw::key::Insert;
    case(GLFW_KEY_DELETE) :
      return glfw::key::Delete;
    case(GLFW_KEY_RIGHT) :
      return glfw::key::Right;
    case(GLFW_KEY_LEFT) :
      return glfw::key::Left;
    case(GLFW_KEY_DOWN) :
      return glfw::key::Down;
    case(GLFW_KEY_UP) :
      return glfw::key::UP;
    case(GLFW_KEY_PAGE_UP) :
      return glfw::key::Page_Up;
    case(GLFW_KEY_PAGE_DOWN) :
      return glfw::key::Page_Down;
    case(GLFW_KEY_HOME) :
      return glfw::key::Home;
    case(GLFW_KEY_END) :
      return glfw::key::End;
    case(GLFW_KEY_CAPS_LOCK) :
      return glfw::key::Caps_Lock;
    case(GLFW_KEY_SCROLL_LOCK) :
      return glfw::key::Scroll_Lock;
    case(GLFW_KEY_NUM_LOCK) :
      return glfw::key::Num_Lock;
    case(GLFW_KEY_PRINT_SCREEN) :
      return glfw::key::Print_Screen;
    case(GLFW_KEY_PAUSE) :
      return glfw::key::Pause;
    case(GLFW_KEY_F1) :
      return glfw::key::F1;
    case(GLFW_KEY_F2) :
      return glfw::key::F2;
    case(GLFW_KEY_F3) :
      return glfw::key::F3;
    case(GLFW_KEY_F4) :
      return glfw::key::F4;
    case(GLFW_KEY_F5) :
      return glfw::key::F5;
    case(GLFW_KEY_F6) :
      return glfw::key::F6;
    case(GLFW_KEY_F7) :
      return glfw::key::F7;
    case(GLFW_KEY_F8) :
      return glfw::key::F8;
    case(GLFW_KEY_F9) :
      return glfw::key::F9;
    case(GLFW_KEY_F10) :
      return glfw::key::F10;
    case(GLFW_KEY_F11) :
      return glfw::key::F11;
    case(GLFW_KEY_F12) :
      return glfw::key::F12;
    case(GLFW_KEY_F13) :
      return glfw::key::F13;
    case(GLFW_KEY_F14) :
      return glfw::key::F14;
    case(GLFW_KEY_F15) :
      return glfw::key::F15;
    case(GLFW_KEY_F16) :
      return glfw::key::F16;
    case(GLFW_KEY_F17) :
      return glfw::key::F17;
    case(GLFW_KEY_F18) :
      return glfw::key::F18;
    case(GLFW_KEY_F19) :
      return glfw::key::F19;
    case(GLFW_KEY_F20) :
      return glfw::key::F20;
    case(GLFW_KEY_F21) :
      return glfw::key::F21;
    case(GLFW_KEY_F22) :
      return glfw::key::F22;
    case(GLFW_KEY_F23) :
      return glfw::key::F23;
    case(GLFW_KEY_F24) :
      return glfw::key::F24;
    case(GLFW_KEY_F25) :
      return glfw::key::F25;
    case(GLFW_KEY_KP_0) :
      return glfw::key::Key_Pad_0;
    case(GLFW_KEY_KP_1) :
      return glfw::key::Key_Pad_1;
    case(GLFW_KEY_KP_2) :
      return glfw::key::Key_Pad_2;
    case(GLFW_KEY_KP_3) :
      return glfw::key::Key_Pad_3;
    case(GLFW_KEY_KP_4) :
      return glfw::key::Key_Pad_4;
    case(GLFW_KEY_KP_5) :
      return glfw::key::Key_Pad_5;
    case(GLFW_KEY_KP_6) :
      return glfw::key::Key_Pad_6;
    case(GLFW_KEY_KP_7) :
      return glfw::key::Key_Pad_7;
    case(GLFW_KEY_KP_8) :
      return glfw::key::Key_Pad_8;
    case(GLFW_KEY_KP_9) :
      return glfw::key::Key_Pad_9;
    case(GLFW_KEY_KP_DECIMAL) :
      return glfw::key::Key_Pad_Decimal;
    case(GLFW_KEY_KP_DIVIDE) :
      return glfw::key::Key_Pad_Divide;
    case(GLFW_KEY_KP_MULTIPLY) :
      return glfw::key::Key_Pad_Multiply;
    case(GLFW_KEY_KP_SUBTRACT) :
      return glfw::key::Key_Pad_Subtract;
    case(GLFW_KEY_KP_ADD) :
      return glfw::key::Key_Pad_Add;
    case(GLFW_KEY_KP_ENTER) :
      return glfw::key::Key_Pad_Enter;
    case(GLFW_KEY_KP_EQUAL) :
      return glfw::key::Key_Pad_Equal;
    case(GLFW_KEY_LEFT_SHIFT) :
      return glfw::key::Left_Shift;
    case(GLFW_KEY_LEFT_CONTROL) :
      return glfw::key::Left_Control;
    case(GLFW_KEY_LEFT_ALT) :
      return glfw::key::Left_Alt;
    case(GLFW_KEY_LEFT_SUPER) :
      return glfw::key::Left_Super;
    case(GLFW_KEY_RIGHT_SHIFT) :
      return glfw::key::Right_Shift;
    case(GLFW_KEY_RIGHT_CONTROL) :
      return glfw::key::Right_Control;
    case(GLFW_KEY_RIGHT_ALT) :
      return glfw::key::Right_Alt;
    case(GLFW_KEY_RIGHT_SUPER) :
      return glfw::key::Right_Super;
    case(GLFW_KEY_MENU) :
      return glfw::key::Menu;
  }
  throw std::invalid_argument("invalid key");
}

[[nodiscard]]
constexpr glfw::mouse_button to_mouse_button(int const mouse_button)
{
  switch(mouse_button)
  {
    case GLFW_MOUSE_BUTTON_LEFT :
      return glfw::mouse_button::Left;
    case GLFW_MOUSE_BUTTON_RIGHT :
      return glfw::mouse_button::Right;
    case GLFW_MOUSE_BUTTON_MIDDLE :
      return glfw::mouse_button::Middle;
    case GLFW_MOUSE_BUTTON_4 :
      return glfw::mouse_button::Button_4;
    case GLFW_MOUSE_BUTTON_5 :
      return glfw::mouse_button::Button_5;
    case GLFW_MOUSE_BUTTON_6 :
      return glfw::mouse_button::Button_6;
    case GLFW_MOUSE_BUTTON_7 :
      return glfw::mouse_button::Button_7;
    case GLFW_MOUSE_BUTTON_8 :
      return glfw::mouse_button::Button_8;
  }
  throw std::invalid_argument("invalid mouse button");
}

[[nodiscard]]
constexpr glfw::action to_action(int const action)
{
  switch(action)
  {
    case(GLFW_PRESS) :
      return glfw::action::press;
    case(GLFW_RELEASE) :
      return glfw::action::release;
    case(GLFW_REPEAT) :
      return glfw::action::repeat;
  }
  throw std::invalid_argument("invalid action");
}

[[nodiscard]]
constexpr glfw::modifiers to_modifier(int const mods) noexcept
{
  return {.Shift     = static_cast<bool>(mods & GLFW_MOD_SHIFT),
          .Control   = static_cast<bool>(mods & GLFW_MOD_CONTROL),
          .Alt       = static_cast<bool>(mods & GLFW_MOD_ALT),
          .Super     = static_cast<bool>(mods & GLFW_MOD_SUPER),
          .Caps_Lock = static_cast<bool>(mods & GLFW_MOD_CAPS_LOCK),
          .Num_Lock  = static_cast<bool>(mods & GLFW_MOD_NUM_LOCK)};
}

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
    glfw_window->on_framebuffer_size_update(*glfw_window, {glfw::to_pixel(width), glfw::to_pixel(height)});
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
    glfw_window->on_mouse_button_action(*glfw_window, to_mouse_button(button), to_action(action), to_modifier(mods));
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
    glfw_window->on_key_action(*glfw_window, scancode, to_key(key), to_action(action), to_modifier(mods));
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
  return {to_pixel(width), to_pixel(height)};
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
    return std::string();
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
    return std::string();
  }
}

glfw::monitor glfw::window::get_monitor() const noexcept
{
  auto * const current_monitor = _window ? glfwGetWindowMonitor(_window.get()) : nullptr;
  return _window and _library ? monitor(current_monitor, *_library) : nullhandle;
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

void glfw::window::reset_icon() noexcept
{
  if(_window)
    glfwSetWindowIcon(_window.get(), 0, nullptr);
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

void glfw::window::set_aspect_ratio(extent<int> const aspect_ratio) noexcept
{
  if(_window)
    glfwSetWindowAspectRatio(_window.get(), aspect_ratio.width, aspect_ratio.height);
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

void glfw::window::set_position(coordinates<int> const position) noexcept
{
  if(_window)
    glfwSetWindowPos(_window.get(), position.x, position.y);
}

void glfw::window::set_size(extent<int> const size) noexcept
{
  if(_window)
    glfwSetWindowSize(_window.get(), size.width, size.height);
}

void glfw::window::set_size_limits(extent<int> const min_size, extent<int> const max_size) noexcept
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

glfw::window::window(nullhandle_t) noexcept
: _window(nullptr, glfwDestroyWindow)
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
: _library(library),
  _window(window, glfwDestroyWindow)
{
  assert(_window);
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
