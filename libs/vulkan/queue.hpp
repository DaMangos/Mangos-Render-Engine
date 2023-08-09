#pragma once

#include "non_dispatchable_handles.hpp"

namespace vulkan
{
struct queue
{
    friend device;

    using pointer       = typename handle_traits<VkQueue>::pointer;
    using const_pointer = typename handle_traits<VkQueue>::const_pointer;
    using element_type  = typename handle_traits<VkQueue>::element_type;
    using deleter_type  = typename handle_traits<VkQueue>::deleter_type;
    using unique_type   = typename handle_traits<VkQueue>::unique_type;
    using shared_type   = typename handle_traits<VkQueue>::shared_type;

    pointer get() const noexcept;

  private:
    queue(pointer queue);

    pointer _queue;
};
}