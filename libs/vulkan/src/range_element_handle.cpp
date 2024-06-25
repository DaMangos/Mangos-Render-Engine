#include "../include/vulkan/range_element_handle.hpp"

template <class Handle>
Handle vulkan::range_element_handle<Handle>::get() const noexcept
{
  return _handles[static_cast<std::ptrdiff_t>(_index)];
}

template <class Handle>
std::uint32_t vulkan::range_element_handle<Handle>::index() const noexcept
{
  return _index;
}

template <class Handle>
std::uint32_t vulkan::range_element_handle<Handle>::size() const noexcept
{
  return _size;
}

template <class Handle>
Handle const * vulkan::range_element_handle<Handle>::data() const noexcept
{
  return _handles.get();
}

template <class Handle>
void vulkan::range_element_handle<Handle>::reset() noexcept
{
  _handles.reset();
  _size  = 0;
  _index = 0;
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
  return _handles <=> other._handles;
}

template <class Handle>
std::strong_ordering vulkan::range_element_handle<Handle>::operator<=>(nullhandle_t) const noexcept
{
  return _handles <=> nullptr;
}

template <class Handle>
vulkan::range_element_handle<Handle>::operator bool() const noexcept
{
  return static_cast<bool>(_handles);
}

template class vulkan::range_element_handle<VkCommandBuffer>;
template class vulkan::range_element_handle<VkDescriptorSet>;