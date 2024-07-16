#pragma once

#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/handles/shared_dispatcher.hpp>
#include <vulkan/non_loaded_functions.hpp>

#include <compare>

namespace vulkan
{
namespace internal
{
struct make_unique_handle_t;
struct create_unique_handle_t;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
class unique_handle
{
  public:
    [[nodiscard]]
    Handle get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    void reset() noexcept;

    unique_handle() noexcept = default;

    unique_handle(nullhandle_t) noexcept;

    unique_handle(unique_handle && other) noexcept;

    unique_handle(unique_handle const &) noexcept = delete;

    unique_handle & operator=(nullhandle_t) noexcept;

    unique_handle & operator=(unique_handle && other) noexcept;

    unique_handle & operator=(unique_handle const &) noexcept = delete;

    ~unique_handle() noexcept;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(unique_handle const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    shared_dispatcher<Dispatcher>                _dispatcher;
    Handle                                       _handle = VK_NULL_HANDLE;
    std::shared_ptr<VkAllocationCallbacks const> _allocation_callbacks;

    friend internal::make_unique_handle_t;
    friend internal::create_unique_handle_t;
};

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
}

namespace vulkan::khr
{
using swapchain = unique_handle<VkDevice, VkSwapchainKHR, vkDestroySwapchainKHR>;
using surface   = unique_handle<VkInstance, VkSurfaceKHR, vkDestroySurfaceKHR>;
}

namespace vulkan::ext
{
using debug_report_callback = unique_handle<VkInstance, VkDebugReportCallbackEXT, ext::destroy_debug_report_callback>;
using debug_utils_messenger = unique_handle<VkInstance, VkDebugUtilsMessengerEXT, ext::destroy_debug_utils_messenger>;
}