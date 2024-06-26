#pragma once

#include <vulkan_wrapper/handles/non_dispatchable_handles.hpp>
#include <vulkan_wrapper/handles/nullhandle.hpp>

#include <compare>
#include <memory>

namespace vulkan
{
inline namespace version_1_0
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
    std::pair<device, VkResult const> create_device(VkDeviceCreateInfo const & info) noexcept;

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

    friend struct internal;
};
}
}