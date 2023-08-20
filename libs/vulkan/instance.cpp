#include "instance.hpp"

#include "physical_device.hpp"

namespace vulkan
{
instance::instance(VkInstanceCreateInfo create_info)
: _instance(
    [](VkInstanceCreateInfo &create_info) -> instance_handle
    {
      VkInstance      ptr;
      VkResult        result = vkCreateInstance(&create_info, nullptr, &ptr);
      instance_handle handle(vkDestroyInstance, ptr, nullptr);
      switch(result)
      {
        case VK_SUCCESS :
          return handle;
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
    }(create_info))
{
}

VkInstance instance::get() const noexcept
{
  return _instance.get();
}

std::vector<physical_device> instance::enumerate_physical_device() const
{
  std::uint32_t count;
  switch(vkEnumeratePhysicalDevices(get(), &count, nullptr))
  {
    case VK_SUCCESS | VK_INCOMPLETE :
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: out of device memory");
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: initialization failed");
    default :
      throw std::runtime_error("failed to enumerate VkPhysicalDevice: unknown error");
  }
  std::vector<VkPhysicalDevice> ptrs(count);
  vkEnumeratePhysicalDevices(get(), &count, ptrs.data());
  return std::vector<physical_device>(ptrs.begin(), ptrs.end());
}

ext::debug_utils_messenger instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const
{
  VkDebugUtilsMessengerEXT ptr;
  VkResult result = std::invoke(get_proc_addr<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT"),
                                get(),
                                &create_info,
                                nullptr,
                                &ptr);
  ext::debug_utils_messenger_handle handle(
    get_proc_addr<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT"),
    get(),
    ptr,
    nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return ext::debug_utils_messenger(_instance, std::move(handle));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDebugUtilsMessengerEXT: out of host memory");
    default :
      throw std::runtime_error("failed to create VkDebugUtilsMessengerEXT: unknown error");
  }
}

ext::debug_report_callback instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const
{
  VkDebugReportCallbackEXT ptr;
  VkResult result = std::invoke(get_proc_addr<PFN_vkCreateDebugReportCallbackEXT>("vkCreateDebugReportCallbackEXT"),
                                get(),
                                &create_info,
                                nullptr,
                                &ptr);
  ext::debug_report_callback_handle handle(
    get_proc_addr<PFN_vkDestroyDebugReportCallbackEXT>("vkDestroyDebugReportCallbackEXT"),
    get(),
    ptr,
    nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return ext::debug_report_callback(_instance, std::move(handle));
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error("failed to create VkDebugReportCallbackEXT: out of host memory");
    default :
      throw std::runtime_error("failed to create VkDebugReportCallbackEXT: unknown error");
  }
}

khr::surface instance::create_surface(GLFWwindow *window) const
{
  VkSurfaceKHR        ptr;
  VkResult            result = glfwCreateWindowSurface(get(), window, nullptr, &ptr);
  khr::surface_handle handle(vkDestroySurfaceKHR, get(), ptr, nullptr);
  switch(result)
  {
    case VK_SUCCESS :
      return khr::surface(_instance, std::move(handle));
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