#pragma once

#include "glfw/structs/extent.hpp"
#include "vulkan/handles/device.hpp"
#include "vulkan/handles/physical_device.hpp"
#include <glfw/handles.hpp>
#include <vulkan/handles.hpp>

namespace graphics
{
class render_window
{
    render_window(std::string const & title, glfw::extent<int> const & size);

  private:
    glfw::library _library;
    glfw::window  _window;

    vulkan::instance                   _instance;
    vulkan::ext::debug_report_callback _debug_report_callback;
    vulkan::ext::debug_utils_messenger _debug_utils_messenger;
    vulkan::device                     _device;
    vulkan::physical_device            _physical_device;
};
}