#include "instance.hpp"

#include "physical_device.hpp"

namespace vulkan
{
instance::instance(VkInstanceCreateInfo const &create_info)
: _handle(
    [&create_info]()
    {
      VkInstance ptr = VK_NULL_HANDLE;
      switch(vkCreateInstance(&create_info, nullptr, &ptr))
      {
        case VK_SUCCESS :
          return ptr = VK_NULL_HANDLE;
        case VK_ERROR_OUT_OF_HOST_MEMORY :
          throw std::runtime_error("failed to create VkInstance: out of host memory");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY :
          throw std::runtime_error("failed to create VkInstance: out of device memory");
        case VK_ERROR_INITIALIZATION_FAILED :
          throw std::runtime_error("failed to create VkInstance: initialization failed");
        case VK_ERROR_LAYER_NOT_PRESENT :
          throw std::runtime_error("failed to create VkInstance: layer not present");
        case VK_ERROR_EXTENSION_NOT_PRESENT :
          throw std::runtime_error("failed to create VkInstance: extension not present");
        case VK_ERROR_INCOMPATIBLE_DRIVER :
          throw std::runtime_error("failed to create VkInstance: incompatible driver");
        default :
          throw std::runtime_error("failed to create VkInstance: unknown error");
      }
    }(),
    [](VkInstance ptr) { vkDestroyInstance(ptr, nullptr); })
{
}

std::pair<std::vector<physical_device>, VkResult> instance::enumerate_physical_devices() const
{
  std::uint32_t count = 0;
  switch(VkResult result = vkEnumeratePhysicalDevices(get(), &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
    {
      std::vector<VkPhysicalDevice> ptrs(count);
      vkEnumeratePhysicalDevices(get(), &count, ptrs.data());
      std::vector<physical_device> physical_devices;
      physical_devices.reserve(count);
      for(VkPhysicalDevice ptr : ptrs)
        physical_devices.emplace_back(physical_device(_handle, ptr));
      return std::make_pair(std::move(physical_devices), result);
    }
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: out of device memory");
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: initialization failed");
    default :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: unknown error");
  }
}

ext::debug_utils_messenger instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &create_info) const
{
  VkDebugUtilsMessengerEXT ptr = VK_NULL_HANDLE;
  switch(std::invoke(get_proc_addr<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT"),
                     get(),
                     &create_info,
                     nullptr,
                     &ptr))
  {
    case VK_SUCCESS :
      return ext::debug_utils_messenger(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDebugUtilsMessengerEXT: out of host memory");
    default :
      throw std::runtime_error("failed to create VkDebugUtilsMessengerEXT: unknown error");
  }
}

ext::debug_report_callback instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &create_info) const
{
  VkDebugReportCallbackEXT ptr = VK_NULL_HANDLE;
  switch(std::invoke(get_proc_addr<PFN_vkCreateDebugReportCallbackEXT>("vkCreateDebugReportCallbackEXT"),
                     get(),
                     &create_info,
                     nullptr,
                     &ptr))
  {
    case VK_SUCCESS :
      return ext::debug_report_callback(_handle, ptr);
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDebugReportCallbackEXT: out of host memory");
    default :
      throw std::runtime_error("failed to create VkDebugReportCallbackEXT: unknown error");
  }
}

khr::surface instance::create_surface(GLFWwindow *const window_ptr) const
{
  VkSurfaceKHR ptr = VK_NULL_HANDLE;
  switch(glfwCreateWindowSurface(get(), window_ptr, nullptr, &ptr))
  {
    case VK_SUCCESS :
      return khr::surface(_handle, ptr);
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error("failed to create VkSurfaceKHR: initialization failed");
    case VK_ERROR_EXTENSION_NOT_PRESENT :
      throw std::runtime_error("failed to create VkSurfaceKHR: extension not present");
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
      throw std::runtime_error("failed to create VkSurfaceKHR: native window in use");
    default :
      throw std::runtime_error("failed to create VkSurfaceKHR: unknown error");
  }
}
}