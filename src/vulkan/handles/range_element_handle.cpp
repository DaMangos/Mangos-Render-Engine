#include <vulkan/handles/range_element_handle.hpp>
#include <vulkan/vulkan.h>

template <class Handle>
Handle vulkan::range_element_handle<Handle>::get() const noexcept
{
  return _shared_handles[static_cast<std::ptrdiff_t>(_array_index)];
}

template <class Handle>
std::uint32_t vulkan::range_element_handle<Handle>::array_index() const noexcept
{
  return _array_index;
}

template <class Handle>
std::uint32_t vulkan::range_element_handle<Handle>::array_size() const noexcept
{
  return _array_size;
}

template <class Handle>
Handle const * vulkan::range_element_handle<Handle>::array_data() const noexcept
{
  return _shared_handles.get();
}

template <class Handle>
void vulkan::range_element_handle<Handle>::reset() noexcept
{
  _shared_handles.reset();
  _array_size  = 0;
  _array_index = 0;
}

template <class Handle>
vulkan::range_element_handle<Handle>::range_element_handle(nullhandle_t) noexcept
{
}

template <class Handle>
vulkan::range_element_handle<Handle> & vulkan::range_element_handle<Handle>::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

template <class Handle>
std::strong_ordering vulkan::range_element_handle<Handle>::operator<=>(range_element_handle const & other) const noexcept
{
  return _shared_handles <=> other._shared_handles;
}

template <class Handle>
std::strong_ordering vulkan::range_element_handle<Handle>::operator<=>(nullhandle_t) const noexcept
{
  return _shared_handles <=> nullptr;
}

template <class Handle>
vulkan::range_element_handle<Handle>::operator bool() const noexcept
{
  return static_cast<bool>(_shared_handles);
}

template class vulkan::range_element_handle<VkDescriptorSet>;