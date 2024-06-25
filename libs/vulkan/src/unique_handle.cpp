#include "../include/vulkan/unique_handle.hpp"

#include "../include/vulkan/non_loaded_functions.hpp"

template <class Dispatcher, class Handle, auto DeleteHandle>
Handle vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::get() const noexcept
{
  return _handle;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
VkAllocationCallbacks const * vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::get_allocation_callbacks() const noexcept
{
  return _allocation_callbacks.get();
}

template <class Dispatcher, class Handle, auto DeleteHandle>
void vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::reset() noexcept
{
  _dispatcher.reset();
  _handle = VK_NULL_HANDLE;
  _allocation_callbacks.reset();
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::unique_handle(nullhandle_t) noexcept
{
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::unique_handle(unique_handle && other) noexcept
: _dispatcher(std::move(other._dispatcher)),
  _handle(std::exchange(other._handle, VK_NULL_HANDLE)),
  _allocation_callbacks(std::move(other._allocation_callbacks))
{
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle> & vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle> & vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::operator=(
  unique_handle && other) noexcept
{
  _dispatcher           = std::move(other._dispatcher);
  _handle               = std::exchange(other._handle, VK_NULL_HANDLE);
  _allocation_callbacks = std::move(other._allocation_callbacks);
  return *this;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::~unique_handle<Dispatcher, Handle, DeleteHandle>() noexcept
{
  if(_handle != VK_NULL_HANDLE)
    DeleteHandle(_dispatcher.get(), _handle, _allocation_callbacks.get());
}

template <class Dispatcher, class Handle, auto DeleteHandle>
std::strong_ordering vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::operator<=>(nullhandle_t) const noexcept
{
  return _handle <=> static_cast<Handle>(VK_NULL_HANDLE);
}

template <class Dispatcher, class Handle, auto DeleteHandle>
std::strong_ordering vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::operator<=>(unique_handle const & other) const noexcept
{
  return _handle <=> other._handle;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::unique_handle<Dispatcher, Handle, DeleteHandle>::operator bool() const noexcept
{
  return _handle != VK_NULL_HANDLE;
}

template class vulkan::unique_handle<VkDevice, VkBuffer, vkDestroyBuffer>;
template class vulkan::unique_handle<VkDevice, VkBufferView, vkDestroyBufferView>;
template class vulkan::unique_handle<VkDevice, VkDescriptorSetLayout, vkDestroyDescriptorSetLayout>;
template class vulkan::unique_handle<VkDevice, VkDeviceMemory, vkFreeMemory>;
template class vulkan::unique_handle<VkDevice, VkEvent, vkDestroyEvent>;
template class vulkan::unique_handle<VkDevice, VkFence, vkDestroyFence>;
template class vulkan::unique_handle<VkDevice, VkFramebuffer, vkDestroyFramebuffer>;
template class vulkan::unique_handle<VkDevice, VkImage, vkDestroyImage>;
template class vulkan::unique_handle<VkDevice, VkImageView, vkDestroyImageView>;
template class vulkan::unique_handle<VkDevice, VkPipeline, vkDestroyPipeline>;
template class vulkan::unique_handle<VkDevice, VkPipelineCache, vkDestroyPipelineCache>;
template class vulkan::unique_handle<VkDevice, VkPipelineLayout, vkDestroyPipelineLayout>;
template class vulkan::unique_handle<VkDevice, VkQueryPool, vkDestroyQueryPool>;
template class vulkan::unique_handle<VkDevice, VkRenderPass, vkDestroyRenderPass>;
template class vulkan::unique_handle<VkDevice, VkSampler, vkDestroySampler>;
template class vulkan::unique_handle<VkDevice, VkSemaphore, vkDestroySemaphore>;
template class vulkan::unique_handle<VkDevice, VkShaderModule, vkDestroyShaderModule>;
template class vulkan::unique_handle<VkDevice, VkSwapchainKHR, vkDestroySwapchainKHR>;
template class vulkan::unique_handle<VkInstance, VkSurfaceKHR, vkDestroySurfaceKHR>;
template class vulkan::unique_handle<VkInstance, VkDebugReportCallbackEXT, vulkan::ext::destroy_debug_report_callback>;
template class vulkan::unique_handle<VkInstance, VkDebugUtilsMessengerEXT, vulkan::ext::destroy_debug_utils_messenger>;