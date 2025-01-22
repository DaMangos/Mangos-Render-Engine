#pragma once

#include <array>

namespace graphics::detail::vulkan_config
{
[[nodiscard]]
consteval auto get_layers() noexcept
{
  return std::array{"VK_LAYER_KHRONOS_validation"};
}
}