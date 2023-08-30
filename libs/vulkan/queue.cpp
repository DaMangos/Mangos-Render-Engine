#include "queue.hpp"

namespace vulkan
{
queue::queue(VkQueue &&queue) noexcept
: _queue(std::move(queue))
{
}

VkQueue queue::get() const noexcept
{
  return _queue;
}
}