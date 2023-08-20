#pragma once

#include "non_dispatchable_handle.hpp"

namespace vulkan
{
struct queue
{
    using element_type = typename std::pointer_traits<VkQueue>::element_type;
    using pointer      = typename std::pointer_traits<VkQueue>::pointer;

    queue(VkQueue queue) noexcept;

    VkQueue get() const noexcept;

  private:
    VkQueue _queue;
};
}