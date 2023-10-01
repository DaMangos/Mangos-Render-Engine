#include "physical_device.hpp"

#include "device.hpp"
#include "instance.hpp"

namespace vulkan
{
VkPhysicalDevice physical_device::get() const noexcept
{
  return _ptr;
}

device physical_device::create_device(VkDeviceCreateInfo create_info) const
{
  VkDevice ptr;
  switch(vkCreateDevice(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return device(_dispatcher, ptr);
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

std::pair<std::vector<VkSurfaceFormatKHR>, VkResult> physical_device::get_surface_formats(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      std::vector<VkSurfaceFormatKHR> surface_formats(count);
      vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, surface_formats.data());
      return std::make_pair(std::move(surface_formats), result);
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkSurfaceFormatKHR: unknown error");
  }
}

std::pair<std::vector<VkPresentModeKHR>, VkResult> physical_device::get_present_modes(VkSurfaceKHR surface) const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      std::vector<VkPresentModeKHR> present_modes(count);
      vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, present_modes.data());
      return std::make_pair(std::move(present_modes), result);
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to get VkPresentModeKHR: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to get VkPresentModeKHR: out of device memory");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error("failed to get VkPresentModeKHR: surface lost");
    default :
      throw std::runtime_error("failed to get VkPresentModeKHR: unknown error");
  }
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

std::pair<std::vector<VkExtensionProperties>, VkResult> physical_device::get_extension_properties() const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      std::vector<VkExtensionProperties> properties(count);
      vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, properties.data());
      return std::make_pair(std::move(properties), result);
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of device memory");
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: layer not present");
    default :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: unknown error");
  }
}

std::pair<std::vector<VkExtensionProperties>, VkResult>
physical_device::get_extension_properties(std::string const &layer_name) const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      std::vector<VkExtensionProperties> properties(count);
      vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, properties.data());
      return std::make_pair(std::move(properties), result);
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: out of device memory");
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: layer not present");
    default :
      throw std::runtime_error("failed to enumerate VkExtensionProperties: unknown error");
  }
}

physical_device::physical_device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &instance,
                                 VkPhysicalDevice                                                      ptr) noexcept
: _dispatcher(instance),
  _ptr(ptr)
{
}
}