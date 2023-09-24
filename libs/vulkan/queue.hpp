#pragma once

#include "non_dispatchable.hpp"

namespace vulkan
{
struct queue final
{
    [[nodiscard]]
    VkQueue get() const noexcept;

  private:
    friend struct device;

    queue(VkQueue &&queue) noexcept;

    VkQueue _queue;
};
}