#pragma once

#include "vulkan/handles/instance.hpp"
#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/handles/unique_handle.hpp>

#include <compare>
#include <memory>

namespace vulkan
{
class device;

class physical_device
{
  public:
    [[nodiscard]]
    VkPhysicalDevice get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    [[nodiscard]]
    std::pair<device, VkResult const> create_device(VkDeviceCreateInfo const & info);

    void reset() noexcept;

    physical_device() noexcept = default;

    physical_device(nullhandle_t) noexcept;

    physical_device(physical_device &&) noexcept = default;

    physical_device(physical_device const &) noexcept = delete;

    physical_device & operator=(nullhandle_t) noexcept;

    physical_device & operator=(physical_device &&) noexcept = default;

    physical_device & operator=(physical_device const &) noexcept = delete;

    ~physical_device() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(physical_device const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::shared_ptr<VkInstance_T>                _instance;
    VkPhysicalDevice                             _physical_device;
    std::shared_ptr<VkAllocationCallbacks const> _allocation_callbacks;

    friend class instance;
};
}