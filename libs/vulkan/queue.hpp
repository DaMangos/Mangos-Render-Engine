#pragma once

#include "non_dispatchable.hpp"

namespace vulkan
{
struct queue final
{
    queue(VkQueue &&queue) noexcept;

    [[nodiscard]]
    VkQueue get() const noexcept;

  private:
    VkQueue _queue;
};
}