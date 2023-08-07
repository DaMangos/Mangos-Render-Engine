#include "physical_device.hpp"

namespace graphics::vulkan
{
physical_device::physical_device(VkPhysicalDevice physical_device) noexcept
: _underling_physical_device(physical_device)
{
}

VkPhysicalDevice physical_device::get() const noexcept
{
  return _underling_physical_device;
}

unique_handle<VkDevice> physical_device::create_device(VkDeviceCreateInfo create_info) const
{
  VkDevice device;
  return return_or_throw(vkCreateDevice(get(), &create_info, nullptr, &device), "vkCreateDevice", make_unique_handle(device));
}

bool physical_device::check_surface_support(VkSurfaceKHR surface, std::uint32_t queue_family) const
{
  VkBool32 supported;
  return return_or_throw(vkGetPhysicalDeviceSurfaceSupportKHR(get(), queue_family, surface, &supported),
                         "vkGetPhysicalDeviceSurfaceSupportKHR",
                         supported == VK_TRUE);
}

VkSurfaceCapabilitiesKHR physical_device::get_surface_capabilities(VkSurfaceKHR surface) const
{
  VkSurfaceCapabilitiesKHR surface_capabilities;
  return return_or_throw(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(get(), surface, &surface_capabilities),
                         "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
                         surface_capabilities);
}

std::vector<VkSurfaceFormatKHR> physical_device::get_surface_formats(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr);
  std::vector<VkSurfaceFormatKHR> surface_formats;
  return return_or_throw(vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, surface_formats.data()),
                         "vkGetPhysicalDeviceSurfaceFormatsKHR",
                         surface_formats);
}

std::vector<VkPresentModeKHR> physical_device::get_present_modes(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr);
  std::vector<VkPresentModeKHR> present_modes;
  return return_or_throw(vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, present_modes.data()),
                         "vkGetPhysicalDeviceSurfacePresentModesKHR",
                         present_modes);
}

VkPhysicalDeviceFeatures physical_device::get_features() const noexcept
{
  VkPhysicalDeviceFeatures features;
  vkGetPhysicalDeviceFeatures(get(), &features);
  return features;
}

VkPhysicalDeviceProperties physical_device::get_properties() const noexcept
{
  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(get(), &properties);
  return properties;
}

std::vector<VkQueueFamilyProperties> physical_device::get_queue_family_properties() const
{
  std::uint32_t count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, nullptr);
  std::vector<VkQueueFamilyProperties> properties(count);
  vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, properties.data());
  return properties;
}

std::vector<VkExtensionProperties> physical_device::get_extension_properties() const
{
  std::uint32_t count = 0;
  vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr);
  std::vector<VkExtensionProperties> properties(count);
  return return_or_throw(vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, properties.data()),
                         "vkEnumerateDeviceExtensionProperties",
                         properties);
}

std::vector<VkExtensionProperties> physical_device::get_extension_properties(std::string const &layer_name) const
{
  std::uint32_t count = 0;
  vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, nullptr);
  std::vector<VkExtensionProperties> properties(count);
  return return_or_throw(vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, properties.data()),
                         "vkEnumerateDeviceExtensionProperties",
                         properties);
}
}