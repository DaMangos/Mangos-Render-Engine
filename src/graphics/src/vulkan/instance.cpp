#include "instance.hpp"

namespace graphics::vulkan
{
unique_handle<VkInstance> create_instance(VkInstanceCreateInfo create_info)
{
  VkInstance instance;
  return return_or_throw(vkCreateInstance(&create_info, nullptr, &instance), "vkCreateInstance", make_unique_handle(instance));
}

instance::instance(unique_handle<VkInstance> underling_instance) noexcept
: _underling_instance(std::move(underling_instance))
{
}

VkInstance instance::get() const noexcept
{
  return _underling_instance.get();
}

std::vector<VkPhysicalDevice> instance::enumerate_Physical_device() const
{
  std::uint32_t count = 0;
  vkEnumeratePhysicalDevices(get(), &count, nullptr);
  std::vector<VkPhysicalDevice> physical_devices(count);
  return return_or_throw(vkEnumeratePhysicalDevices(get(), &count, physical_devices.data()),
                         "vkEnumeratePhysicalDevices",
                         physical_devices);
}

unique_handle<VkDebugUtilsMessengerEXT>
instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const
{
  VkDebugUtilsMessengerEXT debug_utils_messenger;
  return return_or_throw(invoke<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT",
                                                                    get(),
                                                                    &create_info,
                                                                    nullptr,
                                                                    &debug_utils_messenger),
                         "vkCreateDebugUtilsMessengerEXT",
                         make_unique_handle(debug_utils_messenger, get()));
}

unique_handle<VkDebugReportCallbackEXT>
instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const
{
  VkDebugReportCallbackEXT debug_report_callback;
  return return_or_throw(invoke<PFN_vkCreateDebugReportCallbackEXT>("vkCreateDebugReportCallbackEXT",
                                                                    get(),
                                                                    &create_info,
                                                                    nullptr,
                                                                    &debug_report_callback),
                         "vkCreateDebugReportCallbackEXT",
                         make_unique_handle(debug_report_callback, get()));
}

unique_handle<VkSurfaceKHR> instance::create_surface(GLFWwindow *window) const
{
  VkSurfaceKHR surface;
  return return_or_throw(glfwCreateWindowSurface(get(), window, nullptr, &surface),
                         "glfwCreateWindowSurface",
                         make_unique_handle(surface, get()));
}
}