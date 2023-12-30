#pragma once

#include "exception.hpp"
#include "ranges.hpp"

#include <memory>

namespace vulkan
{
template <class>
struct dispatchable_handle;

auto null_create_fn(auto &&...);

template <auto create_fn, auto destroy_fn, class T, class D, bool is_shared = false>
struct non_dispatchable_handle final
{
    using value_type      = T;
    using dispatcher_type = D;

    [[nodiscard]]
    constexpr auto get() const
    {
      return _smart_ptr ? _smart_ptr.get() : throw bad_handle_access();
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    auto operator<=>(non_dispatchable_handle const &) const             = default;
    non_dispatchable_handle(non_dispatchable_handle &&)                 = default;
    non_dispatchable_handle(non_dispatchable_handle const &)            = delete;
    non_dispatchable_handle &operator=(non_dispatchable_handle &&)      = default;
    non_dispatchable_handle &operator=(non_dispatchable_handle const &) = delete;
    ~non_dispatchable_handle()                                          = default;

  private:
    friend struct dispatchable_handle<dispatcher_type>;

    struct deleter_type final
    {
        constexpr void operator()(value_type const ptr) const noexcept
        {
          destroy_fn(dispatcher.get(), ptr, nullptr);
        }

        std::shared_ptr<typename std::pointer_traits<dispatcher_type>::element_type> dispatcher;
    };

    constexpr non_dispatchable_handle(std::shared_ptr<typename std::pointer_traits<dispatcher_type>::element_type> const &dispatcher, auto &&info)
    requires(not std::same_as<decltype(create_fn), std::nullptr_t>)
    : _smart_ptr(
        [&dispatcher, &info]()
        {
          value_type ptr    = nullptr;
          auto const result = create_fn(dispatcher.get(), std::forward<decltype(info)>(info), nullptr, &ptr);
          if(std::to_underlying(result) < 0)
            throw bad_result(result);
          return ptr;
        }(),
        deleter_type{dispatcher})
    {
    }

    constexpr non_dispatchable_handle(value_type ptr, std::shared_ptr<typename std::pointer_traits<dispatcher_type>::element_type> const &dispatcher)
    : _smart_ptr(ptr, deleter_type{dispatcher})
    {
    }

    std::conditional_t<is_shared,
                       std::shared_ptr<typename std::pointer_traits<value_type>::element_type>,
                       std::unique_ptr<typename std::pointer_traits<value_type>::element_type, deleter_type>>
      _smart_ptr;
};

template <auto create_fn, auto destroy_fn, class T, class P, class D>
struct non_dispatchable_handles final
{
    using size_type       = std::uint32_t;
    using value_type      = T;
    using pool_type       = P;
    using dispatcher_type = D;
    using reference       = T const &;
    using const_reference = T const &;
    using iterator        = T const *;
    using const_iterator  = T const *;

    [[nodiscard]]
    constexpr auto get() const
    {
      return not _smart_ptr ? _smart_ptr.get() : throw bad_handle_access();
    }

    [[nodiscard]]
    constexpr auto size() const noexcept
    {
      return _smart_ptr ? _count : 0;
    }

    [[nodiscard]]
    constexpr auto begin() const noexcept
    {
      return _smart_ptr.get();
    }

    [[nodiscard]]
    constexpr auto end() const noexcept
    {
      return _smart_ptr.get() + size();
    }

