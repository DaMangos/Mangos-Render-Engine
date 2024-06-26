#pragma once

#include <vulkan/vulkan.h>

namespace vulkan::ext
{
inline namespace version_1_0
{
VkResult create_debug_report_callback(VkInstance                                 instance,
                                      VkDebugReportCallbackCreateInfoEXT const * info,
                                      VkAllocationCallbacks const *              allocator,
                                      VkDebugReportCallbackEXT *                 callback) noexcept;

VkResult create_debug_utils_messenger(VkInstance                                 instance,
                                      VkDebugUtilsMessengerCreateInfoEXT const * info,
                                      VkAllocationCallbacks const *              allocator,
                                      VkDebugUtilsMessengerEXT *                 messenger) noexcept;

void destroy_debug_report_callback(VkInstance, VkDebugReportCallbackEXT, VkAllocationCallbacks const *) noexcept;

void destroy_debug_utils_messenger(VkInstance, VkDebugUtilsMessengerEXT, VkAllocationCallbacks const *) noexcept;
}
}