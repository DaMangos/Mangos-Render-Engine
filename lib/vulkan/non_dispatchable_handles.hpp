#pragma once

#include "internal.hpp"

namespace vulkan
{
using buffer                = internal::unique_handle<vkDestroyBuffer, VkDevice, VkBuffer>;
using buffer_view           = internal::unique_handle<vkDestroyBufferView, VkDevice, VkBufferView>;
using descriptor_set_layout = internal::unique_handle<vkDestroyDescriptorSetLayout, VkDevice, VkDescriptorSetLayout>;
using device_memory         = internal::unique_handle<vkFreeMemory, VkDevice, VkDeviceMemory>;
using event                 = internal::unique_handle<vkDestroyEvent, VkDevice, VkEvent>;
using fence                 = internal::unique_handle<vkDestroyFence, VkDevice, VkFence>;
using framebuffer           = internal::unique_handle<vkDestroyFramebuffer, VkDevice, VkFramebuffer>;
using image                 = internal::unique_handle<vkDestroyImage, VkDevice, VkImage>;
using image_view            = internal::unique_handle<vkDestroyImageView, VkDevice, VkImageView>;
using pipeline_cache        = internal::unique_handle<vkDestroyPipelineCache, VkDevice, VkPipelineCache>;
using pipeline              = internal::unique_handle<vkDestroyPipeline, VkDevice, VkPipeline>;
using pipeline_layout       = internal::unique_handle<vkDestroyPipelineLayout, VkDevice, VkPipelineLayout>;
using query_pool            = internal::unique_handle<vkDestroyQueryPool, VkDevice, VkQueryPool>;
using render_pass           = internal::unique_handle<vkDestroyRenderPass, VkDevice, VkRenderPass>;
using sampler               = internal::unique_handle<vkDestroySampler, VkDevice, VkSampler>;
using semaphore             = internal::unique_handle<vkDestroySemaphore, VkDevice, VkSemaphore>;
using shader_module         = internal::unique_handle<vkDestroyShaderModule, VkDevice, VkShaderModule>;
using command_pool          = internal::shared_handle<vkDestroyCommandPool, VkDevice, VkCommandPool>;
using descriptor_pool       = internal::shared_handle<vkDestroyDescriptorPool, VkDevice, VkDescriptorPool>;
using command_buffers       = internal::collection_of_handles<vkFreeCommandBuffers, VkCommandBuffer, command_pool>;
using descriptor_sets       = internal::collection_of_handles<vkFreeDescriptorSets, VkDescriptorSet, descriptor_pool>;
}

namespace vulkan::ext
{
using debug_report_callback =
  ::vulkan::internal::unique_handle<internal::destroy_debug_report_callback, VkInstance, VkDebugReportCallbackEXT>;
using debug_utils_messenger =
  ::vulkan::internal::unique_handle<internal::destroy_debug_utils_messenger, VkInstance, VkDebugUtilsMessengerEXT>;
}

namespace vulkan::khr
{
using surface   = internal::unique_handle<vkDestroySurfaceKHR, VkInstance, VkSurfaceKHR>;
using swapchain = internal::unique_handle<vkDestroySwapchainKHR, VkDevice, VkSwapchainKHR>;
}