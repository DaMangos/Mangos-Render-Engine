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
    device create_device(VkDeviceCreateInfo create_info) const;

    [[nodiscard]]
    bool check_surface_support(VkSurfaceKHR surface, std::uint32_t queue_family) const;

    [[nodiscard]]
    VkSurfaceCapabilitiesKHR get_surface_capabilities(VkSurfaceKHR surface) const;

    [[nodiscard]]
    std::pair<std::vector<VkSurfaceFormatKHR>, VkResult> get_surface_formats(VkSurfaceKHR surface) const;

    [[nodiscard]]
    std::pair<std::vector<VkPresentModeKHR>, VkResult> get_present_modes(VkSurfaceKHR surface) const;

    [[nodiscard]]
    VkPhysicalDeviceFeatures get_features() const noexcept;

    [[nodiscard]]
    VkPhysicalDeviceProperties get_properties() const noexcept;

    [[nodiscard]]
    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;

    [[nodiscard]]
    std::pair<std::vector<VkExtensionProperties>, VkResult> get_extension_properties() const;

    [[nodiscard]]
    std::pair<std::vector<VkExtensionProperties>, VkResult> get_extension_properties(std::string const &layer_name) const;

    physical_device(physical_device &&)                 = default;
    physical_device(physical_device const &)            = delete;
    physical_device &operator=(physical_device &&)      = default;
    physical_device &operator=(physical_device const &) = delete;
    ~physical_device()                                  = default;

  private:
    friend struct instance;

    physical_device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher,
                    VkPhysicalDevice                                                      ptr) noexcept;

    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _dispatcher;
    VkPhysicalDevice                                               _ptr;
};
}