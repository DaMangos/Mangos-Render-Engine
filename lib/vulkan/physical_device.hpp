#pragma once

#include "device.hpp"

namespace vulkan
{
template <class>
struct dispatchable_handle;

template <>
struct dispatchable_handle<VkPhysicalDevice> final
{
    using value_type = VkPhysicalDevice;

    [[nodiscard]]
    constexpr auto get() const
    {
      return _dispatcher ? _ptr : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_device(VkDeviceCreateInfo const &info) const
    {
      return _dispatcher ? device(_dispatcher, _ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    constexpr bool check_surface_support(VkSurfaceKHR const surface, std::uint32_t const queue_family) const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      VkBool32   supported = VK_FALSE;
      auto const result    = vkGetPhysicalDeviceSurfaceSupportKHR(get(), queue_family, surface, &supported);
      return std::to_underlying(result) >= 0 ? supported == VK_TRUE : throw bad_result(result);
    }

    [[nodiscard]]
    constexpr auto get_surface_capabilities(VkSurfaceKHR const surface) const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      auto       return_value = VkSurfaceCapabilitiesKHR{};
      auto const result       = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(get(), surface, &return_value);
      return std::to_underlying(result) >= 0 ? return_value : throw bad_result(result);
    }

    [[nodiscard]]
    constexpr auto get_surface_formats(VkSurfaceKHR const surface) const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      std::uint32_t count  = 0;
      auto const    result = vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, nullptr);
      if(std::to_underlying(result) < 0)
        throw bad_result(result);
      auto return_value   = std::pair<std::vector<VkSurfaceFormatKHR>, VkResult>(count, VK_SUCCESS);
      return_value.second = vkGetPhysicalDeviceSurfaceFormatsKHR(get(), surface, &count, return_value.first.data());
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_present_modes(VkSurfaceKHR const surface) const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      std::uint32_t count  = 0;
      auto const    result = vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, nullptr);
      if(std::to_underlying(result) < 0)
        throw bad_result(result);
      auto return_value   = std::pair<std::vector<VkPresentModeKHR>, VkResult>(count, VK_SUCCESS);
      return_value.second = vkGetPhysicalDeviceSurfacePresentModesKHR(get(), surface, &count, return_value.first.data());
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_features() const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      auto return_value = VkPhysicalDeviceFeatures{};
      vkGetPhysicalDeviceFeatures(get(), &return_value);
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_properties() const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      auto return_value = VkPhysicalDeviceProperties{};
      vkGetPhysicalDeviceProperties(get(), &return_value);
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_queue_family_properties() const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      std::uint32_t count = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, nullptr);
      auto return_value = std::vector<VkQueueFamilyProperties>(count);
      vkGetPhysicalDeviceQueueFamilyProperties(get(), &count, return_value.data());
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_extension_properties() const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      std::uint32_t count  = 0;
      auto const    result = vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, nullptr);
      if(std::to_underlying(result) < 0)
        throw bad_result(result);
      auto return_value   = std::pair<std::vector<VkExtensionProperties>, VkResult>(count, VK_SUCCESS);
      return_value.second = vkEnumerateDeviceExtensionProperties(get(), nullptr, &count, return_value.first.data());
      return return_value;
    }

    [[nodiscard]]
    constexpr auto get_extension_properties(std::string const &layer_name) const
    {
      if(not _dispatcher)
        throw bad_handle_access();
      std::uint32_t count  = 0;
      auto const    result = vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, nullptr);
      if(std::to_underlying(result) < 0)
        throw bad_result(result);
      auto return_value   = std::pair<std::vector<VkExtensionProperties>, VkResult>(count, VK_SUCCESS);
      return_value.second = vkEnumerateDeviceExtensionProperties(get(), layer_name.c_str(), &count, return_value.first.data());
      return return_value;
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_ptr);
    }

    auto operator<=>(dispatchable_handle const &other) const    = default;
    dispatchable_handle(dispatchable_handle &&)                 = default;
    dispatchable_handle(dispatchable_handle const &)            = delete;
    dispatchable_handle &operator=(dispatchable_handle &&)      = default;
    dispatchable_handle &operator=(dispatchable_handle const &) = delete;
    ~dispatchable_handle()                                      = default;

  private:
    friend dispatchable_handle<VkInstance>;

    dispatchable_handle(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &dispatcher, VkPhysicalDevice const ptr) noexcept
    : _dispatcher(dispatcher),
      _ptr(ptr)
    {
    }

    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _dispatcher;
    value_type                                                     _ptr;
};

using physical_device = dispatchable_handle<VkPhysicalDevice>;
}