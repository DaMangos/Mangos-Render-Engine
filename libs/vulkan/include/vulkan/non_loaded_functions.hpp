#pragma once

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan::ext
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