#include "../enums/to_platform.hpp"
#include "../structs/internal/set_hints.hpp"

#include <glfw/enums/platform.hpp>
#include <glfw/except/api_unavailable.hpp>
#include <glfw/except/cursor_unavailable.hpp>
#include <glfw/except/feature_unavailable.hpp>
#include <glfw/except/feature_unimplemented.hpp>
#include <glfw/except/format_unavailable.hpp>
#include <glfw/except/invalid_enum.hpp>
#include <glfw/except/invalid_value.hpp>
#include <glfw/except/no_current_context.hpp>
#include <glfw/except/no_window_context.hpp>
#include <glfw/except/not_initialized.hpp>
#include <glfw/except/out_of_memory.hpp>
#include <glfw/except/platform_error.hpp>
#include <glfw/except/platform_unavailable.hpp>
#include <glfw/except/version_unavailable.hpp>
#include <glfw/handles/cursor.hpp>
#include <glfw/handles/library.hpp>
#include <glfw/handles/monitor.hpp>
#include <glfw/handles/window.hpp>
#include <glfw/structs/coordinates.hpp>
#include <glfw/structs/version.hpp>

#include <atomic>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
std::atomic_long reference_count = 0;

void error_callback(int const error_code, char const * const description)
{
  switch(error_code)
  {
    case GLFW_NOT_INITIALIZED :
      throw glfw::not_initialized(description);
    case GLFW_NO_CURRENT_CONTEXT :
      throw glfw::no_current_context(description);
    case GLFW_INVALID_ENUM :
      throw glfw::invalid_enum(description);
    case GLFW_INVALID_VALUE :
      throw glfw::invalid_value(description);
    case GLFW_NO_WINDOW_CONTEXT :
      throw glfw::no_window_context(description);
    case GLFW_OUT_OF_MEMORY :
      throw glfw::out_of_memory(description);
    case GLFW_PLATFORM_ERROR :
      throw glfw::platform_error(description);
    case GLFW_PLATFORM_UNAVAILABLE :
      throw glfw::platform_unavailable(description);
    case GLFW_FEATURE_UNAVAILABLE :
      throw glfw::feature_unavailable(description);
    case GLFW_API_UNAVAILABLE :
      throw glfw::api_unavailable(description);
    case GLFW_VERSION_UNAVAILABLE :
      throw glfw::version_unavailable(description);
    case GLFW_FORMAT_UNAVAILABLE :
      throw glfw::format_unavailable(description);
    case GLFW_CURSOR_UNAVAILABLE :
      throw glfw::cursor_unavailable(description);
    case GLFW_FEATURE_UNIMPLEMENTED :
      throw glfw::feature_unimplemented(description);
  }
  throw;
}
}

long glfw::library::use_count() const noexcept
{
  return reference_count.load();
}

glfw::cursor glfw::library::create_cursor(image image, coordinates<pixel> const & hotspot) const
{
  image.pixels.push_back(std::byte{'\0'});
  GLFWimage const glfw_image = {
    .width  = image.size.width,
    .height = image.size.height,
    .pixels = reinterpret_cast<unsigned char *>(image.pixels.data()),
  };

  return cursor(glfwCreateCursor(&glfw_image, static_cast<int>(hotspot.x), static_cast<int>(hotspot.y)), *this);
}

glfw::cursor glfw::library::create_standard_arrow_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_ARROW_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_i_beam_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_IBEAM_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_crosshair_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_hand_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_HAND_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_horizontal_resize_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR), *this);
}

glfw::cursor glfw::library::create_standard_vertical_resize_cursor() const
{
  return cursor(glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title) const
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, monitor const & monitor) const
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, window const & share) const
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, monitor const & monitor, window const & share) const
{
  glfwDefaultWindowHints();
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, window_hints const & hints) const
{
  glfwDefaultWindowHints();
  internal::set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const &  size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window_hints const & hints) const
{
  glfwDefaultWindowHints();
  internal::set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), nullptr), *this);
}

glfw::window glfw::library::create_window(extent<int> const & size, std::string const & title, window const & share, window_hints const & hints) const
{
  glfwDefaultWindowHints();
  internal::set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, share.get()), *this);
}

glfw::window glfw::library::create_window(extent<int> const &  size,
                                          std::string const &  title,
                                          monitor const &      monitor,
                                          window const &       share,
                                          window_hints const & hints) const
{
  glfwDefaultWindowHints();
  internal::set_hints(hints);
  return window(glfwCreateWindow(size.width, size.height, title.c_str(), monitor.get(), share.get()), *this);
}

glfw::window glfw::library::get_current_context() const
{
  return window(glfwGetCurrentContext(), *this);
}

glfw::monitor glfw::library::get_primary_monitor() const
{
  return monitor(glfwGetPrimaryMonitor(), *this);
}

std::vector<glfw::monitor> glfw::library::get_monitors() const
{
  int                  count   = {};
  auto * const * const handles = glfwGetMonitors(&count);

  if(not handles)
    return {};

  std::vector<monitor> monitors;
  monitors.reserve(static_cast<std::size_t>(count));
  std::ranges::transform(std::span(handles, static_cast<std::size_t>(count)),
                         std::back_inserter(monitors),
                         [this](auto const handle) { return monitor(handle, *this); });

  return monitors;
}

glfw::version glfw::library::get_version()
{
  version version = {};
  glfwGetVersion(&version.major, &version.minor, &version.revision);
  return version;
}

std::string glfw::library::get_version_string()
{
  return glfwGetVersionString();
}

glfw::platform glfw::library::get_platform() const
{
  return to_platform(glfwGetPlatform());
}

bool glfw::library::is_platform_supported(glfw::platform const platform)
{
  return glfwPlatformSupported(static_cast<int>(platform)) == GLFW_TRUE;
}

bool glfw::library::is_raw_mouse_motion_supported() const
{
  return glfwRawMouseMotionSupported() == GLFW_TRUE;
}

bool glfw::library::is_extension_supported(std::string const & extension) const
{
  return glfwExtensionSupported(extension.c_str()) == GLFW_TRUE;
}

bool glfw::library::is_vulkan_supported() const
{
  return glfwVulkanSupported() == GLFW_TRUE;
}

std::vector<std::string> glfw::library::get_required_instance_extensions() const
{
  std::uint32_t      count      = {};
  auto const * const extensions = glfwGetRequiredInstanceExtensions(&count);
  return std::vector<std::string>(extensions, std::ranges::next(extensions, count));
}

int glfw::library::get_key_scancode(key const key) const
{
  return glfwGetKeyScancode(static_cast<int>(key));
}

std::string glfw::library::get_key_name(printable_key const key) const
{
  return glfwGetKeyName(static_cast<int>(static_cast<glfw::key>(key)), 0);
}

void glfw::library::swap_interval(int const interval) const
{
  glfwSwapInterval(interval);
}

void glfw::library::poll_events() const
{
  glfwPollEvents();
}

void glfw::library::wait_events() const
{
  glfwWaitEvents();
}

void glfw::library::wait_events_timeout(double const timeout) const
{
  glfwWaitEventsTimeout(timeout);
}

void glfw::library::post_empty_event() const
{
  glfwPostEmptyEvent();
}

glfw::library::library()
{
  glfwTerminate();
  glfwInit();
  glfwSetErrorCallback(error_callback);
  reference_count++;
}

glfw::library::library(library_hints const & hints)
{
  glfwTerminate();
  internal::set_hints(hints);
  glfwInit();
  glfwSetErrorCallback(error_callback);
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
