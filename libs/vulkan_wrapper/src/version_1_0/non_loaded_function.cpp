#include <vulkan_wrapper/version_1_0/non_loaded_functions.hpp>

VkResult vulkan::ext::create_debug_report_callback(VkInstance                                 instance,
                                                   VkDebugReportCallbackCreateInfoEXT const * info,
                                                   VkAllocationCallbacks const *              allocator,
                                                   VkDebugReportCallbackEXT *                 callback) noexcept
{
  auto const create = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
  return create ? create(instance, info, allocator, callback) : VK_ERROR_EXTENSION_NOT_PRESENT;
}

VkResult vulkan::ext::create_debug_utils_messenger(VkInstance                                 instance,
                                                   VkDebugUtilsMessengerCreateInfoEXT const * info,
                                                   VkAllocationCallbacks const *              allocator,
                                                   VkDebugUtilsMessengerEXT *                 messenger) noexcept
{
  auto const create = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
  return create ? create(instance, info, allocator, messenger) : VK_ERROR_EXTENSION_NOT_PRESENT;
}

void vulkan::ext::destroy_debug_report_callback(VkInstance                    instance,
                                                VkDebugReportCallbackEXT      callback,
                                                VkAllocationCallbacks const * allocator) noexcept
{
  auto const destroy = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
  if(destroy)
    destroy(instance, callback, allocator);
}

void vulkan::ext::destroy_debug_utils_messenger(VkInstance                    instance,
                                                VkDebugUtilsMessengerEXT      messenger,
                                                VkAllocationCallbacks const * allocator) noexcept
{
  auto const destroy = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
  if(destroy)
    destroy(instance, messenger, allocator);
}
