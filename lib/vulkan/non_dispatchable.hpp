#pragma once

#include <memory>
#include <type_traits>

#define ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
template <auto func_pointer, class dispatcher_pointer, class pointer>
requires std::invocable<decltype(func_pointer), dispatcher_pointer, pointer, std::nullptr_t> and
         std::is_pointer_v<dispatcher_pointer> and std::is_pointer_v<pointer>
struct non_dispatchable_handle final
{
    [[nodiscard]]
    pointer get() const noexcept
    {
      return _handle.get();
    }

  private:
    friend struct device;
    friend struct instance;

    non_dispatchable_handle(
      std::shared_ptr<typename std::pointer_traits<dispatcher_pointer>::element_type> const &dispatcher_handle,
      pointer                                                                                ptr) noexcept
    : _handle(ptr, deleter{._dispatcher_handle = dispatcher_handle})
    {
    }

    struct deleter final
    {
        void operator()(pointer ptr) const noexcept
        {
          func_pointer(_dispatcher_handle.get(), ptr, nullptr);
        }

        std::shared_ptr<typename std::pointer_traits<dispatcher_pointer>::element_type> _dispatcher_handle;
    };

    std::unique_ptr<typename std::pointer_traits<pointer>::element_type, deleter> _handle;
};

template <>
struct non_dispatchable_handle<vkDestroyCommandPool, VkDevice, VkCommandPool>
{
    [[nodiscard]]
    VkCommandPool get() const noexcept
    {
      return _handle.get();
    }

    non_dispatchable_handle(non_dispatchable_handle &&)                 = default;
    non_dispatchable_handle(non_dispatchable_handle const &)            = delete;
    non_dispatchable_handle &operator=(non_dispatchable_handle &&)      = default;
    non_dispatchable_handle &operator=(non_dispatchable_handle const &) = delete;
    ~non_dispatchable_handle()                                          = default;

  private:
    friend struct device;
    friend struct command_buffers;

    non_dispatchable_handle(std::shared_ptr<typename std::pointer_traits<VkDevice>::element_type> const &dispatcher_handle,
                            VkCommandPool                                                                ptr) noexcept
    : _handle(ptr, deleter{dispatcher_handle})
    {
    }

    struct deleter final
    {
        void operator()(VkCommandPool ptr) const noexcept
        {
          vkDestroyCommandPool(dispatcher_handle.get(), ptr, nullptr);
        }

        std::shared_ptr<typename std::pointer_traits<VkDevice>::element_type> dispatcher_handle;
    };

    std::shared_ptr<typename std::pointer_traits<VkCommandPool>::element_type> _handle;
};

template <>
struct non_dispatchable_handle<vkDestroyDescriptorPool, VkDevice, VkDescriptorPool>
{
    [[nodiscard]]
    constexpr VkDescriptorPool get() const noexcept
    {
      return _handle.get();
    }

    non_dispatchable_handle(non_dispatchable_handle &&)                 = default;
    non_dispatchable_handle(non_dispatchable_handle const &)            = delete;
    non_dispatchable_handle &operator=(non_dispatchable_handle &&)      = default;
    non_dispatchable_handle &operator=(non_dispatchable_handle const &) = delete;
    ~non_dispatchable_handle()                                          = default;

  private:
    friend struct device;
    friend struct descriptor_sets;

    non_dispatchable_handle(std::shared_ptr<typename std::pointer_traits<VkDevice>::element_type> const &dispatcher_handle,
                            VkDescriptorPool                                                             ptr) noexcept
    : _handle(ptr, deleter{dispatcher_handle})
    {
    }

    struct deleter final
    {
        constexpr void operator()(VkDescriptorPool ptr) const noexcept
        {
          vkDestroyDescriptorPool(dispatcher_handle.get(), ptr, nullptr);
        }

        std::shared_ptr<typename std::pointer_traits<VkDevice>::element_type> dispatcher_handle;
    };

    std::shared_ptr<typename std::pointer_traits<VkDescriptorPool>::element_type> _handle;
};

using buffer                = non_dispatchable_handle<vkDestroyBuffer, VkDevice, VkBuffer>;
using buffer_view           = non_dispatchable_handle<vkDestroyBufferView, VkDevice, VkBufferView>;
using command_pool          = non_dispatchable_handle<vkDestroyCommandPool, VkDevice, VkCommandPool>;
using descriptor_pool       = non_dispatchable_handle<vkDestroyDescriptorPool, VkDevice, VkDescriptorPool>;
using descriptor_set_layout = non_dispatchable_handle<vkDestroyDescriptorSetLayout, VkDevice, VkDescriptorSetLayout>;
using device_memory         = non_dispatchable_handle<vkFreeMemory, VkDevice, VkDeviceMemory>;
using event                 = non_dispatchable_handle<vkDestroyEvent, VkDevice, VkEvent>;
using fence                 = non_dispatchable_handle<vkDestroyFence, VkDevice, VkFence>;
using framebuffer           = non_dispatchable_handle<vkDestroyFramebuffer, VkDevice, VkFramebuffer>;
using image                 = non_dispatchable_handle<vkDestroyImage, VkDevice, VkImage>;
using image_view            = non_dispatchable_handle<vkDestroyImageView, VkDevice, VkImageView>;
using pipeline_cache        = non_dispatchable_handle<vkDestroyPipelineCache, VkDevice, VkPipelineCache>;
using pipeline              = non_dispatchable_handle<vkDestroyPipeline, VkDevice, VkPipeline>;
using pipeline_layout       = non_dispatchable_handle<vkDestroyPipelineLayout, VkDevice, VkPipelineLayout>;
using query_pool            = non_dispatchable_handle<vkDestroyQueryPool, VkDevice, VkQueryPool>;
using render_pass           = non_dispatchable_handle<vkDestroyRenderPass, VkDevice, VkRenderPass>;
using sampler               = non_dispatchable_handle<vkDestroySampler, VkDevice, VkSampler>;
using semaphore             = non_dispatchable_handle<vkDestroySemaphore, VkDevice, VkSemaphore>;
using shader_module         = non_dispatchable_handle<vkDestroyShaderModule, VkDevice, VkShaderModule>;

namespace ext
{
using debug_report_callback = non_dispatchable_handle<
  [](VkInstance dispatcher_ptr, VkDebugReportCallbackEXT ptr, std::nullptr_t)
  {
    std::invoke(reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                  vkGetInstanceProcAddr(dispatcher_ptr, "vkDestroyDebugReportCallbackEXT")),
                dispatcher_ptr,
                ptr,
                nullptr);
  },
  VkInstance,
  VkDebugReportCallbackEXT>;

using debug_utils_messenger = non_dispatchable_handle<
  [](VkInstance dispatcher_ptr, VkDebugUtilsMessengerEXT ptr, std::nullptr_t)
  {
    std::invoke(reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                  vkGetInstanceProcAddr(dispatcher_ptr, "vkDestroyDebugUtilsMessengerEXT")),
                dispatcher_ptr,
                ptr,
                nullptr);
  },
  VkInstance,
  VkDebugUtilsMessengerEXT>;
}

namespace khr
{
using surface   = non_dispatchable_handle<vkDestroySurfaceKHR, VkInstance, VkSurfaceKHR>;
using swapchain = non_dispatchable_handle<vkDestroySwapchainKHR, VkDevice, VkSwapchainKHR>;
}
}