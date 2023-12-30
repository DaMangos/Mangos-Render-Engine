#pragma once

#include <glfw/handles.hpp>
#include <span>
#include <string_view>
#include <unordered_map>
#include <vulkan/handles.hpp>

struct vulkan_engine final
{
    vulkan_engine(std::span<std::string_view const> const args);

    void draw_frame();

    vulkan_engine(vulkan_engine &&)                 = delete;
    vulkan_engine(vulkan_engine const &)            = delete;
    vulkan_engine &operator=(vulkan_engine &&)      = delete;
    vulkan_engine &operator=(vulkan_engine const &) = delete;
    ~vulkan_engine()                                = default;

  private:
    vulkan::instance                                  _instance;
    vulkan::physical_device                           _physical_device;
    vulkan::device                                    _device;
    std::optional<vulkan::ext::debug_utils_messenger> _utils_messenger;
    std::optional<vulkan::ext::debug_report_callback> _report_callback;
};