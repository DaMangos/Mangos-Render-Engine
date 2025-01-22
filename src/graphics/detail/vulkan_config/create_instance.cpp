#include "create_instance.hpp"

#include "create_debug_utils_messenger.hpp"
#include "get_count.hpp"
#include "get_data.hpp"
#include "get_layers.hpp"
#include "get_required_instance_extensions.hpp"

#include <GLFW/glfw3.h>

namespace
{
consteval vk::ApplicationInfo create_application_info() noexcept
{
  return {
    .applicationVersion = VK_MAKE_VERSION(1, 1, 0),
    .engineVersion      = VK_MAKE_VERSION(0, 1, 0),
    .apiVersion         = vk::HeaderVersionComplete,
  };
}
}

vk::UniqueInstance graphics::detail::vulkan_config::create_instance()
{
  VULKAN_HPP_DEFAULT_DISPATCHER.init();

  auto const app_info   = create_application_info();
  auto const extensions = get_required_instance_extensions();

  vk::InstanceCreateInfo const info = {
    .flags                   = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
    .pApplicationInfo        = &app_info,
    .enabledExtensionCount   = get_count(extensions),
    .ppEnabledExtensionNames = get_data(extensions),
  };

  auto instance = vk::createInstanceUnique(info);

  VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.get());

  return instance;
}

vk::UniqueInstance graphics::detail::vulkan_config::create_debug_instance()
{
  VULKAN_HPP_DEFAULT_DISPATCHER.init();

  auto const app_info   = create_application_info();
  auto const extensions = get_required_debug_instance_extensions();
  auto const layers     = get_layers();

  vk::InstanceCreateInfo const info = {
    .flags                   = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
    .pApplicationInfo        = &app_info,
    .enabledLayerCount       = get_count(layers),
    .ppEnabledLayerNames     = get_data(layers),
    .enabledExtensionCount   = get_count(extensions),
    .ppEnabledExtensionNames = get_data(extensions),
  };

  vk::StructureChain const chain(info, create_debug_utils_messenger_create_info());

  auto instance = vk::createInstanceUnique(chain.get());

  VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.get());

  return instance;
}
