#include <glfw/handles/library.hpp>
#include <glfw/handles/monitor.hpp>
#include <glfw/handles/window.hpp>

#include <atomic>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
std::atomic_long reference_count = 0;
}

long glfw::library::use_count() const noexcept
{
  return reference_count.load();
}

void glfw::library::reset() noexcept
{
  glfwTerminate();
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title) const noexcept
{
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title, monitor const & monitor) const noexcept
{
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title, window const & share) const noexcept
{
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get());
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const   size,
                                          std::string const & title,
                                          monitor const &     monitor,
                                          window const &      share) const noexcept
{
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get());
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::monitor glfw::library::get_primary_monitor() const noexcept
{
  auto * const primary_monitor = glfwGetPrimaryMonitor();
  return primary_monitor ? glfw::monitor(primary_monitor, *this) : nullhandle;
}

std::vector<glfw::monitor> glfw::library::get_monitors() const noexcept
{
  try
  {
    int                  count   = {};
    auto * const * const handles = glfwGetMonitors(&count);

    std::vector<glfw::monitor> monitors;

    std::ranges::transform(std::span(handles, static_cast<std::size_t>(count)),
                           std::back_inserter(monitors),
                           [this](auto const handle) { return glfw::monitor(handle, *this); });

    return monitors;
  }
  catch(std::exception const &)
  {
    return {};
  }
}

glfw::library::library() noexcept
{
  glfwTerminate();
  glfwInit();
  reference_count++;
}

glfw::library::library(library_hints const & hints) noexcept
{
  glfwTerminate();

  glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, hints.joystick_hat_buttons ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, hints.cocoa_chdir_resources ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_COCOA_MENUBAR, hints.cocoa_menubar ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_WAYLAND_LIBDECOR,
               [&hints]()
               {
                 switch(hints.wayland_libdecor)
                 {
                   case library_hints::wayland_libdecor_type::prefer :
                     return GLFW_WAYLAND_PREFER_LIBDECOR;
                   case library_hints::wayland_libdecor_type::disable :
                     return GLFW_WAYLAND_DISABLE_LIBDECOR;
                 }
                 return GLFW_WAYLAND_PREFER_LIBDECOR;
               }());

  glfwInit();
  reference_count++;
}

glfw::library::library(library &&) noexcept
{
  reference_count++;
}

glfw::library::library(library const &) noexcept
{
  reference_count++;
}

glfw::library & glfw::library::operator=(library &&) noexcept
{
  reference_count++;
  return *this;
}

glfw::library & glfw::library::operator=(library const &) noexcept
{
  reference_count++;
  return *this;
}

glfw::library::~library() noexcept
{
  --reference_count;
  if(not reference_count)
    glfwTerminate();
}
