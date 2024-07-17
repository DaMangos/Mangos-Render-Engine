#pragma once

#include <vulkan/vulkan.h>

#include <memory>

namespace vulkan
{
template <class Dispatcher>
struct shared_dispatcher;

template <>
struct shared_dispatcher<VkInstance>
{
    [[nodiscard]]
    VkInstance get() const noexcept
    {
      return shared_instance.get();
    }

    void reset() noexcept
    {
      shared_instance.reset();
    }

    std::shared_ptr<VkInstance_T> shared_instance;
};

template <>
struct shared_dispatcher<VkDevice>
{
    [[nodiscard]]
    VkDevice get() const noexcept
    {
      return shared_device.get();
    }

    void reset() noexcept
    {
      shared_device.reset();
      shared_instance.reset();
    }

    std::shared_ptr<VkDevice_T>   shared_device;
    std::shared_ptr<VkInstance_T> shared_instance;
};
}