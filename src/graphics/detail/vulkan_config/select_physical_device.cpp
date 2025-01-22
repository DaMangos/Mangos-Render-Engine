#include "select_physical_device.hpp"

#include "find_queue_family_index.hpp"
#include "get_required_device_extensions.hpp"
#include "get_required_physical_device_features.hpp"

#include <algorithm>
#include <ranges>
#include <span>

namespace
{
bool has_required_queue_properties(vk::PhysicalDevice const physical_device)
{
  using namespace graphics::detail::vulkan_config;

  return static_cast<bool>(find_queue_family_index(physical_device.getQueueFamilyProperties(), vk::QueueFlagBits::eGraphics));
}

bool has_extention_support(vk::PhysicalDevice const physical_device)
{
  using namespace graphics::detail::vulkan_config;

  return std::ranges::all_of(
    get_required_device_extensions(),
    [properties = physical_device.enumerateDeviceExtensionProperties()](auto const & extension)
    {
      return std::ranges::any_of(properties, [extension](auto const & property) { return std::string_view(property.extensionName) == extension; });
    });
}

bool has_required_features(vk::PhysicalDevice const physical_device)
{
  using namespace graphics::detail::vulkan_config;

  auto const features          = physical_device.getFeatures();
  auto const required_features = get_required_physical_device_features();

  auto const to_span = [](auto & features)
  {
    return std::span(reinterpret_cast<vk::Bool32 const *>(&features), sizeof(features) / sizeof(vk::Bool32));
  };

  return std::ranges::equal(to_span(features),
                            to_span(required_features),
                            [](auto const feature, auto const required_feature)
                            { return required_feature == vk::True ? feature == vk::True : true; });
}

bool is_suitable(vk::PhysicalDevice const physical_device)
{
  return has_required_features(physical_device) and has_required_queue_properties(physical_device) and has_extention_support(physical_device);
}
}

vk::PhysicalDevice graphics::detail::vulkan_config::select_physical_device(vk::Instance const instance)
{
  auto suitable_physical_devices = instance.enumeratePhysicalDevices() | std::views::filter(is_suitable);

  if(suitable_physical_devices.empty())
    throw std::runtime_error("no suitable physical device found");

  return *std::ranges::max_element(suitable_physical_devices);
}