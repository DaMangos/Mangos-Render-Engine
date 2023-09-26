#pragma once

#include "device.hpp"
#include "non_dispatchable.hpp"

#include <string>

namespace vulkan
{
struct physical_device final
{
    physical_device(VkPhysicalDevice &&physical_device) noexcept;

    [[nodiscard]]
    VkPhysicalDevice get() const noexcept;

    [[nodiscard]]
    device create_device(VkDeviceCreateInfo create_info) const;

    [[nodiscard]]
    bool check_surface_support(VkSurfaceKHR surface, std::uint32_t queue_family) const;

    [[nodiscard]]
    VkSurfaceCapabilitiesKHR get_surface_capabilities(VkSurfaceKHR surface) const;

    [[nodiscard]]
    std::vector<VkSurfaceFormatKHR> get_surface_formats(VkSurfaceKHR surface) const;

    [[nodiscard]]
    std::vector<VkPresentModeKHR> get_present_modes(VkSurfaceKHR surface) const;

    [[nodiscard]]
    VkPhysicalDeviceFeatures get_features() const noexcept;

    [[nodiscard]]
    VkPhysicalDeviceProperties get_properties() const noexcept;

    [[nodiscard]]
    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;

    [[nodiscard]]
    std::vector<VkExtensionProperties> get_extension_properties() const;

    [[nodiscard]]
    std::vector<VkExtensionProperties> get_extension_properties(std::string const &layer_name) const;

  private:
    VkPhysicalDevice physical_device_;
};
}