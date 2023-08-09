#pragma once

#include "dispatchable_handles.hpp"
#include "handle_traits.hpp"

#include <stdexcept>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
template <class managed_type, class dispatcher_type>
struct non_dispatchable_handle
{
    friend dispatcher_type;

    using pointer       = typename handle_traits<managed_type>::pointer;
    using const_pointer = typename handle_traits<managed_type>::const_pointer;
    using element_type  = typename handle_traits<managed_type>::element_type;
    using deleter_type  = typename handle_traits<managed_type>::deleter_type;
    using unique_type   = typename handle_traits<managed_type>::unique_type;
    using shared_type   = typename handle_traits<managed_type>::shared_type;

    pointer get() const noexcept
    {
      return _unique_handle.get();
    }

  private:
    non_dispatchable_handle(pointer ptr, deleter_type &&deleter)
    : _unique_handle(ptr, std::forward<decltype(deleter)>(deleter))
    {
    }

    shared_type _unique_handle;
};

template <>
struct non_dispatchable_handle<VkDescriptorSet[], device>
{
    friend device;

    using size_type              = typename handle_traits<VkDescriptorSet[]>::size_type;
    using value_type             = typename handle_traits<VkDescriptorSet[]>::value_type;
    using difference_type        = typename handle_traits<VkDescriptorSet[]>::difference_type;
    using pointer                = typename handle_traits<VkDescriptorSet[]>::pointer;
    using const_pointer          = typename handle_traits<VkDescriptorSet[]>::const_pointer;
    using reference              = typename handle_traits<VkDescriptorSet[]>::reference;
    using const_reference        = typename handle_traits<VkDescriptorSet[]>::const_reference;
    using iterator               = typename handle_traits<VkDescriptorSet[]>::iterator;
    using const_iterator         = typename handle_traits<VkDescriptorSet[]>::const_iterator;
    using reverse_iterator       = typename handle_traits<VkDescriptorSet[]>::reverse_iterator;
    using const_reverse_iterator = typename handle_traits<VkDescriptorSet[]>::const_reverse_iterator;
    using element_type           = typename handle_traits<VkDescriptorSet[]>::element_type;
    using deleter_type           = typename handle_traits<VkDescriptorSet[]>::deleter_type;
    using unique_type            = typename handle_traits<VkDescriptorSet[]>::unique_type;
    using shared_type            = typename handle_traits<VkDescriptorSet[]>::shared_type;

    size_type size() const noexcept
    {
      return _count;
    }

    pointer get() const noexcept
    {
      return _unique_handle.get();
    }

    pointer data() const noexcept
    {
      return get();
    }

    reference operator[](size_type i) const noexcept
    {
      return data()[i];
    }

    reference at(size_type i) const
    {
      if(i < _count)
        return data()[i];
      throw std::out_of_range("descriptor_sets::at");
    }

    iterator begin() const noexcept
    {
      return data();
    }

    iterator end() const noexcept
    {
      return data() + size();
    }

    iterator cbegin() const noexcept
    {
      return begin();
    }

    iterator cend() const noexcept
    {
      return begin();
    }

    reverse_iterator rbegin() const noexcept
    {
      return reverse_iterator(end());
    }

    reverse_iterator rend() const noexcept
    {
      return reverse_iterator(begin());
    }

    reverse_iterator crbegin() const noexcept
    {
      return rbegin();
    }

    reverse_iterator crend() const noexcept
    {
      return rbegin();
    }

  private:
    non_dispatchable_handle(size_type count, pointer ptr, deleter_type &&deleter)
    : _count(count),
      _unique_handle(ptr, std::forward<decltype(deleter)>(deleter))
    {
    }

    size_type   _count;
    shared_type _unique_handle;
};

using buffer                = non_dispatchable_handle<VkBuffer, device>;
using image                 = non_dispatchable_handle<VkImage, device>;
using semaphore             = non_dispatchable_handle<VkSemaphore, device>;
using fence                 = non_dispatchable_handle<VkFence, device>;
using device_memory         = non_dispatchable_handle<VkDeviceMemory, device>;
using event                 = non_dispatchable_handle<VkEvent, device>;
using query_pool            = non_dispatchable_handle<VkQueryPool, device>;
using buffer_view           = non_dispatchable_handle<VkBufferView, device>;
using image_view            = non_dispatchable_handle<VkImageView, device>;
using shader_module         = non_dispatchable_handle<VkShaderModule, device>;
using pipeline_cache        = non_dispatchable_handle<VkPipelineCache, device>;
using pipeline_layout       = non_dispatchable_handle<VkPipelineLayout, device>;
using pipeline              = non_dispatchable_handle<VkPipeline, device>;
using render_pass           = non_dispatchable_handle<VkRenderPass, device>;
using descriptor_set_layout = non_dispatchable_handle<VkDescriptorSetLayout, device>;
using sampler               = non_dispatchable_handle<VkSampler, device>;
using descriptor_sets       = non_dispatchable_handle<VkDescriptorSet[], device>;
using descriptor_pool       = non_dispatchable_handle<VkDescriptorPool, device>;
using framebuffer           = non_dispatchable_handle<VkFramebuffer, device>;
using command_pool          = non_dispatchable_handle<VkCommandPool, device>;

namespace khr
{
using surface                  = non_dispatchable_handle<VkSurfaceKHR, instance>;
using swapchain                = non_dispatchable_handle<VkSwapchainKHR, device>;
using video_session            = non_dispatchable_handle<VkVideoSessionKHR, device>;
using video_session_parameters = non_dispatchable_handle<VkVideoSessionParametersKHR, device>;
using deferred_operation       = non_dispatchable_handle<VkDeferredOperationKHR, device>;
using acceleration_structure   = non_dispatchable_handle<VkAccelerationStructureKHR, device>;

// using display               = non_dispatchable_handle<VkDisplayKHR, physical_device>;
// using display_mode          = non_dispatchable_handle<VkDisplayModeKHR, physical_device>;
}

namespace ext
{
using debug_report_callback = non_dispatchable_handle<VkDebugReportCallbackEXT, instance>;
using debug_utils_messenger = non_dispatchable_handle<VkDebugUtilsMessengerEXT, instance>;
using validation_cache      = non_dispatchable_handle<VkValidationCacheEXT, device>;
using micromap              = non_dispatchable_handle<VkMicromapEXT, device>;
using shader                = non_dispatchable_handle<VkShaderEXT, device>;
}
}