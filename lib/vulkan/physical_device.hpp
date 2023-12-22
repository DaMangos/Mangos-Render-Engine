#pragma once

#include "non_dispatchable.hpp"

#include <string>

namespace vulkan
{
struct device;

struct physical_device final
{
    [[nodiscard]]
    VkPhysicalDevice get() const noexcept;

    [[nodiscard]]
    device create_device(VkDeviceCreateInfo const &create_info) const;

    [[nodiscard]]
    bool check_surface_support(VkSurfaceKHR const surface, std::uint32_t const queue_family) const;

    [[nodiscard]]
    VkSurfaceCapabilitiesKHR get_surface_capabilities(VkSurfaceKHR const surface) const;

    [[nodiscard]]
    std::pair<std::vector<VkSurfaceFormatKHR>, VkResult const> get_surface_formats(VkSurfaceKHR const surface) const;

    [[nodiscard]]
    std::pair<std::vector<VkPresentModeKHR>, VkResult const> get_present_modes(VkSurfaceKHR const surface) const;

    [[nodiscard]]
    VkPhysicalDeviceFeatures get_features() const noexcept;

    [[nodiscard]]
    VkPhysicalDeviceProperties get_properties() const noexcept;

    [[nodiscard]]
    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;

    [[nodiscard]]
    std::pair<std::vector<VkExtensionProperties>, VkResult const> get_extension_properties() const;

    [[nodiscard]]
    std::pair<std::vector<VkExtensionProperties>, VkResult const> get_extension_properties(std::string const &layer_name) const;

    bool operator==(physical_device const &other) const noexcept;

    bool operator!=(physical_device const &other) const noexcept;

    physical_device(physical_device &&)                 = default;
    physical_device(physical_device const &)            = delete;
    physical_device &operator=(physical_device &&)      = default;
    physical_device &operator=(physical_device const &) = delete;
    ~physical_device()                                  = default;

  private:
    friend struct instance;

    physical_device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher,
                    VkPhysicalDevice const                                                ptr) noexcept;

    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _dispatcher;
    VkPhysicalDevice                                               _ptr;
};
}

template <>
struct std::hash<vulkan::physical_device>
{
    std::size_t operator()(vulkan::physical_device const &physical_device) const noexcept
    {
      return std::hash<VkPhysicalDevice>()(physical_device.get());
    }
};
