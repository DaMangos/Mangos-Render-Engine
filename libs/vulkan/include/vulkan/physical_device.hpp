#pragma once

#include "../../deleter.hpp"

namespace vulkan
{
struct physical_device
{
    physical_device(VkPhysicalDevice physical_device) noexcept;

    VkPhysicalDevice get() const noexcept;

    mgo::unique_handle<VkDevice> create_device(VkDeviceCreateInfo create_info) const;

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
    VkPhysicalDevice _underling_physical_device;
};
}