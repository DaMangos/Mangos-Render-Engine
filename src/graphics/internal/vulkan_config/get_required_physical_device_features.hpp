#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
consteval vk::PhysicalDeviceFeatures get_required_physical_device_features() noexcept
{
  return {.samplerAnisotropy = vk::True};
}
}