#include "set_hints.hpp"

#include "glfw_wrapper/version_3_4/window_hints.hpp"
#include <glfw_wrapper/version_3_4/library.hpp>
#include <glfw_wrapper/version_3_4/monitor.hpp>
#include <glfw_wrapper/version_3_4/window.hpp>

#include <atomic>

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
  glfwDefaultWindowHints();
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title, monitor const & monitor) const noexcept
{
  glfwDefaultWindowHints();
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title, window const & share) const noexcept
{
  glfwDefaultWindowHints();
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get());
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const   size,
                                          std::string const & title,
                                          monitor const &     monitor,
                                          window const &      share) const noexcept
{
  glfwDefaultWindowHints();
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get());
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const size, std::string const & title, window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const    size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr);
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const    size,
                                          std::string const &  title,
                                          window const &       share,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  auto * const window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get());
  return window ? glfw::window(window, *this) : nullhandle;
}

glfw::window glfw::library::create_window(extent<int> const    size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window const &       share,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
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
  set_hints(hints);
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
