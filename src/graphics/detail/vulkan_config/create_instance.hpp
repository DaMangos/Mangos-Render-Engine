#pragma once

#include <vulkan/vulkan.hpp>

namespace graphics::detail::vulkan_config
{
[[nodiscard]]
vk::UniqueInstance create_instance();

[[nodiscard]]
vk::UniqueInstance create_debug_instance();
}