#include "queue.hpp"

namespace vulkan
{
queue::queue(std::shared_ptr<std::pointer_traits<VkDevice>::element_type> const &dispatcher, VkQueue const ptr) noexcept
: _dispatcher(dispatcher),
  _ptr(ptr)
{
}

VkQueue queue::get() const noexcept
{
  return _ptr;
}

bool queue::operator==(queue const &other) const noexcept
{
  return _ptr == other._ptr;
}

bool queue::operator!=(queue const &other) const noexcept
{
  return _ptr != other._ptr;
}
}
