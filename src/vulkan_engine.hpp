#pragma once

#include <span>
#include <string_view>
#include <unordered_map>
#include <vulkan/wrappers.hpp>

struct vulkan_engine final
{
    vulkan_engine([[maybe_unused]] std::span<std::string_view const> const args);

    void run();

    vulkan_engine(vulkan_engine &&)                 = delete;
    vulkan_engine(vulkan_engine const &)            = delete;
    vulkan_engine &operator=(vulkan_engine &&)      = delete;
    vulkan_engine &operator=(vulkan_engine const &) = delete;
    ~vulkan_engine()                                = default;

  private:
    vulkan::instance                                            _instance;
    std::unordered_map<vulkan::physical_device, vulkan::device> _devices;
};