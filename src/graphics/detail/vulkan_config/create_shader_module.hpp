#pragma once

#include <vulkan/vulkan.hpp>

#include <filesystem>

namespace graphics::detail::vulkan_config
{
[[nodiscard]]
vk::UniqueShaderModule create_shader_module(vk::Device const device, std::filesystem::path const & complied_shader_path);
}