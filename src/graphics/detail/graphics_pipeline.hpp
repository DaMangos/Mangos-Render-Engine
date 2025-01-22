#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <memory>

namespace graphics::detail
{
class graphics_pipeline
{
  public:
    graphics_pipeline(std::shared_ptr<GLFWwindow> const & window, bool const debug);

  private:
    std::shared_ptr<GLFWwindow>      window;
    vk::UniqueInstance               instance;
    vk::UniqueDebugUtilsMessengerEXT debug_messenger;
    vk::UniqueSurfaceKHR             surface;
    vk::PhysicalDevice               physical_device;
    vk::UniqueDevice                 device;
    vk::UniqueCommandPool            command_pool;
    vk::UniqueShaderModule           vertex_shader_module;
    vk::UniqueShaderModule           fragment_shader_module;
};
}
