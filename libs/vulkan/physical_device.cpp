#include "physical_device.hpp"

#include "device.hpp"
#include "instance.hpp"

namespace vulkan
{
VkPhysicalDevice physical_device::get() const noexcept
{
  return physical_device_;
}

device physical_device::create_device(VkDeviceCreateInfo create_info) const
{
  VkDevice ptr;
  switch(vkCreateDevice(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return device(std::move(ptr));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDevice: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to create VkDevice: out of device memory");
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error("failed to create VkDevice: initialization failed");
    case VK_ERROR_EXTENSION_NOT_PRESENT :
      throw std::runtime_error("failed to create VkDevice: extension not present");
    case VK_ERROR_FEATURE_NOT_PRESENT :
      throw std::runtime_error("failed to create VkDevice: feature not present");
    case VK_ERROR_TOO_MANY_OBJECTS :
      throw std::runtime_error("failed to create VkDevice: too many objects");
    case VK_ERROR_DEVICE_LOST :
      throw std::runtime_error("failed to create VkDevice: device lost");
    default :
      throw std::runtime_error("failed to create VkDevice: unknown error");
  }
}

bool physical_device::check_surface_support(VkSurfaceKHR surface, std::uint32_t queue_family) const
{
  VkBool32 supported = VK_FALSE;
  switch(vkGetPhysicalDeviceSurfaceSupportKHR(get(), queue_family, surface, &supported))
  {
    case VK_SUCCESS :
      return supported == VK_TRUE;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: unknown error");
  }
}

VkSurfaceCapabilitiesKHR physical_device::get_surface_capabilities(VkSurfaceKHR surface) const
{
  VkSurfaceCapabilitiesKHR surface_capabilities;
  switch(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(get(), surface, &surface_capabilities))
  {
    case VK_SUCCESS :
      return surface_capabilities;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkSurfaceCapabilitiesKHR: unknown error");
  }
}

std::vector<VkSurfaceFormatKHR> physical_device::get_surface_formats(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  switch(vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: unknown error");
  }
  std::vector<VkSurfaceFormatKHR> surface_formats(count);
  vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, surface_formats.data());
  return surface_formats;
}

std::vector<VkPresentModeKHR> physical_device::get_present_modes(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  switch(vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkPresentModeKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkPresentModeKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkPresentModeKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkPresentModeKHR: unknown error");
  }
  std::vector<VkPresentModeKHR> present_modes(count);
  vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, present_modes.data());
  return present_modes;
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
  switch(vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of device memory");
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: layer not present");
    default :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: unknown error");
  }
  std::vector<VkExtensionProperties> properties(count);
  vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, properties.data());
  return properties;
}

std::vector<VkExtensionProperties> physical_device::get_extension_properties(std::string const &layer_name) const
{
  std::uint32_t count = 0;
  switch(vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of device memory");
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: layer not present");
    default :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: unknown error");
  }
  std::vector<VkExtensionProperties> properties(count);
  vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, properties.data());
  return properties;
}

physical_device::physical_device(VkPhysicalDevice &&physical_device) noexcept
: physical_device_(std::move(physical_device))
{
}
}