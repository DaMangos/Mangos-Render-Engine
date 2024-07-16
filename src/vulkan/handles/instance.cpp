#include "internal/create_unique_handle.hpp"
#include <vulkan/handles/instance.hpp>
#include <vulkan/handles/physical_device.hpp>

#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

std::pair<vulkan::instance, VkResult const> vulkan::create_instance(VkInstanceCreateInfo const & info)
{
  VkInstance handle = VK_NULL_HANDLE;
  auto const result = vkCreateInstance(&info, nullptr, &handle);

  if(static_cast<int>(result) < 0)
    return {nullhandle, result};

  instance instance;
  instance._instance = std::shared_ptr<VkInstance_T>(handle, [](auto const handle) { vkDestroyInstance(handle, nullptr); });
  return {std::move(instance), result};
}

std::pair<vulkan::instance, VkResult const> vulkan::create_instance(VkInstanceCreateInfo const &  info,
                                                                    VkAllocationCallbacks const & allocation_callbacks)
{
  auto const shared_allocation_callbacks = std::make_shared<VkAllocationCallbacks const>(allocation_callbacks);

  VkInstance handle = VK_NULL_HANDLE;
  auto const result = vkCreateInstance(&info, shared_allocation_callbacks.get(), &handle);

  if(static_cast<int>(result) < 0)
    return {nullhandle, result};

  std::shared_ptr<VkInstance_T> shared_instance(handle,
                                                [shared_allocation_callbacks](auto const handle)
                                                { vkDestroyInstance(handle, shared_allocation_callbacks.get()); });

  instance instance;
  instance._instance             = shared_instance;
  instance._allocation_callbacks = shared_allocation_callbacks;

  return {std::move(instance), result};
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
  VkDebugReportCallbackCreateInfoEXT const & info)
{
  return internal::create_unique_handle<VkDebugReportCallbackEXT, ext::create_debug_report_callback, ext::destroy_debug_report_callback>(
    _instance,
    &info,
    _allocation_callbacks);
}

std::pair<vulkan::ext::debug_utils_messenger, VkResult const> vulkan::instance::create_debug_utils_messenger(
  VkDebugUtilsMessengerCreateInfoEXT const & info)
{
  return internal::create_unique_handle<VkDebugUtilsMessengerEXT, ext::create_debug_utils_messenger, ext::destroy_debug_utils_messenger>(
    _instance,
    &info,
    _allocation_callbacks);
}

std::pair<vulkan::khr::surface, VkResult const> vulkan::instance::create_surface(GLFWwindow * const window)
{
  return internal::create_unique_handle<VkSurfaceKHR, glfwCreateWindowSurface, vkDestroySurfaceKHR>(_instance, window, _allocation_callbacks);
}

std::pair<std::vector<vulkan::physical_device>, VkResult const> vulkan::instance::enumerate_physical_devices()
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
                         [this](auto const handle)
                         {
                           physical_device physical_device;
                           physical_device._instance             = _instance;
                           physical_device._physical_device      = handle;
                           physical_device._allocation_callbacks = _allocation_callbacks;
                           return physical_device;
                         });

  return {std::move(physical_devices), second_result};
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
