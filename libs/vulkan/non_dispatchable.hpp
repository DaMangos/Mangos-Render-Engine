#pragma once

#include <mgo/memory.hpp>

#define ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
template <auto func_pointer, class dispatcher_pointer, class pointer>
struct non_dispatchable
{
    [[nodiscard]]
    constexpr pointer get() const noexcept
    {
      return handle_.template get<1>();
    }

  private:
    friend struct device;
    friend struct instance;

    constexpr non_dispatchable(dispatcher_pointer dispatcher, pointer &&ptr) noexcept
    : handle_(dispatcher, std::move(ptr))
    {
    }

    mgo::apply_in_destructor<[](dispatcher_pointer dispatcher, pointer ptr) { func_pointer(dispatcher, ptr, nullptr); },
                             dispatcher_pointer,
                             pointer>
      handle_;
};

using buffer                = non_dispatchable<vkDestroyBuffer, VkDevice, VkBuffer>;
using buffer_view           = non_dispatchable<vkDestroyBufferView, VkDevice, VkBufferView>;
using command_pool          = non_dispatchable<vkDestroyCommandPool, VkDevice, VkCommandPool>;
using descriptor_pool       = non_dispatchable<vkDestroyDescriptorPool, VkDevice, VkDescriptorPool>;
using descriptor_set_layout = non_dispatchable<vkDestroyDescriptorSetLayout, VkDevice, VkDescriptorSetLayout>;
using device_memory         = non_dispatchable<vkFreeMemory, VkDevice, VkDeviceMemory>;
using event                 = non_dispatchable<vkDestroyEvent, VkDevice, VkEvent>;
using fence                 = non_dispatchable<vkDestroyFence, VkDevice, VkFence>;
using framebuffer           = non_dispatchable<vkDestroyFramebuffer, VkDevice, VkFramebuffer>;
using image                 = non_dispatchable<vkDestroyImage, VkDevice, VkImage>;
using image_view            = non_dispatchable<vkDestroyImageView, VkDevice, VkImageView>;
using pipeline_cache        = non_dispatchable<vkDestroyPipelineCache, VkDevice, VkPipelineCache>;
using pipeline              = non_dispatchable<vkDestroyPipeline, VkDevice, VkPipeline>;
using pipeline_layout       = non_dispatchable<vkDestroyPipelineLayout, VkDevice, VkPipelineLayout>;
using query_pool            = non_dispatchable<vkDestroyQueryPool, VkDevice, VkQueryPool>;
using render_pass           = non_dispatchable<vkDestroyRenderPass, VkDevice, VkRenderPass>;
using sampler               = non_dispatchable<vkDestroySampler, VkDevice, VkSampler>;
using semaphore             = non_dispatchable<vkDestroySemaphore, VkDevice, VkSemaphore>;
using shader_module         = non_dispatchable<vkDestroyShaderModule, VkDevice, VkShaderModule>;

namespace ext
{
using debug_report_callback = non_dispatchable<
  [](VkInstance instance, VkDebugReportCallbackEXT debug_report_callback, VkAllocationCallbacks const *allocation_callbacks)
  {
    std::invoke(
      reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT")),
      instance,
      debug_report_callback,
      allocation_callbacks);
  },
  VkInstance,
  VkDebugReportCallbackEXT>;

using debug_utils_messenger = non_dispatchable<
  [](VkInstance instance, VkDebugUtilsMessengerEXT debug_utils_messenger, VkAllocationCallbacks const *allocation_callbacks)
  {
    std::invoke(
      reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")),
      instance,
      debug_utils_messenger,
      allocation_callbacks);
  },
  VkInstance,
  VkDebugUtilsMessengerEXT>;
}

namespace khr
{
using surface   = non_dispatchable<vkDestroySurfaceKHR, VkInstance, VkSurfaceKHR>;
using swapchain = non_dispatchable<vkDestroySwapchainKHR, VkDevice, VkSwapchainKHR>;
}
}