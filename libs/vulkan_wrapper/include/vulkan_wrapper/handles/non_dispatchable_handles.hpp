#pragma once

#include <vulkan_wrapper/handles/non_loaded_functions.hpp>

namespace vulkan
{
inline namespace version_1_0
{
template <class Dispatcher, class Handle, auto DeleteHandle>
class unique_handle;

template <class Dispatcher, class Handle, auto DeleteHandle>
class shared_handle;

template <class Handle>
class range_element_handle;

using buffer                = unique_handle<VkDevice, VkBuffer, vkDestroyBuffer>;
using buffer_view           = unique_handle<VkDevice, VkBufferView, vkDestroyBufferView>;
using descriptor_set_layout = unique_handle<VkDevice, VkDescriptorSetLayout, vkDestroyDescriptorSetLayout>;
using device_memory         = unique_handle<VkDevice, VkDeviceMemory, vkFreeMemory>;
using event                 = unique_handle<VkDevice, VkEvent, vkDestroyEvent>;
using fence                 = unique_handle<VkDevice, VkFence, vkDestroyFence>;
using framebuffer           = unique_handle<VkDevice, VkFramebuffer, vkDestroyFramebuffer>;
using image                 = unique_handle<VkDevice, VkImage, vkDestroyImage>;
using image_view            = unique_handle<VkDevice, VkImageView, vkDestroyImageView>;
using pipeline              = unique_handle<VkDevice, VkPipeline, vkDestroyPipeline>;
using pipeline_cache        = unique_handle<VkDevice, VkPipelineCache, vkDestroyPipelineCache>;
using pipeline_layout       = unique_handle<VkDevice, VkPipelineLayout, vkDestroyPipelineLayout>;
using query_pool            = unique_handle<VkDevice, VkQueryPool, vkDestroyQueryPool>;
using render_pass           = unique_handle<VkDevice, VkRenderPass, vkDestroyRenderPass>;
using sampler               = unique_handle<VkDevice, VkSampler, vkDestroySampler>;
using semaphore             = unique_handle<VkDevice, VkSemaphore, vkDestroySemaphore>;
using shader_module         = unique_handle<VkDevice, VkShaderModule, vkDestroyShaderModule>;
using command_pool          = shared_handle<VkDevice, VkCommandPool, vkDestroyCommandPool>;
using descriptor_pool       = shared_handle<VkDevice, VkDescriptorPool, vkDestroyDescriptorPool>;
using command_buffer        = range_element_handle<VkCommandBuffer>;
using descriptor_set        = range_element_handle<VkDescriptorSet>;
}
}

namespace vulkan::khr
{
inline namespace version_1_0
{
using swapchain = unique_handle<VkDevice, VkSwapchainKHR, vkDestroySwapchainKHR>;
using surface   = unique_handle<VkInstance, VkSurfaceKHR, vkDestroySurfaceKHR>;
}
}

namespace vulkan::ext
{
inline namespace version_1_0
{
using debug_report_callback = unique_handle<VkInstance, VkDebugReportCallbackEXT, destroy_debug_report_callback>;
using debug_utils_messenger = unique_handle<VkInstance, VkDebugUtilsMessengerEXT, destroy_debug_utils_messenger>;
}

}