#include <glfw_wrapper/version_3_4/handles/monitor.hpp>

#include <algorithm>
#include <cassert>
#include <exception>
#include <iterator>
#include <optional>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

GLFWmonitor * glfw::monitor::get() const noexcept
{
  return _monitor;
}

glfw::coordinates<int> glfw::monitor::get_position() const noexcept
{
  int xpos = {}, ypos = {};
  if(_monitor)
    glfwGetMonitorPos(_monitor, &xpos, &ypos);
  return {xpos, ypos};
}

glfw::workarea<int> glfw::monitor::get_workarea() const noexcept
{
  int xpos = {}, ypos = {}, width = {}, height = {};
  if(_monitor)
    glfwGetMonitorWorkarea(_monitor, &xpos, &ypos, &width, &height);
  return {
    { xpos,   ypos},
    {width, height}
  };
}

glfw::extent<glfw::millimetre> glfw::monitor::get_physical_size() const noexcept
{
  int width = {}, height = {};
  if(_monitor)
    glfwGetMonitorPhysicalSize(_monitor, &width, &height);
  return {static_cast<millimetre>(width), static_cast<millimetre>(height)};
}

glfw::scale<float> glfw::monitor::get_content_scale() const noexcept
{
  scale<float> scale = {};
  if(_monitor)
    glfwGetMonitorContentScale(_monitor, &scale.x, &scale.y);
  return scale;
}

std::string glfw::monitor::get_name() const noexcept
{
  try
  {
    return _monitor ? glfwGetMonitorName(_monitor) : std::string();
  }
  catch(std::exception const &)
  {
    return {};
  }
}

std::vector<glfw::video_mode> glfw::monitor::get_video_modes() const noexcept
{
  if(not _monitor)
    return {};

  int                count = {};
  auto const * const modes = glfwGetVideoModes(_monitor, &count);

  try
  {
    std::vector<video_mode> video_modes;
    std::ranges::transform(std::span(modes, static_cast<std::size_t>(count)),
                           std::back_inserter(video_modes),
                           [](auto const & mode)
                           {
                             return video_mode{
                               {mode.width, mode.height},
                               {mode.redBits, mode.greenBits, mode.blueBits},
                               static_cast<hertz>(mode.refreshRate),
                             };
                           });

    return video_modes;
  }
  catch(std::exception const &)
  {
    return {};
  }
}

std::optional<glfw::video_mode> glfw::monitor::get_video_mode() const noexcept
{
  if(not _monitor)
    return {};

  auto const * const mode = glfwGetVideoMode(_monitor);

  return mode ? std::optional<video_mode>({
                  {mode->width, mode->height},
                  {mode->redBits, mode->greenBits, mode->blueBits},
                  static_cast<hertz>(mode->refreshRate)
  })
              : std::nullopt;
}

std::vector<glfw::channel<unsigned short>> glfw::monitor::get_gamma_ramp() const noexcept
{
  if(not _monitor)
    return {};

  auto const * const current_gamma_ramp = glfwGetGammaRamp(_monitor);

  if(not current_gamma_ramp)
    return {};

  try
  {
    std::vector<channel<unsigned short>> gamma_ramp;
    for(unsigned int i = 0; i < current_gamma_ramp->size; i++)
      gamma_ramp.push_back({current_gamma_ramp->red[i], current_gamma_ramp->green[i], current_gamma_ramp->blue[i]});

    return gamma_ramp;
  }
  catch(std::exception const &)
  {
    return {};
  }
}

void glfw::monitor::set_gamma(float const gamma) noexcept
{
  if(_monitor)
    glfwSetGamma(_monitor, gamma);
}

void glfw::monitor::set_gamma_ramp(std::span<channel<unsigned short>> const ramp)
{
  if(not _monitor)
    return;

  auto const * const current_gamma_ramp = glfwGetGammaRamp(_monitor);

  if(not current_gamma_ramp)
    return;

  try
  {
    std::vector<unsigned short> red_chanel;
    std::vector<unsigned short> green_chanel;
    std::vector<unsigned short> blue_chanel;

    std::ranges::transform(ramp, std::back_inserter(red_chanel), [](auto const & channel) { return channel.red; });
    std::ranges::transform(ramp, std::back_inserter(green_chanel), [](auto const & channel) { return channel.green; });
    std::ranges::transform(ramp, std::back_inserter(blue_chanel), [](auto const & channel) { return channel.blue; });

    red_chanel.resize(static_cast<std::size_t>(current_gamma_ramp->size), {});
    green_chanel.resize(static_cast<std::size_t>(current_gamma_ramp->size), {});
    blue_chanel.resize(static_cast<std::size_t>(current_gamma_ramp->size), {});

    GLFWgammaramp const new_gamma_ramp = {
      .red   = red_chanel.data(),
      .green = green_chanel.data(),
      .blue  = blue_chanel.data(),
      .size  = current_gamma_ramp->size,
    };

    glfwSetGammaRamp(_monitor, &new_gamma_ramp);
  }
  catch(std::exception const &)
  {
  }
}

void glfw::monitor::reset() noexcept
{
  _monitor = nullptr;
}

glfw::monitor::monitor(nullhandle_t) noexcept
{
}

glfw::monitor::monitor(monitor && other) noexcept
: _library(std::move(other._library)),
  _monitor(std::exchange(other._monitor, nullptr))
{
}

glfw::monitor & glfw::monitor::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

glfw::monitor & glfw::monitor::operator=(monitor && other) noexcept
{
  _library = std::move(other._library);
  _monitor = std::exchange(other._monitor, nullptr);
  return *this;
}

std::strong_ordering glfw::monitor::operator<=>(nullhandle_t) const noexcept
{
  return _monitor <=> static_cast<GLFWmonitor *>(nullptr);
}

std::strong_ordering glfw::monitor::operator<=>(monitor const & other) const noexcept
{
  return _monitor <=> other._monitor;
}

glfw::monitor::operator bool() const noexcept
{
  return static_cast<bool>(_monitor);
}

glfw::monitor::monitor(GLFWmonitor * const monitor, library const library)
: _library(std::nullopt),
  _monitor(monitor)
{
  if(_monitor)
    _library.emplace(library);
}
