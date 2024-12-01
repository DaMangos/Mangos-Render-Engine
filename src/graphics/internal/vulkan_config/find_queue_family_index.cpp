#include "find_queue_family_index.hpp"

#include <iterator>
#include <optional>
#include <ranges>

std::optional<std::uint32_t> graphics::internal::vulkan_config::find_queue_family_index(
  std::vector<vk::QueueFamilyProperties> const & queue_properties,
  vk::QueueFlagBits const                        flags_bit)
{
  auto const property =
    std::ranges::find_if(queue_properties, [flags_bit](auto const & property) { return static_cast<bool>(property.queueFlags & flags_bit); });

  auto const index = std::ranges::distance(queue_properties.begin(), property);

  return index == std::ranges::ssize(queue_properties) ? std::nullopt : std::make_optional(static_cast<std::uint32_t>(index));
}

std::optional<std::uint32_t> graphics::internal::vulkan_config::find_surface_support_queue_family_index(vk::PhysicalDevice const physical_device,
                                                                                                        vk::SurfaceKHR const     surface)
{
  std::uint32_t size = {};
  physical_device.getQueueFamilyProperties(&size, nullptr);

  for(std::uint32_t index = {}; index < size; ++index)
    if(physical_device.getSurfaceSupportKHR(index, surface) == vk::True)
      return index;

  return std::nullopt;
}
