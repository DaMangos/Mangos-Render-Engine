#include <glfw/except/bad_monitor_access.hpp>
#include <glfw/handles/monitor.hpp>

#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

GLFWmonitor * glfw::monitor::get() const noexcept
{
  return _monitor;
}

glfw::coordinates<int> glfw::monitor::get_position() const
{
  int xpos = {}, ypos = {};
  _monitor ? glfwGetMonitorPos(_monitor, &xpos, &ypos) : throw bad_monitor_access();
  return {xpos, ypos};
}

glfw::workarea<int> glfw::monitor::get_workarea() const
{
  int xpos = {}, ypos = {}, width = {}, height = {};
  _monitor ? glfwGetMonitorWorkarea(_monitor, &xpos, &ypos, &width, &height) : throw bad_monitor_access();
  return {
    { xpos,   ypos},
    {width, height}
  };
}

glfw::extent<glfw::millimetre> glfw::monitor::get_physical_size() const
{
  int width = {}, height = {};
  _monitor ? glfwGetMonitorPhysicalSize(_monitor, &width, &height) : throw bad_monitor_access();
  return {static_cast<millimetre>(width), static_cast<millimetre>(height)};
}

glfw::scale<float> glfw::monitor::get_content_scale() const
{
  scale<float> scale = {};
  _monitor ? glfwGetMonitorContentScale(_monitor, &scale.x, &scale.y) : throw bad_monitor_access();
  return scale;
}

std::string glfw::monitor::get_name() const
{
  return _monitor ? glfwGetMonitorName(_monitor) : throw bad_monitor_access();
}

std::vector<glfw::video_mode> glfw::monitor::get_video_modes() const
{
  int                count = {};
  auto const * const modes = _monitor ? glfwGetVideoModes(_monitor, &count) : throw bad_monitor_access();

  if(not modes)
    return {};

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

std::optional<glfw::video_mode> glfw::monitor::get_video_mode() const
{
  auto const * const mode = _monitor ? glfwGetVideoMode(_monitor) : throw bad_monitor_access();

  return mode ? std::optional<video_mode>({
                  {mode->width, mode->height},
                  {mode->redBits, mode->greenBits, mode->blueBits},
                  static_cast<hertz>(mode->refreshRate),
  })
              : std::nullopt;
}

std::vector<glfw::channel<unsigned short>> glfw::monitor::get_gamma_ramp() const
{
  auto const * const current_gamma_ramp = _monitor ? glfwGetGammaRamp(_monitor) : throw bad_monitor_access();

  if(not current_gamma_ramp)
    return {};

  std::vector<channel<unsigned short>> gamma_ramp;
  for(unsigned int i = 0; i < current_gamma_ramp->size; i++)
    gamma_ramp.push_back({current_gamma_ramp->red[i], current_gamma_ramp->green[i], current_gamma_ramp->blue[i]});

  return gamma_ramp;
}

void glfw::monitor::set_gamma(float const gamma)
{
  _monitor ? glfwSetGamma(_monitor, gamma) : throw bad_monitor_access();
}

void glfw::monitor::set_gamma_ramp(std::span<channel<unsigned short>> const ramp)
{
  auto const * const current_gamma_ramp = _monitor ? glfwGetGammaRamp(_monitor) : throw bad_monitor_access();

  if(not current_gamma_ramp)
    return;

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
