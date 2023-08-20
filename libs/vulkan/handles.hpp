#pragma once

#include <mgo/memory.hpp>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
using buffer_handle                = mgo::unique_handle<1, VkDevice, VkBuffer, VkAllocationCallbacks const *>;
using buffer_view_handle           = mgo::unique_handle<1, VkDevice, VkBufferView, VkAllocationCallbacks const *>;
using command_buffers_handle       = mgo::unique_handle<3, VkDevice, VkCommandPool, std::uint32_t, VkCommandBuffer const *>;
using command_pool_handle          = mgo::shared_handle<1, VkDevice, VkCommandPool, VkAllocationCallbacks const *>;
using descriptor_pool_handle       = mgo::shared_handle<1, VkDevice, VkDescriptorPool, VkAllocationCallbacks const *>;
using descriptor_set_layout_handle = mgo::unique_handle<1, VkDevice, VkDescriptorSetLayout, VkAllocationCallbacks const *>;
using descriptor_sets_handle       = mgo::unique_handle<3, VkDevice, VkDescriptorPool, std::uint32_t, VkDescriptorSet const *>;
using device_handle                = mgo::shared_handle<0, VkDevice, VkAllocationCallbacks const *>;
using device_memory_handle         = mgo::unique_handle<1, VkDevice, VkDeviceMemory, VkAllocationCallbacks const *>;
using event_handle                 = mgo::unique_handle<1, VkDevice, VkEvent, VkAllocationCallbacks const *>;
using fence_handle                 = mgo::unique_handle<1, VkDevice, VkFence, VkAllocationCallbacks const *>;
using framebuffer_handle           = mgo::unique_handle<1, VkDevice, VkFramebuffer, VkAllocationCallbacks const *>;
using image_handle                 = mgo::unique_handle<1, VkDevice, VkImage, VkAllocationCallbacks const *>;
using image_view_handle            = mgo::unique_handle<1, VkDevice, VkImageView, VkAllocationCallbacks const *>;
using instance_handle              = mgo::shared_handle<0, VkInstance, VkAllocationCallbacks const *>;
using pipeline_cache_handle        = mgo::unique_handle<1, VkDevice, VkPipelineCache, VkAllocationCallbacks const *>;
using pipeline_handle              = mgo::unique_handle<1, VkDevice, VkPipeline, VkAllocationCallbacks const *>;
using pipeline_layout_handle       = mgo::unique_handle<1, VkDevice, VkPipelineLayout, VkAllocationCallbacks const *>;
using query_pool_handle            = mgo::unique_handle<1, VkDevice, VkQueryPool, VkAllocationCallbacks const *>;
using render_pass_handle           = mgo::unique_handle<1, VkDevice, VkRenderPass, VkAllocationCallbacks const *>;
using sampler_handle               = mgo::unique_handle<1, VkDevice, VkSampler, VkAllocationCallbacks const *>;
using semaphore_handle             = mgo::unique_handle<1, VkDevice, VkSemaphore, VkAllocationCallbacks const *>;
using shader_module_handle         = mgo::unique_handle<1, VkDevice, VkShaderModule, VkAllocationCallbacks const *>;

namespace ext
{
using debug_report_callback_handle = mgo::unique_handle<1, VkInstance, VkDebugReportCallbackEXT, VkAllocationCallbacks const *>;
using debug_utils_messenger_handle = mgo::unique_handle<1, VkInstance, VkDebugUtilsMessengerEXT, VkAllocationCallbacks const *>;
}

namespace khr
{
using surface_handle   = mgo::unique_handle<1, VkInstance, VkSurfaceKHR, VkAllocationCallbacks const *>;
using swapchain_handle = mgo::unique_handle<1, VkDevice, VkSwapchainKHR, VkAllocationCallbacks const *>;
}
}