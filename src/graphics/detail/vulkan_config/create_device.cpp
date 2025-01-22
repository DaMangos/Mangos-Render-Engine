#include "create_device.hpp"

#include "find_queue_family_index.hpp"
#include "get_count.hpp"
#include "get_data.hpp"
#include "get_required_device_extensions.hpp"
#include "get_required_physical_device_features.hpp"

#include <ranges>

namespace
{
vk::DeviceQueueCreateInfo create_device_queue_create_info(std::uint32_t const queue_family_index) noexcept
{
  using namespace graphics::detail::vulkan_config;

  static constexpr std::array queue_priorities = {1.0f};

  return {
    .queueFamilyIndex = queue_family_index,
    .queueCount       = get_count(queue_priorities),
    .pQueuePriorities = get_data(queue_priorities),
  };
}

auto get_unique_device_queue_create_infos(std::ranges::contiguous_range auto & device_queue_create_infos) noexcept
{
  return std::ranges::unique(device_queue_create_infos,
                             [](auto const & lhs, auto const & rhs) { return lhs.queueFamilyIndex == rhs.queueFamilyIndex; });
}
}

vk::UniqueDevice graphics::detail::vulkan_config::create_device(vk::PhysicalDevice const physical_device, vk::SurfaceKHR const surface)
{
  auto const queue_properties             = physical_device.getQueueFamilyProperties();
  auto const graphics_queue_family_index  = find_queue_family_index(queue_properties, vk::QueueFlagBits::eGraphics);
  auto const present_queue_property_index = find_surface_support_queue_family_index(physical_device, surface);

  std::array device_queue_create_infos = {
    create_device_queue_create_info(graphics_queue_family_index.value()),
    create_device_queue_create_info(present_queue_property_index.value()),
  };

  auto const unique_device_queue_create_infos = get_unique_device_queue_create_infos(device_queue_create_infos);
  auto const extensions                       = get_required_device_extensions();
  auto const features                         = get_required_physical_device_features();

  vk::DeviceCreateInfo const info = {
    .queueCreateInfoCount    = get_count(unique_device_queue_create_infos),
    .pQueueCreateInfos       = get_data(unique_device_queue_create_infos),
    .enabledExtensionCount   = get_count(extensions),
    .ppEnabledExtensionNames = get_data(extensions),
    .pEnabledFeatures        = &features,
  };

  return physical_device.createDeviceUnique(info);
}
