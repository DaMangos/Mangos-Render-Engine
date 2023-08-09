#include "instance.hpp"

#include "functional.hpp"
#include "physical_device.hpp"

namespace vulkan
{
instance create_instance(VkInstanceCreateInfo create_info)
{
  instance::pointer ptr;
  return return_or_throw<instance>(vkCreateInstance(&create_info, nullptr, &ptr),
                                   "vkCreateInstance",
                                   instance(ptr, [](instance::pointer ptr) -> void { vkDestroyInstance(ptr, nullptr); }));
}

instance::instance(pointer instance, deleter_type &&deleter)
: _instance(instance, deleter)
{
}

instance::pointer instance::get() const noexcept
{
  return _instance.get();
}

std::vector<physical_device> instance::enumerate_physical_device() const
{
  std::uint32_t count = 0;
  vkEnumeratePhysicalDevices(get(), &count, nullptr);
  std::vector<physical_device::pointer> ptrs(count);
  return return_or_throw(vkEnumeratePhysicalDevices(get(), &count, ptrs.data()),
                         "vkEnumeratePhysicalDevices",
                         [&]() -> std::vector<physical_device>
                         {
                           std::vector<physical_device> physical_devices;
                           for(auto ptr : ptrs)
                             physical_devices.emplace_back(physical_device(ptr));
                           return physical_devices;
                         }());
}

ext::debug_utils_messenger instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const
{
  ext::debug_utils_messenger::pointer ptr;
  return return_or_throw(
    invoke<PFN_vkCreateDebugUtilsMessengerEXT>(get(), "vkCreateDebugUtilsMessengerEXT", get(), &create_info, nullptr, &ptr),
    "vkCreateDebugUtilsMessengerEXT",
    ext::debug_utils_messenger(
      ptr,
      [instance = get()](ext::debug_utils_messenger::pointer ptr) -> void
      { invoke<PFN_vkDestroyDebugUtilsMessengerEXT>(instance, "vkDestroyDebugUtilsMessengerEXT", instance, ptr, nullptr); }));
}

ext::debug_report_callback instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const
{
  ext::debug_report_callback::pointer ptr;
  return return_or_throw(
    invoke<PFN_vkCreateDebugReportCallbackEXT>(get(), "vkCreateDebugReportCallbackEXT", get(), &create_info, nullptr, &ptr),
    "vkCreateDebugReportCallbackEXT",
    ext::debug_report_callback(
      ptr,
      [instance = get()](ext::debug_report_callback::pointer ptr) -> void
      { invoke<PFN_vkDestroyDebugReportCallbackEXT>(instance, "vkDestroyDebugReportCallbackEXT", instance, ptr, nullptr); }));
}

khr::surface instance::create_surface(GLFWwindow *window) const
{
  khr::surface::pointer ptr;
  return return_or_throw(
    glfwCreateWindowSurface(get(), window, nullptr, &ptr),
    "glfwCreateWindowSurface",
    khr::surface(ptr, [instance = get()](khr::surface::pointer ptr) -> void { vkDestroySurfaceKHR(instance, ptr, nullptr); }));
}

}