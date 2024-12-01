#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
vk::PhysicalDevice select_physical_device(vk::Instance const instance);
}