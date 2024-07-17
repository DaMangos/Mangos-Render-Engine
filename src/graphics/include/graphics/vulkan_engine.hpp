#pragma once

#include <vulkan/handles.hpp>

#include <optional>

namespace graphics
{
class vulkan_engine
{
    vulkan_engine(std::optional<int> const logging_level = std::nullopt);

  private:
    vulkan::instance                   _instance;
    vulkan::ext::debug_report_callback _debug_report_callback;
    vulkan::ext::debug_utils_messenger _debug_utils_messenger;
    vulkan::device                     _device;
    vulkan::physical_device            _physical_device;
    vulkan::khr::surface               _surface;
};
}