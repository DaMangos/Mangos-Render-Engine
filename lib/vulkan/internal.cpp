#include "internal.hpp"

namespace vulkan::ext::internal
{
VkResult create_debug_utils_messenger(VkInstance                                dispatcher,
                                      VkDebugUtilsMessengerCreateInfoEXT const *info,
                                      VkAllocationCallbacks const              *allocator,
                                      VkDebugUtilsMessengerEXT                 *ptr) noexcept
{
  return std::invoke(
    reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(dispatcher, "vkCreateDebugUtilsMessengerEXT")),
    dispatcher,
    info,
    allocator,
    ptr);
};

VkResult create_debug_report_callback(VkInstance                                dispatcher,
                                      VkDebugReportCallbackCreateInfoEXT const *info,
                                      VkAllocationCallbacks const              *allocator,
                                      VkDebugReportCallbackEXT                 *ptr) noexcept
{
  return std::invoke(
    reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(dispatcher, "vkCreateDebugReportCallbackEXT")),
    dispatcher,
    info,
    allocator,
    ptr);
};

void destroy_debug_report_callback(VkInstance                   dispatcher,
                                   VkDebugReportCallbackEXT     ptr,
                                   VkAllocationCallbacks const *allocator) noexcept
{
  std::invoke(
    reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(dispatcher, "vkDestroyDebugReportCallbackEXT")),
    dispatcher,
    ptr,
    allocator);
};

void destroy_debug_utils_messenger(VkInstance                   dispatcher,
                                   VkDebugUtilsMessengerEXT     ptr,
                                   VkAllocationCallbacks const *allocator) noexcept
{
  std::invoke(
    reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(dispatcher, "vkDestroyDebugUtilsMessengerEXT")),
    dispatcher,
    ptr,
    allocator);
};
}