#pragma once

#include "device.hpp"
#include "non_dispatchable.hpp"

#include <string>

namespace vulkan
{
struct physical_device final
{
    VkPhysicalDevice get() const noexcept;

    device create_device(VkDeviceCreateInfo create_info) const;

    bool check_surface_support(VkSurfaceKHR surface, std::uint32_t queue_family) const;

    VkSurfaceCapabilitiesKHR get_surface_capabilities(VkSurfaceKHR surface) const;

    std::vector<VkSurfaceFormatKHR> get_surface_formats(VkSurfaceKHR surface) const;

    std::vector<VkPresentModeKHR> get_present_modes(VkSurfaceKHR surface) const;

    VkPhysicalDeviceFeatures get_features() const noexcept;

    VkPhysicalDeviceProperties get_properties() const noexcept;

    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;

    std::vector<VkExtensionProperties> get_extension_properties() const;

    std::vector<VkExtensionProperties> get_extension_properties(std::string const &layer_name) const;

  private:
    friend struct instance;

    physical_device(VkPhysicalDevice &&physical_device) noexcept;

    VkPhysicalDevice _physical_device;
};
}