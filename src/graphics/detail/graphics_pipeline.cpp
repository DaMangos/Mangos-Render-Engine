#include "graphics_pipeline.hpp"

#include "vulkan_config/create_command_pool.hpp"
#include "vulkan_config/create_debug_utils_messenger.hpp"
#include "vulkan_config/create_device.hpp"
#include "vulkan_config/create_instance.hpp"
#include "vulkan_config/create_shader_module.hpp"
#include "vulkan_config/create_surface.hpp"
#include "vulkan_config/select_physical_device.hpp"

graphics::detail::graphics_pipeline::graphics_pipeline(std::shared_ptr<GLFWwindow> const & window, bool const debug)
: window(window ? window : throw std::invalid_argument("window is nullptr")),
  instance(debug ? vulkan_config::create_debug_instance() : vulkan_config::create_instance()),
  debug_messenger(debug ? vulkan_config::create_debug_utils_messenger(instance.get()) : vk::UniqueDebugUtilsMessengerEXT{}),
  surface(vulkan_config::create_surface(instance.get(), window.get())),
  physical_device(vulkan_config::select_physical_device(instance.get())),
  device(vulkan_config::create_device(physical_device, surface.get())),
  command_pool(vulkan_config::create_command_pool(device.get(), physical_device)),
  vertex_shader_module(vulkan_config::create_shader_module(device.get(), "main.spv")),
  fragment_shader_module(vulkan_config::create_shader_module(device.get(), "spv/frag/shader/main.spv"))
{
}
