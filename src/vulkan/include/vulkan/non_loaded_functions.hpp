#pragma once

#include <vulkan/vulkan.h>

namespace vulkan::ext
{
VkResult create_debug_report_callback(VkInstance                                 instance,
                                      VkDebugReportCallbackCreateInfoEXT const * info,
                                      VkAllocationCallbacks const *              allocator,
                                      VkDebugReportCallbackEXT *                 callback);

VkResult create_debug_utils_messenger(VkInstance                                 instance,
                                      VkDebugUtilsMessengerCreateInfoEXT const * info,
                                      VkAllocationCallbacks const *              allocator,
                                      VkDebugUtilsMessengerEXT *                 messenger);

void destroy_debug_report_callback(VkInstance, VkDebugReportCallbackEXT, VkAllocationCallbacks const *);

void destroy_debug_utils_messenger(VkInstance, VkDebugUtilsMessengerEXT, VkAllocationCallbacks const *);
}