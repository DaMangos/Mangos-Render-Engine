#include "get_required_instance_extensions.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <stdexcept>

std::vector<char const *> graphics::internal::vulkan_config::get_required_instance_extensions(instance_extensions_flags const & flags)
{
  uint32_t extension_count = {};

  auto const extensions_begin = glfwGetRequiredInstanceExtensions(&extension_count);
  auto const extensions_end   = std::ranges::next(extensions_begin, extension_count);

  if(not extensions_begin or not extensions_end)
    throw std::runtime_error("unable to get required instance extensions");

  std::vector extensions(extensions_begin, extensions_end);

  if(flags.enable_debug)
    extensions.emplace_back(vk::EXTDebugUtilsExtensionName);

  extensions.emplace_back(vk::KHRPortabilityEnumerationExtensionName);

  return extensions;
}
