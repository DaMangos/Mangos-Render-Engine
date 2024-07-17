#include <vulkan/handles/shared_handle.hpp>
#include <vulkan/handles/unique_handle.hpp>

template <class Dispatcher, class Handle, auto DeleteHandle>
Handle vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::get() const noexcept
{
  return _underlying_handle ? _underlying_handle->get() : VK_NULL_HANDLE;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
VkAllocationCallbacks const * vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::get_allocation_callbacks() const noexcept
{
  return _underlying_handle ? _underlying_handle->get_allocation_callbacks() : nullptr;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
void vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::reset() noexcept
{
  _underlying_handle.reset();
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::shared_handle(nullhandle_t) noexcept
{
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::shared_handle<Dispatcher, Handle, DeleteHandle> & vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
std::strong_ordering vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::operator<=>(nullhandle_t) const noexcept
{
  return _underlying_handle ? *_underlying_handle <=> nullhandle : std::strong_ordering::less;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
std::strong_ordering vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::operator<=>(shared_handle const & other) const noexcept
{
  if(not _underlying_handle)
    return std::strong_ordering::less;

  if(not other._underlying_handle)
    return std::strong_ordering::greater;

  return *_underlying_handle <=> *other._underlying_handle;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
vulkan::shared_handle<Dispatcher, Handle, DeleteHandle>::operator bool() const noexcept
{
  return _underlying_handle and *_underlying_handle;
}

template class vulkan::shared_handle<VkDevice, VkCommandPool, vkDestroyCommandPool>;
template class vulkan::shared_handle<VkDevice, VkDescriptorPool, vkDestroyDescriptorPool>;