#pragma once

#include "functional.hpp"

#include <memory>
#include <mgo/memory.hpp>

template <>
struct mgo::deleter<VkBuffer>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkBuffer buffer) const noexcept
    {
      vkDestroyBuffer(_device.get(), buffer, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkBufferView>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkBufferView buffer_view) const noexcept
    {
      vkDestroyBufferView(_device.get(), buffer_view, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkCommandBuffer[]>
{
    deleter(mgo::shared_handle<VkDevice> device, mgo::shared_handle<VkCommandPool> command_pool, std::uint32_t count) noexcept
    : _device(device),
      _command_pool(command_pool),
      _count(count)
    {
    }

    void operator()(VkCommandBuffer *command_buffers) const noexcept
    {
      vkFreeCommandBuffers(_device.get(), _command_pool.get(), _count, command_buffers);
      delete[] command_buffers;
    }

  private:
    mgo::shared_handle<VkDevice>      _device;
    mgo::shared_handle<VkCommandPool> _command_pool;
    std::uint32_t                     _count;
};

template <>
struct mgo::deleter<VkCommandPool>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkCommandPool command_pool) const noexcept
    {
      vkDestroyCommandPool(_device.get(), command_pool, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkDebugReportCallbackEXT>
{
    deleter(mgo::shared_handle<VkInstance> instance)
    : _instance(instance)
    {
    }

    void operator()(VkDebugReportCallbackEXT debug_report_callback) const noexcept
    {
      vulkan::invoke<PFN_vkDestroyDebugReportCallbackEXT>(_instance.get(),
                                                          "vkDestroyDebugReportCallbackEXT",
                                                          _instance.get(),
                                                          debug_report_callback,
                                                          nullptr);
    }

  private:
    mgo::shared_handle<VkInstance> _instance;
};

template <>
struct mgo::deleter<VkDebugUtilsMessengerEXT>
{
    deleter(mgo::shared_handle<VkInstance> instance)
    : _instance(instance)
    {
    }

    void operator()(VkDebugUtilsMessengerEXT debug_utils_messenger) const noexcept
    {
      vulkan::invoke<PFN_vkDestroyDebugUtilsMessengerEXT>(_instance.get(),
                                                          "vkDestroyDebugUtilsMessengerEXT",
                                                          _instance.get(),
                                                          debug_utils_messenger,
                                                          nullptr);
    }

  private:
    mgo::shared_handle<VkInstance> _instance;
};

template <>
struct mgo::deleter<VkDescriptorPool>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkDescriptorPool descriptor_pool) const noexcept
    {
      vkDestroyDescriptorPool(_device.get(), descriptor_pool, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkDescriptorSetLayout>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkDescriptorSetLayout descriptor_set_layout) const noexcept
    {
      vkDestroyDescriptorSetLayout(_device.get(), descriptor_set_layout, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkDevice>
{
    void operator()(VkDevice device) const noexcept
    {
      vkDestroyDevice(device, nullptr);
    }
};

template <>
struct mgo::deleter<VkFence>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkFence fence) const noexcept
    {
      vkDestroyFence(_device.get(), fence, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkFramebuffer>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkFramebuffer framebuffer) const noexcept
    {
      vkDestroyFramebuffer(_device.get(), framebuffer, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkImage>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkImage image) const noexcept
    {
      vkDestroyImage(_device.get(), image, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkImageView>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkImageView image_view) const noexcept
    {
      vkDestroyImageView(_device.get(), image_view, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkInstance>
{
    void operator()(VkInstance instance) const noexcept
    {
      vkDestroyInstance(instance, nullptr);
    }
};

template <>
struct mgo::deleter<VkSurfaceKHR>
{
    deleter(mgo::shared_handle<VkInstance> instance) noexcept
    : _instance(instance)
    {
    }

    void operator()(VkSurfaceKHR surface) const noexcept
    {
      vkDestroySurfaceKHR(_instance.get(), surface, nullptr);
    }

  private:
    mgo::shared_handle<VkInstance> _instance;
};

template <>
struct mgo::deleter<VkSwapchainKHR>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSwapchainKHR swapchain) const noexcept
    {
      vkDestroySwapchainKHR(_device.get(), swapchain, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkPipeline>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipeline pipeline) const noexcept
    {
      vkDestroyPipeline(_device.get(), pipeline, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkPipelineCache>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipelineCache pipeline_cache) const noexcept
    {
      vkDestroyPipelineCache(_device.get(), pipeline_cache, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkPipelineLayout>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkPipelineLayout pipeline_layout) const noexcept
    {
      vkDestroyPipelineLayout(_device.get(), pipeline_layout, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkRenderPass>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkRenderPass render_pass) const noexcept
    {
      vkDestroyRenderPass(_device.get(), render_pass, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkSampler>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSampler sampler) const noexcept
    {
      vkDestroySampler(_device.get(), sampler, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkSemaphore>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkSemaphore semaphore) const noexcept
    {
      vkDestroySemaphore(_device.get(), semaphore, nullptr);
    }

    mgo::shared_handle<VkDevice> _device;
};

template <>
struct mgo::deleter<VkShaderModule>
{
    deleter(mgo::shared_handle<VkDevice> device) noexcept
    : _device(device)
    {
    }

    void operator()(VkShaderModule shader_module) const noexcept
    {
      vkDestroyShaderModule(_device.get(), shader_module, nullptr);
    }

  private:
    mgo::shared_handle<VkDevice> _device;
};