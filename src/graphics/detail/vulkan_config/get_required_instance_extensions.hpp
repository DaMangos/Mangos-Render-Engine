#pragma once

#include <vector>

namespace graphics::detail::vulkan_config
{
[[nodiscard]]
std::vector<char const *> get_required_instance_extensions();

[[nodiscard]]
std::vector<char const *> get_required_debug_instance_extensions();
}