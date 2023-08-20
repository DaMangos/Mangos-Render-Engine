#include "queue.hpp"

namespace vulkan
{
queue::queue(VkQueue queue) noexcept
: _queue(queue)
{
}

VkQueue queue::get() const noexcept
{
  return _queue;
}
}