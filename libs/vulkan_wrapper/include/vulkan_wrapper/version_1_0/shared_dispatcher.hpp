#pragma once

#include <vulkan/vulkan.h>

#include <memory>

namespace vulkan
{
inline namespace version_1_0
{
template <class Dispatcher>
struct shared_dispatcher;

template <>
struct shared_dispatcher<VkInstance>
{
    [[nodiscard]]
    VkInstance get() const noexcept
    {
      return instance.get();
    }

    void reset() noexcept
    {
      instance.reset();
    }

    std::shared_ptr<VkInstance_T> instance;
};

template <>
struct shared_dispatcher<VkDevice>
{
    [[nodiscard]]
    VkDevice get() const noexcept
    {
      return device.get();
    }

    void reset() noexcept
    {
      device.reset();
      instance.reset();
    }

    std::shared_ptr<VkDevice_T>   device;
    std::shared_ptr<VkInstance_T> instance;
};
}
}