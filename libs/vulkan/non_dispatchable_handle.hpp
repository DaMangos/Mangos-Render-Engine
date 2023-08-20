#pragma once

#include <concepts>
#include <mgo/memory.hpp>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
struct command_buffers;
struct device;
struct instance;
struct physical_device;
struct queue;

template <class dispatcher_type, class handle_type>
struct non_dispatchable_handle
{
    using element_type = typename handle_type::element_type;
    using pointer      = typename handle_type::pointer;

    pointer get() const noexcept
    {
      return _handle.get();
    }

    VkDevice get_device() const noexcept requires std::same_as<typename dispatcher_type::pointer, VkDevice>
    {
      return _dispatcher.get();
    }

    VkInstance get_instance() const noexcept requires std::same_as<typename dispatcher_type::pointer, VkInstance>
    {
      return _dispatcher.get();
    }

    non_dispatchable_handle(non_dispatchable_handle const &) noexcept            = delete;
    non_dispatchable_handle &operator=(non_dispatchable_handle const &) noexcept = delete;
    non_dispatchable_handle(non_dispatchable_handle &&) noexcept                 = default;
    non_dispatchable_handle &operator=(non_dispatchable_handle &&) noexcept      = default;
    ~non_dispatchable_handle()                                                   = default;

  private:
    friend struct command_buffers;
    friend struct device;
    friend struct instance;
    friend struct physical_device;
    friend struct queue;

    non_dispatchable_handle(dispatcher_type dispatcher, handle_type handle) noexcept
    : _dispatcher(dispatcher),
      _handle(std::move(handle))
    {
    }

    dispatcher_type _dispatcher;
    handle_type     _handle;
};

using buffer_handle                = mgo::unique_handle<1, VkDevice, VkBuffer, VkAllocationCallbacks const *>;
using buffer_view_handle           = mgo::unique_handle<1, VkDevice, VkBufferView, VkAllocationCallbacks const *>;
using command_buffers_handle       = mgo::unique_handle<3, VkDevice, VkCommandPool, std::uint32_t, VkCommandBuffer const *>;
using command_pool_handle          = mgo::shared_handle<1, VkDevice, VkCommandPool, VkAllocationCallbacks const *>;
using descriptor_pool_handle       = mgo::shared_handle<1, VkDevice, VkDescriptorPool, VkAllocationCallbacks const *>;
using descriptor_sets_handle       = mgo::unique_handle<3, VkDevice, VkDescriptorPool, std::uint32_t, VkDescriptorSet const *>;
using descriptor_set_layout_handle = mgo::unique_handle<1, VkDevice, VkDescriptorSetLayout, VkAllocationCallbacks const *>;
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

using buffer                = non_dispatchable_handle<device_handle, buffer_handle>;
using buffer_view           = non_dispatchable_handle<device_handle, buffer_view_handle>;
using command_pool          = non_dispatchable_handle<device_handle, command_pool_handle>;
using descriptor_pool       = non_dispatchable_handle<device_handle, descriptor_pool_handle>;
using descriptor_set_layout = non_dispatchable_handle<device_handle, descriptor_set_layout_handle>;
using descriptor_sets       = non_dispatchable_handle<descriptor_pool_handle, descriptor_sets_handle>;
using device_memory         = non_dispatchable_handle<device_handle, device_memory_handle>;
using event                 = non_dispatchable_handle<device_handle, event_handle>;
using fence                 = non_dispatchable_handle<device_handle, fence_handle>;
using framebuffer           = non_dispatchable_handle<device_handle, framebuffer_handle>;
using image                 = non_dispatchable_handle<device_handle, image_handle>;
using image_view            = non_dispatchable_handle<device_handle, image_view_handle>;
using pipeline_cache        = non_dispatchable_handle<device_handle, pipeline_cache_handle>;
using pipeline              = non_dispatchable_handle<device_handle, pipeline_handle>;
using pipeline_layout       = non_dispatchable_handle<device_handle, pipeline_layout_handle>;
using query_pool            = non_dispatchable_handle<device_handle, query_pool_handle>;
using render_pass           = non_dispatchable_handle<device_handle, render_pass_handle>;
using sampler               = non_dispatchable_handle<device_handle, sampler_handle>;
using semaphore             = non_dispatchable_handle<device_handle, semaphore_handle>;
using shader_module         = non_dispatchable_handle<device_handle, shader_module_handle>;

namespace ext
{
using debug_report_callback_handle = mgo::unique_handle<1, VkInstance, VkDebugReportCallbackEXT, VkAllocationCallbacks const *>;
using debug_utils_messenger_handle = mgo::unique_handle<1, VkInstance, VkDebugUtilsMessengerEXT, VkAllocationCallbacks const *>;

using debug_report_callback = non_dispatchable_handle<instance_handle, debug_report_callback_handle>;
using debug_utils_messenger = non_dispatchable_handle<instance_handle, debug_utils_messenger_handle>;
}

namespace khr
{
using surface_handle   = mgo::unique_handle<1, VkInstance, VkSurfaceKHR, VkAllocationCallbacks const *>;
using swapchain_handle = mgo::unique_handle<1, VkDevice, VkSwapchainKHR, VkAllocationCallbacks const *>;

using surface   = non_dispatchable_handle<instance_handle, surface_handle>;
using swapchain = non_dispatchable_handle<device_handle, swapchain_handle>;
}
}