#pragma once

#include <vulkan/vulkan.hpp>

#include <array>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
consteval auto get_required_device_extensions() noexcept
{
  return std::array{vk::KHRSwapchainExtensionName, vk::KHRPortabilitySubsetExtensionName};
}
}