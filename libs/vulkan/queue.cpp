#include "queue.hpp"

namespace vulkan
{
queue::queue(std::shared_ptr<std::pointer_traits<VkDevice>::element_type> const &dispatcher, VkQueue ptr) noexcept
: _dispatcher(dispatcher),
  _ptr(ptr)
{
}

VkQueue queue::get() const noexcept
{
  return _ptr;
}
}