#include "physical_device.hpp"

#include "device.hpp"
#include "instance.hpp"

namespace vulkan
{
device physical_device::create_device(VkDeviceCreateInfo const &create_info) const
{
  VkDevice ptr = VK_NULL_HANDLE;
  switch(vkCreateDevice(get(), &create_info, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return {_dispatcher, ptr};
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

constexpr VkPhysicalDevice physical_device::get() const noexcept
{
  return _ptr;
}

bool physical_device::check_surface_support(VkSurfaceKHR const surface, std::uint32_t const queue_family) const
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

VkSurfaceCapabilitiesKHR physical_device::get_surface_capabilities(VkSurfaceKHR const surface) const
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

std::pair<std::vector<VkSurfaceFormatKHR>, VkResult> physical_device::get_surface_formats(VkSurfaceKHR const surface) const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      auto surface_formats = std::vector<VkSurfaceFormatKHR>(count);
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

std::pair<std::vector<VkPresentModeKHR>, VkResult> physical_device::get_present_modes(VkSurfaceKHR const surface) const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      auto present_modes = std::vector<VkPresentModeKHR>(count);
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
  auto features = VkPhysicalDeviceFeatures{};
  vkGetPhysicalDeviceFeatures(get(), &features);
  return features;
}

VkPhysicalDeviceProperties physical_device::get_properties() const noexcept
{
  auto properties = VkPhysicalDeviceProperties{};
  vkGetPhysicalDeviceProperties(get(), &properties);
  return properties;
}

std::vector<VkQueueFamilyProperties> physical_device::get_queue_family_properties() const
{
  std::uint32_t count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, nullptr);
  auto properties = std::vector<VkQueueFamilyProperties>(count);
  vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, properties.data());
  return properties;
}

std::pair<std::vector<VkExtensionProperties>, VkResult> physical_device::get_extension_properties() const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr); result)
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      auto properties = std::vector<VkExtensionProperties>(count);
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
      auto properties = std::vector<VkExtensionProperties>(count);
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
                                 VkPhysicalDevice const                                                ptr) noexcept
: _dispatcher(instance),
  _ptr(ptr)
{
}
}