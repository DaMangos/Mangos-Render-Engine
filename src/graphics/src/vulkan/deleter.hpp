#pragma once

#include "funtional.hpp"

namespace graphics::vulkan
{
template <class value_type>
struct deleter;

template <>
struct deleter<VkBuffer>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkBuffer buffer) const noexcept
    {
      vkDestroyBuffer(_device, buffer, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkBufferView>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkBufferView buffer_view) const noexcept
    {
      vkDestroyBufferView(_device, buffer_view, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkCommandBuffer>
{
    deleter(VkDevice device, VkCommandPool command_pool) noexcept
    : _device(device),
      _command_pool(command_pool)
    {
    }

    void operator()(VkCommandBuffer *command_buffers, std::size_t count) noexcept
    {
      vkFreeCommandBuffers(_device, _command_pool, to_count(count), command_buffers);
    }

  private:
    VkDevice      _device;
    VkCommandPool _command_pool;
};

template <>
struct deleter<VkCommandPool>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkCommandPool command_pool) const noexcept
    {
      vkDestroyCommandPool(_device, command_pool, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkDebugReportCallbackEXT>
{
    deleter(VkInstance instance)
    : _instance(instance)
    {
    }

    void operator()(VkDebugReportCallbackEXT debug_report_callback) const noexcept
    {
      invoke<PFN_vkDestroyDebugReportCallbackEXT>(_instance,
                                                  "vkDestroyDebugReportCallbackEXT",
                                                  _instance,
                                                  debug_report_callback,
                                                  nullptr);
    }

  private:
    VkInstance _instance;
};

template <>
struct deleter<VkDebugUtilsMessengerEXT>
{
    deleter(VkInstance instance)
    : _instance(instance)
    {
    }

    void operator()(VkDebugUtilsMessengerEXT debug_utils_messenger) const noexcept
    {
      invoke<PFN_vkDestroyDebugUtilsMessengerEXT>(_instance,
                                                  "vkDestroyDebugUtilsMessengerEXT",
                                                  _instance,
                                                  debug_utils_messenger,
                                                  nullptr);
    }

  private:
    VkInstance _instance;
};

template <>
struct deleter<VkDescriptorPool>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkDescriptorPool descriptor_pool) const noexcept
    {
      vkDestroyDescriptorPool(_device, descriptor_pool, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkDescriptorSetLayout>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkDescriptorSetLayout descriptor_set_layout) const noexcept
    {
      vkDestroyDescriptorSetLayout(_device, descriptor_set_layout, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkDevice>
{
    void operator()(VkDevice device) const noexcept
    {
      vkDestroyDevice(device, nullptr);
    }
};

template <>
struct deleter<VkFence>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkFence fence) const noexcept
    {
      vkDestroyFence(_device, fence, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkFramebuffer>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkFramebuffer framebuffer) const noexcept
    {
      vkDestroyFramebuffer(_device, framebuffer, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkImage>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkImage image) const noexcept
    {
      vkDestroyImage(_device, image, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkImageView>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkImageView image_view) const noexcept
    {
      vkDestroyImageView(_device, image_view, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkInstance>
{
    void operator()(VkInstance instance) const noexcept
    {
      vkDestroyInstance(instance, nullptr);
    }
};

template <>
struct deleter<VkSurfaceKHR>
{
    deleter(VkInstance instance) noexcept
    : _instance(instance)
    {
    }

    void operator()(VkSurfaceKHR surface) const noexcept
    {
      vkDestroySurfaceKHR(_instance, surface, nullptr);
    }

  private:
    VkInstance _instance;
};

template <>
struct deleter<VkSwapchainKHR>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSwapchainKHR swapchain) const noexcept
    {
      vkDestroySwapchainKHR(_device, swapchain, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkPipeline>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipeline pipeline) const noexcept
    {
      vkDestroyPipeline(_device, pipeline, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkPipelineCache>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipelineCache pipeline_cache) const noexcept
    {
      vkDestroyPipelineCache(_device, pipeline_cache, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkPipelineLayout>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipelineLayout pipeline_layout) const noexcept
    {
      vkDestroyPipelineLayout(_device, pipeline_layout, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkRenderPass>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkRenderPass render_pass) const noexcept
    {
      vkDestroyRenderPass(_device, render_pass, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkSampler>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSampler sampler) const noexcept
    {
      vkDestroySampler(_device, sampler, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct deleter<VkSemaphore>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSemaphore semaphore) const noexcept
    {
      vkDestroySemaphore(_device, semaphore, nullptr);
    }

    VkDevice _device;
};

template <>
struct deleter<VkShaderModule>
{
    deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(VkShaderModule shader_module) const noexcept
    {
      vkDestroyShaderModule(_device, shader_module, nullptr);
    }

  private:
    VkDevice _device;
};
}