#include "vulkan_engine.hpp"

#include "application.hpp"

#include <iostream>

namespace
{
constexpr std::array const extensions = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                                         VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME};

constexpr std::array const debug_extensions = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                                               VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
                                               VK_EXT_DEBUG_UTILS_EXTENSION_NAME};

constexpr std::array const debug_layers = {"VK_LAYER_KHRONOS_validation"};

vulkan::instance make_instances(bool const is_debug)
{
  return vulkan::instance({});
}

vulkan::physical_device make_physical_device(vulkan::instance const &instance)
{
  auto [physical_devices, result] = instance.enumerate_physical_devices();
  auto physical_device            = std::ranges::find_if(physical_devices, [](auto &physical_device) { return true; });
  if(physical_device == physical_devices.end())
    throw std::runtime_error("failed to find suitable gpu");
  return std::move(*physical_device);
}

vulkan::device make_device(vulkan::physical_device const &physical_device)
{
  return physical_device.create_device({});
}
}

vulkan_engine::vulkan_engine([[maybe_unused]] std::span<std::string_view const> const args)
: _instance(make_instances(std::ranges::any_of(args, [](auto const &arg) { return arg == "--debug"; }))),
  _physical_device(make_physical_device(_instance)),
  _device(make_device(_physical_device))
{
}

void vulkan_engine::run()
{
}