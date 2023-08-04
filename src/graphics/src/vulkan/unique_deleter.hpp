#pragma once

#include "funtional.hpp"

#include <cstdint>
#include <vector>

namespace graphics::vulkan
{
template <class managed_type>
struct handle_deleter;

template <>
struct handle_deleter<VkBuffer>

{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkBufferView>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkCommandBuffer[]>
{
    handle_deleter(std::vector<VkCommandBuffer> &command_buffers, VkDevice device, VkCommandPool command_pool) noexcept
    : _device(device),
      _command_pool(command_pool),
      _command_buffers(std::move(command_buffers))
    {
    }

    void operator()(VkCommandBuffer *) noexcept
    {
      vkFreeCommandBuffers(_device, _command_pool, to_count(_command_buffers), _command_buffers.data());
      _command_buffers.clear();
    }

  private:
    VkDevice                     _device;
    VkCommandPool                _command_pool;
    std::vector<VkCommandBuffer> _command_buffers;
};

template <>
struct handle_deleter<VkCommandPool>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkDebugReportCallbackEXT>
{
    handle_deleter(VkInstance instance)
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
struct handle_deleter<VkDebugUtilsMessengerEXT>
{
    handle_deleter(VkInstance instance)
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
struct handle_deleter<VkDescriptorPool>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkDescriptorSetLayout>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkDevice>
{
    void operator()(VkDevice device) const noexcept
    {
      vkDestroyDevice(device, nullptr);
    }
};

template <>
struct handle_deleter<VkFence>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkFramebuffer>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkImage>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkImageView>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkInstance>
{
    void operator()(VkInstance instance) const noexcept
    {
      vkDestroyInstance(instance, nullptr);
    }
};

template <>
struct handle_deleter<VkSurfaceKHR>
{
    handle_deleter(VkInstance instance) noexcept
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
struct handle_deleter<VkSwapchainKHR>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkPipeline>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkPipeline[]>
{
    handle_deleter(VkDevice device) noexcept
    : _device(device)
    {
    }

    void operator()(std::vector<VkPipeline> &pipelines) noexcept
    {
      for(VkPipeline pipeline : pipelines)
        vkDestroyPipeline(_device, pipeline, nullptr);
    }

  private:
    VkDevice _device;
};

template <>
struct handle_deleter<VkPipelineCache>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkPipelineLayout>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkRenderPass>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkSampler>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkSemaphore>
{
    handle_deleter(VkDevice device) noexcept
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
struct handle_deleter<VkShaderModule>
{
    handle_deleter(VkDevice device) noexcept
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