    constexpr auto operator[](size_type const i) const noexcept
    {
      return _smart_ptr[static_cast<std::size_t>(i)];
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    ~non_dispatchable_handles()
    {
      if(_smart_ptr)
        destroy_fn(_dispatcher.get(), _pool.get(), _count, _smart_ptr.get());
    }

    auto operator<=>(non_dispatchable_handles const &) const              = default;
    non_dispatchable_handles(non_dispatchable_handles &&)                 = default;
    non_dispatchable_handles(non_dispatchable_handles const &)            = delete;
    non_dispatchable_handles &operator=(non_dispatchable_handles &&)      = default;
    non_dispatchable_handles &operator=(non_dispatchable_handles const &) = delete;

  private:
    friend struct dispatchable_handle<D>;

    constexpr non_dispatchable_handles(std::shared_ptr<typename std::pointer_traits<dispatcher_type>::element_type> const &dispatcher,
                                       std::shared_ptr<typename std::pointer_traits<pool_type>::element_type> const       &pool,
                                       size_type const                                                                     count,
                                       auto                                                                              &&info)
    : _dispatcher(dispatcher),
      _pool(pool),
      _count(count),
      _smart_ptr(
        [&info, this]()
        {
          auto       smart_ptr = std::make_unique_for_overwrite<value_type[]>(static_cast<std::size_t>(_count));
          auto const result    = create_fn(_dispatcher.get(), std::forward<decltype(info)>(info), smart_ptr.get());
          if(std::to_underlying(result) < 0)
            throw bad_result(result);
          return smart_ptr;
        }())
    {
    }

    std::shared_ptr<typename std::pointer_traits<dispatcher_type>::element_type> _dispatcher;
    std::shared_ptr<typename std::pointer_traits<pool_type>::element_type>       _pool;
    size_type                                                                    _count;
    std::unique_ptr<value_type[]>                                                _smart_ptr;
};

using buffer                = non_dispatchable_handle<vkCreateBuffer, vkDestroyBuffer, VkBuffer, VkDevice>;
using buffer_view           = non_dispatchable_handle<vkCreateBufferView, vkDestroyBufferView, VkBufferView, VkDevice>;
using command_buffers       = non_dispatchable_handles<vkAllocateCommandBuffers, vkFreeCommandBuffers, VkCommandBuffer, VkCommandPool, VkDevice>;
using command_pool          = non_dispatchable_handle<vkCreateCommandPool, vkDestroyCommandPool, VkCommandPool, VkDevice, true>;
using descriptor_pool       = non_dispatchable_handle<vkCreateDescriptorPool, vkDestroyDescriptorPool, VkDescriptorPool, VkDevice, true>;
using descriptor_set_layout = non_dispatchable_handle<vkCreateDescriptorSetLayout, vkDestroyDescriptorSetLayout, VkDescriptorSetLayout, VkDevice>;
using descriptor_sets       = non_dispatchable_handles<vkAllocateDescriptorSets, vkFreeDescriptorSets, VkDescriptorSet, VkDescriptorPool, VkDevice>;
using device_memory         = non_dispatchable_handle<vkAllocateMemory, vkFreeMemory, VkDeviceMemory, VkDevice>;
using event                 = non_dispatchable_handle<vkCreateEvent, vkDestroyEvent, VkEvent, VkDevice>;
using fence                 = non_dispatchable_handle<vkCreateFence, vkDestroyFence, VkFence, VkDevice>;
using framebuffer           = non_dispatchable_handle<vkCreateFramebuffer, vkDestroyFramebuffer, VkFramebuffer, VkDevice>;
using image                 = non_dispatchable_handle<vkCreateImage, vkDestroyImage, VkImage, VkDevice>;
using image_view            = non_dispatchable_handle<vkCreateImageView, vkDestroyImageView, VkImageView, VkDevice>;
using pipeline              = non_dispatchable_handle<nullptr, vkDestroyPipeline, VkPipeline, VkDevice>;
using pipeline_cache        = non_dispatchable_handle<vkCreatePipelineCache, vkDestroyPipelineCache, VkPipelineCache, VkDevice>;
using pipeline_layout       = non_dispatchable_handle<vkCreatePipelineLayout, vkDestroyPipelineLayout, VkPipelineLayout, VkDevice>;
using query_pool            = non_dispatchable_handle<vkCreateQueryPool, vkDestroyQueryPool, VkQueryPool, VkDevice>;
using render_pass           = non_dispatchable_handle<vkCreateRenderPass2, vkDestroyRenderPass, VkRenderPass, VkDevice>;
using sampler               = non_dispatchable_handle<vkCreateSampler, vkDestroySampler, VkSampler, VkDevice>;
using semaphore             = non_dispatchable_handle<vkCreateSemaphore, vkDestroySemaphore, VkSemaphore, VkDevice>;
using shader_module         = non_dispatchable_handle<vkCreateShaderModule, vkDestroyShaderModule, VkShaderModule, VkDevice>;

namespace ext
{
using debug_report_callback =
  non_dispatchable_handle<[](auto &&dispatcher, auto &&...args)
                          {
                            return std::invoke(
                              PFN_vkCreateDebugReportCallbackEXT(vkGetInstanceProcAddr(dispatcher, "vkCreateDebugReportCallbackEXT")),
                              std::forward<decltype(dispatcher)>(dispatcher),
                              std::forward<decltype(args)>(args)...);
                          },
                          [](auto &&dispatcher, auto &&...args)
                          {
                            std::invoke(PFN_vkDestroyDebugReportCallbackEXT(vkGetInstanceProcAddr(dispatcher, "vkDestroyDebugReportCallbackEXT")),
                                        std::forward<decltype(dispatcher)>(dispatcher),
                                        std::forward<decltype(args)>(args)...);
                          },

                          VkDebugReportCallbackEXT,
                          VkInstance>;

using debug_utils_messenger =
  non_dispatchable_handle<[](auto &&dispatcher, auto &&...args)
                          {
                            return std::invoke(
                              PFN_vkCreateDebugUtilsMessengerEXT(vkGetInstanceProcAddr(dispatcher, "vkCreateDebugUtilsMessengerEXT")),
                              std::forward<decltype(dispatcher)>(dispatcher),
                              std::forward<decltype(args)>(args)...);
                          },
                          [](auto &&dispatcher, auto &&...args)
                          {
                            std::invoke(PFN_vkDestroyDebugUtilsMessengerEXT(vkGetInstanceProcAddr(dispatcher, "vkDestroyDebugUtilsMessengerEXT")),
                                        std::forward<decltype(dispatcher)>(dispatcher),
                                        std::forward<decltype(args)>(args)...);
                          },
                          VkDebugUtilsMessengerEXT,
                          VkInstance>;
}

namespace khr
{
using surface   = non_dispatchable_handle<glfwCreateWindowSurface, vkDestroySurfaceKHR, VkSurfaceKHR, VkInstance>;
using swapchain = non_dispatchable_handle<vkCreateSwapchainKHR, vkDestroySwapchainKHR, VkSwapchainKHR, VkDevice>;
}
}