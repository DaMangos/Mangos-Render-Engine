#pragma once

#include "non_dispatchable_handles.hpp"

namespace vulkan
{
struct physical_device
{
    friend instance;

    using pointer       = typename handle_traits<VkPhysicalDevice>::pointer;
    using const_pointer = typename handle_traits<VkPhysicalDevice>::const_pointer;
    using element_type  = typename handle_traits<VkPhysicalDevice>::element_type;
    using deleter_type  = typename handle_traits<VkPhysicalDevice>::deleter_type;
    using unique_type   = typename handle_traits<VkPhysicalDevice>::unique_type;
    using shared_type   = typename handle_traits<VkPhysicalDevice>::shared_type;

    pointer get() const noexcept;

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
    physical_device(pointer physical_device);

    pointer _physical_device;
};
}