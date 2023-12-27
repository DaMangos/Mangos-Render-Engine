#pragma once

#include "non_dispatchable_handles.hpp"

namespace vulkan
{
struct device;

struct physical_device final
{
    using pointer      = typename std::pointer_traits<VkPhysicalDevice>::pointer;
    using element_type = typename std::pointer_traits<VkPhysicalDevice>::element_type;

    [[nodiscard]]
    device create_device(VkDeviceCreateInfo const &create_info) const;

    [[nodiscard]]
    constexpr bool check_surface_support(VkSurfaceKHR const surface, std::uint32_t const queue_family) const
    {
      VkBool32   supported = VK_FALSE;
      auto const result    = vkGetPhysicalDeviceSurfaceSupportKHR(get(), queue_family, surface, &supported);
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult. (" + std::to_string(result) +
                                 ")");
      return supported == VK_TRUE;
    }

    [[nodiscard]]
    constexpr VkSurfaceCapabilitiesKHR get_surface_capabilities(VkSurfaceKHR const surface) const
    {
      auto       surface_capabilities = VkSurfaceCapabilitiesKHR{};
      auto const result               = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(get(), surface, &surface_capabilities);
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult. (" + std::to_string(result) +
                                 ")");
      return surface_capabilities;
    }

    [[nodiscard]]
    constexpr std::pair<std::vector<VkSurfaceFormatKHR>, VkResult const> get_surface_formats(VkSurfaceKHR const surface) const
    {
      std::uint32_t count = 0;
      vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr);
      auto       surface_formats = std::vector<VkSurfaceFormatKHR>(count);
      auto const result          = vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, surface_formats.data());
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult. (" + std::to_string(result) +
                                 ")");
      return std::make_pair(std::move(surface_formats), result);
    }

    [[nodiscard]]
    constexpr std::pair<std::vector<VkPresentModeKHR>, VkResult const> get_present_modes(VkSurfaceKHR const surface) const
    {
      std::uint32_t count = 0;
      vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr);
      auto       present_modes = std::vector<VkPresentModeKHR>(count);
      auto const result        = vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, present_modes.data());
      return result == VK_SUCCESS or result == VK_INCOMPLETE
               ? std::make_pair(std::move(present_modes), result)
               : throw std::runtime_error("failed to get VkPresentModeKHR: " + std::to_string(result));
    }

    [[nodiscard]]
    constexpr VkPhysicalDeviceFeatures get_features() const noexcept
    {
      auto features = VkPhysicalDeviceFeatures{};
      vkGetPhysicalDeviceFeatures(get(), &features);
      return features;
    }

    [[nodiscard]]
    constexpr VkPhysicalDeviceProperties get_properties() const noexcept
    {
      auto properties = VkPhysicalDeviceProperties{};
      vkGetPhysicalDeviceProperties(get(), &properties);
      return properties;
    }

    [[nodiscard]]
    constexpr std::vector<VkQueueFamilyProperties> get_queue_family_properties() const
    {
      std::uint32_t count = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, nullptr);
      auto properties = std::vector<VkQueueFamilyProperties>(count);
      vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, properties.data());
      return properties;
    }

    [[nodiscard]]
    constexpr std::pair<std::vector<VkExtensionProperties>, VkResult const> get_extension_properties() const
    {
      std::uint32_t count = 0;
      vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr);
      auto       properties = std::vector<VkExtensionProperties>(count);
      auto const result     = vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, properties.data());
      return result == VK_SUCCESS or result == VK_INCOMPLETE
               ? std::make_pair(std::move(properties), result)
               : throw std::runtime_error("failed to enumerate VkExtensionProperties: " + std::to_string(result));
    }

    [[nodiscard]]
    constexpr std::pair<std::vector<VkExtensionProperties>, VkResult const> get_extension_properties(
      std::string const &layer_name) const
    {
      std::uint32_t count = 0;
      vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, nullptr);
      auto       properties = std::vector<VkExtensionProperties>(count);
      auto const result     = vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, properties.data());
      return result == VK_SUCCESS or result == VK_INCOMPLETE
               ? std::make_pair(std::move(properties), result)
               : throw std::runtime_error("failed to enumerate VkExtensionProperties: unknown error");
    }

    [[nodiscard]]
    constexpr VkPhysicalDevice get() const noexcept
    {
      return _ptr;
    }

    constexpr operator bool() const noexcept
    {
      return static_cast<bool>(_ptr);
    }

    constexpr bool operator==(std::nullptr_t null) noexcept
    {
      return _ptr == null;
    }

    constexpr bool operator!=(std::nullptr_t null) noexcept
    {
      return _ptr != null;
    }

    constexpr bool operator==(physical_device const &other) noexcept
    {
      return _ptr == other._ptr;
    }

    constexpr bool operator!=(physical_device const &other) noexcept
    {
      return _ptr != other._ptr;
    }

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
      return std::hash<VkPhysicalDevice>{}(physical_device.get());
    }
};
