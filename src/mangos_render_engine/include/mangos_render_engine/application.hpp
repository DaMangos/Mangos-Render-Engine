#pragma once

#include <glfw_wrapper/glfw_wrapper.hpp>
#include <vulkan_wrapper/vulkan_wrapper.hpp>

#include <optional>
#include <string_view>
#include <vector>

namespace mangos_render_engine
{
class application
{
  public:
    explicit application(std::vector<std::string_view> const & args);

    void run();

  private:
    glfw::library                                     _library;
    glfw::window                                      _window;
    vulkan::instance                                  _instance;
    std::optional<vulkan::ext::debug_report_callback> _debug_report_callback;
    std::optional<vulkan::ext::debug_utils_messenger> _debug_utils_messenger;
    vulkan::physical_device                           _physical_device;
    vulkan::device                                    _device;
};
}