#pragma once

#include "non_dispatchable_handles.hpp"

#include <string>

namespace vulkan
{
instance create_instance(VkInstanceCreateInfo create_info);

struct instance
{
    friend instance create_instance(VkInstanceCreateInfo create_info);

    using pointer       = typename handle_traits<VkInstance>::pointer;
    using const_pointer = typename handle_traits<VkInstance>::const_pointer;
    using element_type  = typename handle_traits<VkInstance>::element_type;
    using deleter_type  = typename handle_traits<VkInstance>::deleter_type;
    using unique_type   = typename handle_traits<VkInstance>::unique_type;
    using shared_type   = typename handle_traits<VkInstance>::shared_type;

    pointer get() const noexcept;

    std::vector<physical_device> enumerate_physical_device() const;

    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    khr::surface create_surface(GLFWwindow *window) const;

  private:
    instance(pointer instance, deleter_type &&deleter);

    unique_type _instance;
};
}