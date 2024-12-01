#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::internal::vulkan_config
{
[[nodiscard]]
vk::DebugUtilsMessengerCreateInfoEXT create_debug_utils_messenger_create_info();

[[nodiscard]]
vk::UniqueDebugUtilsMessengerEXT create_debug_utils_messenger(vk::Instance const instance);
}