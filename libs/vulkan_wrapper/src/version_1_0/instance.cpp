#include <vulkan_wrapper/version_1_0/instance.hpp>

#include "internal.hpp"
#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

std::pair<vulkan::instance, VkResult const> vulkan::create_instance(VkInstanceCreateInfo const & info) noexcept
{
  try
  {
    VkInstance handle = VK_NULL_HANDLE;
    auto const result = vkCreateInstance(&info, nullptr, &handle);

    if(static_cast<int>(result) < 0)
      return {nullhandle, result};

    return {internal::make_instance(std::shared_ptr<VkInstance_T>(handle, [](auto const handle) { vkDestroyInstance(handle, nullptr); }), nullptr),
            result};
  }
  catch(std::exception const &)
  {
    return {nullhandle, VK_ERROR_UNKNOWN};
  }
}

std::pair<vulkan::instance, VkResult const> vulkan::create_instance(VkInstanceCreateInfo const &  info,
                                                                    VkAllocationCallbacks const & allocation_callbacks) noexcept
{
  try
  {
    auto const shared_allocation_callbacks = std::make_shared<VkAllocationCallbacks const>(allocation_callbacks);

    VkInstance handle = VK_NULL_HANDLE;
    auto const result = vkCreateInstance(&info, shared_allocation_callbacks.get(), &handle);

    if(static_cast<int>(result) < 0)
      return {nullhandle, result};

    return {internal::make_instance(std::shared_ptr<VkInstance_T>(handle,
                                                                  [shared_allocation_callbacks](auto const handle)
                                                                  { vkDestroyInstance(handle, shared_allocation_callbacks.get()); }),
                                    shared_allocation_callbacks),
            result};
  }
  catch(std::exception const &)
  {
    return {nullhandle, VK_ERROR_UNKNOWN};
  }
}

VkInstance vulkan::instance::get() const noexcept
{
  return _instance.get();
}

VkAllocationCallbacks const * vulkan::instance::get_allocation_callbacks() const noexcept
{
  return _allocation_callbacks.get();
}

std::pair<vulkan::ext::debug_report_callback, VkResult const> vulkan::instance::create_debug_report_callback(
  VkDebugReportCallbackCreateInfoEXT const & info) noexcept
{
  return internal::create_unique_handle<VkDebugReportCallbackEXT, ext::create_debug_report_callback, ext::destroy_debug_report_callback>(
    _instance,
    &info,
    _allocation_callbacks);
}

std::pair<vulkan::ext::debug_utils_messenger, VkResult const> vulkan::instance::create_debug_utils_messenger(
  VkDebugUtilsMessengerCreateInfoEXT const & info) noexcept
{
  return internal::create_unique_handle<VkDebugUtilsMessengerEXT, ext::create_debug_utils_messenger, ext::destroy_debug_utils_messenger>(
    _instance,
    &info,
    _allocation_callbacks);
}

std::pair<vulkan::khr::surface, VkResult const> vulkan::instance::create_surface(GLFWwindow * const window) noexcept
{
  return internal::create_unique_handle<VkSurfaceKHR, glfwCreateWindowSurface, vkDestroySurfaceKHR>(_instance, window, _allocation_callbacks);
}

std::pair<std::vector<vulkan::physical_device>, VkResult const> vulkan::instance::enumerate_physical_devices() noexcept
{
  try
  {
    std::uint32_t count = 0;

    auto const first_result = vkEnumeratePhysicalDevices(_instance.get(), &count, nullptr);

    if(static_cast<int>(first_result) < 0)
      return {std::vector<physical_device>(), first_result};

    std::vector<VkPhysicalDevice> handles(count, VK_NULL_HANDLE);

    auto const second_result = vkEnumeratePhysicalDevices(_instance.get(), &count, handles.data());

    if(static_cast<int>(second_result) < 0)
      return {std::vector<physical_device>(), second_result};

    std::vector<physical_device> physical_devices;

    std::ranges::transform(handles,
                           std::back_inserter(physical_devices),
                           [instance = _instance, allocation_callbacks = _allocation_callbacks](auto const handle)
                           { return internal::make_physical_device(instance, handle, allocation_callbacks); });

    return {std::move(physical_devices), second_result};
  }
  catch(std::exception const &)
  {
    return {std::vector<physical_device>(), VK_ERROR_UNKNOWN};
  }
}

void vulkan::instance::reset() noexcept
{
  _instance.reset();
  _allocation_callbacks.reset();
}

vulkan::instance::instance(nullhandle_t) noexcept
{
}

vulkan::instance & vulkan::instance::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

std::strong_ordering vulkan::instance::operator<=>(instance const & other) const noexcept
{
  return _instance <=> other._instance;
}

std::strong_ordering vulkan::instance::operator<=>(nullhandle_t) const noexcept
{
  return _instance <=> nullptr;
}

vulkan::instance::operator bool() const noexcept
{
  return static_cast<bool>(_instance);
}
