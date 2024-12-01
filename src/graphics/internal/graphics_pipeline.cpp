#include "graphics_pipeline.hpp"

#include "vulkan_config/create_command_pool.hpp"
#include "vulkan_config/create_debug_utils_messenger.hpp"
#include "vulkan_config/create_device.hpp"
#include "vulkan_config/create_instance.hpp"
#include "vulkan_config/create_shader_module.hpp"
#include "vulkan_config/create_surface.hpp"
#include "vulkan_config/select_physical_device.hpp"

graphics::internal::graphics_pipeline::graphics_pipeline(std::shared_ptr<GLFWwindow> const & window)
: _window(window ? window : throw std::invalid_argument("window is nullptr")),
  _instance(vulkan_config::create_debug_instance()),
  _debug_messenger(vulkan_config::create_debug_utils_messenger(_instance.get())),
  _surface(vulkan_config::create_surface(_instance.get(), window.get())),
  _physical_device(vulkan_config::select_physical_device(_instance.get())),
  _device(vulkan_config::create_device(_physical_device, _surface.get())),
  _command_pool(vulkan_config::create_command_pool(_device.get(), _physical_device)),
  _vertex_shader_module(vulkan_config::create_shader_module(_device.get(), "")),
  _fragment_shader_module(vulkan_config::create_shader_module(_device.get(), ""))
{
}
