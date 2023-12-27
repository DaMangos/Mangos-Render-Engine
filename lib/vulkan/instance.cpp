#include "instance.hpp"

#include "non_dispatchable_handles.hpp"
#include "physical_device.hpp"

#include <algorithm>
#include <iterator>

namespace vulkan
{
instance::instance(VkInstanceCreateInfo const &info)
: _smart_ptr(
    [&info]()
    {
      auto       ptr    = VkInstance{};
      auto const result = vkCreateInstance(&info, nullptr, &ptr);
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult (" + std::to_string(result) +
                                 ")");
      return ptr;
    }(),
    [](VkInstance const ptr) { vkDestroyInstance(ptr, nullptr); })
{
}

std::pair<std::vector<physical_device>, VkResult const> instance::enumerate_physical_devices() const
{
  std::uint32_t count = 0;
  vkEnumeratePhysicalDevices(get(), &count, nullptr);
  auto ptrs = std::vector<VkPhysicalDevice>(count);
  auto return_value =
    std::pair<std::vector<physical_device>, VkResult const>({}, vkEnumeratePhysicalDevices(get(), &count, ptrs.data()));
  if(std::to_underlying(return_value.second) < 0)
    throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                             ":\033[1;31m error:\033[0m vulkan return a negative VkResult (" +
                             std::to_string(return_value.second) + ")");
  std::ranges::transform(ptrs,
                         std::back_inserter(return_value.first),
                         [this](auto const ptr) { return physical_device(_smart_ptr, ptr); });
  return return_value;
}

ext::debug_utils_messenger instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &info) const
{
  return internal::make_unique<ext::internal::create_debug_utils_messenger,
                               ext::internal::destroy_debug_utils_messenger,
                               VkDebugUtilsMessengerEXT>(_smart_ptr, &info);
}

ext::debug_report_callback instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &info) const
{
  return internal::make_unique<ext::internal::create_debug_report_callback,
                               ext::internal::destroy_debug_report_callback,
                               VkDebugReportCallbackEXT>(_smart_ptr, &info);
}

khr::surface instance::create_surface(GLFWwindow *const window) const
{
  return internal::make_unique<glfwCreateWindowSurface, vkDestroySurfaceKHR, VkSurfaceKHR>(_smart_ptr, window);
}
}
