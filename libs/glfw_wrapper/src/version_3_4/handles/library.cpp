#include "../enums/to_error_code.hpp"
#include "../enums/to_key.hpp"
#include "../enums/to_platform.hpp"
#include "../structs/set_hints.hpp"

#include <glfw_wrapper/structs/version.hpp>
#include <glfw_wrapper/version_3_4/enums/platform.hpp>
#include <glfw_wrapper/version_3_4/handles/cursor.hpp>
#include <glfw_wrapper/version_3_4/handles/library.hpp>
#include <glfw_wrapper/version_3_4/handles/monitor.hpp>
#include <glfw_wrapper/version_3_4/handles/window.hpp>
#include <glfw_wrapper/version_3_4/structs/coordinates.hpp>

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

glfw::cursor glfw::library::create_cursor(image image, coordinates<pixel> const & hotspot) const noexcept
{
  GLFWimage const glfw_image = {
    .width  = image.size.width,
    .height = image.size.height,
    .pixels = reinterpret_cast<unsigned char *>(image.pixels.data()),
  };

  return cursor(glfwCreateCursor(&glfw_image, static_cast<int>(hotspot.x), static_cast<int>(hotspot.y)), *this);
}

glfw::cursor glfw::library::create_standard_arrow_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_ARROW_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_i_beam_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_IBEAM_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_crosshair_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_hand_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_HAND_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_horizontal_resize_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_vertical_resize_cursor() const noexcept
{
  return cursor(glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title) const noexcept
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, monitor const & monitor) const noexcept
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, window const & share) const noexcept
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size,
                                          std::string const & title,
                                          monitor const &     monitor,
                                          window const &      share) const noexcept
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const &  size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const &  size,
                                          std::string const &  title,
                                          window const &       share,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const &  size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window const &       share,
                                          window_hints const & hints) const noexcept
{
  glfwDefaultWindowHints();
  set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get()), *this);
}

glfw::window glfw::library::get_current_context() const noexcept
{
  return window(glfwGetCurrentContext(), *this);
}

glfw::monitor glfw::library::get_primary_monitor() const noexcept
{
  return monitor(glfwGetPrimaryMonitor(), *this);
}

std::vector<glfw::monitor> glfw::library::get_monitors() const noexcept
{
  int                  count   = {};
  auto * const * const handles = glfwGetMonitors(&count);

  try
  {
    std::vector<monitor> monitors;
    monitors.reserve(static_cast<std::size_t>(count));
    std::ranges::transform(std::span(handles, static_cast<std::size_t>(count)),
                           std::back_inserter(monitors),
                           [this](auto const handle) { return monitor(handle, *this); });

    return monitors;
  }
  catch(std::exception const &)
  {
    return {};
  }
}

glfw::version glfw::library::get_version() noexcept
{
  version version = {};
  glfwGetVersion(&version.major, &version.minor, &version.revision);
  return version;
}

std::string glfw::library::get_version_string() noexcept
{
  auto const * const version = glfwGetVersionString();
  try
  {
    return version ? std::string(version) : std::string();
  }
  catch(std::exception const &)
  {
    return {};
  }
}

std::pair<glfw::error_code, std::string> glfw::library::get_last_error() noexcept
{
  char const * description = nullptr;
  auto         code        = glfwGetError(&description);
  try
  {
    return {to_error_code(code), description ? std::string(description) : std::string()};
  }
  catch(std::exception const &)
  {
    return {to_error_code(code), {}};
  }
}

glfw::platform glfw::library::get_platform() const noexcept
{
  return to_platform(glfwGetPlatform());
}

bool glfw::library::is_platform_supported(glfw::platform const platform) noexcept
{
  try
  {
    return glfwPlatformSupported(to_int(platform)) == GLFW_TRUE;
  }
  catch(std::exception const &)
  {
    return false;
  }
}

bool glfw::library::is_raw_mouse_motion_supported() const noexcept
{
  return glfwRawMouseMotionSupported() == GLFW_TRUE;
}

bool glfw::library::is_extension_supported(std::string const & extension) const noexcept
{
  return glfwExtensionSupported(extension.c_str()) == GLFW_TRUE;
}

bool glfw::library::is_vulkan_supported() const noexcept
{
  return glfwVulkanSupported() == GLFW_TRUE;
}

std::vector<std::string> glfw::library::get_required_instance_extensions() const noexcept
{
  std::uint32_t      count      = {};
  auto const * const extensions = glfwGetRequiredInstanceExtensions(&count);
  try
  {
    return std::vector<std::string>(extensions, std::ranges::next(extensions, count));
  }
  catch(std::exception const &)
  {
    return {};
  }
}

int glfw::library::get_key_scancode(key const key) const noexcept
{
  return glfwGetKeyScancode(to_int(key));
}

std::string glfw::library::get_key_name(key const key, int const scancode) const noexcept
{
  try
  {
    return glfwGetKeyName(to_int(key), scancode);
  }
  catch(std::exception const &)
  {
    return {};
  }
}

void glfw::library::swap_interval(int const interval) const noexcept
{
  glfwSwapInterval(interval);
}

void glfw::library::poll_events() const noexcept
{
  glfwPollEvents();
}

void glfw::library::wait_events() const noexcept
{
  glfwWaitEvents();
}

void glfw::library::wait_events_timeout(double const timeout) const noexcept
{
  glfwWaitEventsTimeout(timeout);
}

void glfw::library::post_empty_event() const noexcept
{
  glfwPostEmptyEvent();
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
