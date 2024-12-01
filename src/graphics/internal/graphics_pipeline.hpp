#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <memory>

namespace graphics::internal
{
class graphics_pipeline
{
  public:
    graphics_pipeline(std::shared_ptr<GLFWwindow> const & window);

  private:
    std::shared_ptr<GLFWwindow>      _window;
    vk::UniqueInstance               _instance;
    vk::UniqueDebugUtilsMessengerEXT _debug_messenger;
    vk::UniqueSurfaceKHR             _surface;
    vk::PhysicalDevice               _physical_device;
    vk::UniqueDevice                 _device;
    vk::UniqueCommandPool            _command_pool;
    vk::UniqueShaderModule           _vertex_shader_module;
    vk::UniqueShaderModule           _fragment_shader_module;
};
}
