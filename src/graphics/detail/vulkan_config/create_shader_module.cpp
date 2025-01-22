#include "create_shader_module.hpp"

#include <fstream>

vk::UniqueShaderModule graphics::detail::vulkan_config::create_shader_module(vk::Device const              device,
                                                                             std::filesystem::path const & complied_shader_path)
{
  std::ifstream file(complied_shader_path, std::ios::binary);

  if(not file)
    throw std::runtime_error("failed to open file " + complied_shader_path.string());

  std::vector const code(std::istreambuf_iterator(file), {});

  if(code.empty())
    throw std::runtime_error("file " + complied_shader_path.string() + " is empty");

  vk::ShaderModuleCreateInfo const info = {
    .codeSize = code.size(),
    .pCode    = reinterpret_cast<std::uint32_t const *>(code.data()),
  };

  return device.createShaderModuleUnique(info);
}