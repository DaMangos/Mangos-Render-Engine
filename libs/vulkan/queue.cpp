#include "queue.hpp"

namespace vulkan
{
queue::queue(pointer queue)
: _queue(queue)
{
}

queue::pointer queue::get() const noexcept
{
  return _queue;
}
}