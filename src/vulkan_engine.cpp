#include "vulkan_engine.hpp"

#include "application.hpp"

#include <iostream>
#include <stdexcept>

namespace
{
constexpr std::array const extensions = {
  VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
  VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

constexpr std::array const debug_extensions = {
  VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
  VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
  VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

constexpr std::array const device_extensions = {
  VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
  VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#ifdef __APPLE__
  VK_NV_GLSL_SHADER_EXTENSION_NAME,
#endif
};

constexpr std::array const debug_layers = {"VK_LAYER_KHRONOS_validation"};

vulkan::instance make_instance(std::span<std::string_view const> const args)
{
  bool is_debug = std::ranges::any_of(args, [](auto const &arg) { return arg == "--debug"; });

  return vulkan::instance({
    .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext                   = nullptr,
    .flags                   = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
    .pApplicationInfo        = nullptr,
    .enabledLayerCount       = is_debug ? vulkan::ranges::size(debug_layers) : 0,
    .ppEnabledLayerNames     = is_debug ? vulkan::ranges::data(debug_layers) : nullptr,
    .enabledExtensionCount   = is_debug ? vulkan::ranges::size(debug_extensions) : vulkan::ranges::size(extensions),
    .ppEnabledExtensionNames = is_debug ? vulkan::ranges::data(debug_extensions) : vulkan::ranges::data(extensions),
  });
}

vulkan::physical_device make_physical_device(vulkan::instance const &instance)
{
  auto [physical_devices, result] = instance.enumerate_physical_devices();
  auto physical_device            = std::ranges::find_if(physical_devices, [](auto &) { return true; });
  if(physical_device == physical_devices.end())
    throw std::runtime_error("failed to find suitable gpu");
  return std::move(*physical_device);
}

vulkan::device make_device(std::span<std::string_view const> const args, vulkan::physical_device const &physical_device)
{
  bool is_debug = std::ranges::any_of(args, [](auto const &arg) { return arg == "--debug"; });

  return physical_device.create_device({
    .sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext                   = nullptr,
    .flags                   = {},
    .queueCreateInfoCount    = 0,
    .pQueueCreateInfos       = nullptr,
    .enabledLayerCount       = is_debug ? vulkan::ranges::size(debug_layers) : 0,
    .ppEnabledLayerNames     = is_debug ? vulkan::ranges::data(debug_layers) : nullptr,
    .enabledExtensionCount   = vulkan::ranges::size(device_extensions),
    .ppEnabledExtensionNames = vulkan::ranges::data(device_extensions),
    .pEnabledFeatures        = nullptr,
  });
}
}

vulkan_engine::vulkan_engine(std::span<std::string_view const> const args)
: _instance(make_instance(args)),
  _physical_device(make_physical_device(_instance)),
  _device(make_device(args, _physical_device))
{
}

void vulkan_engine::draw_frame()
{
}