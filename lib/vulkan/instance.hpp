#pragma once

#include "non_dispatchable.hpp"

#include <cstddef>
#include <optional>
#include <string>

namespace vulkan
{
struct physical_device;

struct instance final
{
    instance(VkInstanceCreateInfo const &create_info);

    [[nodiscard]]
    VkInstance get() const noexcept;

    [[nodiscard]]
    std::pair<std::vector<physical_device>, VkResult const> enumerate_physical_devices() const;

    [[nodiscard]]
    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &create_info) const;

    [[nodiscard]]
    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &create_info) const;

    [[nodiscard]]
    khr::surface create_surface(GLFWwindow *const window_ptr) const;

    template <class function_pointer>
    [[nodiscard]]
    auto get_proc_addr(std::string const &function_name) const
    {
      if(auto function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return function_pointer(function);
      throw std::runtime_error("failed get protocol address: " + function_name);
    }

    bool operator==(instance const &other) const noexcept;

    bool operator!=(instance const &other) const noexcept;

    instance(instance &&)                 = default;
    instance(instance const &)            = delete;
    instance &operator=(instance &&)      = default;
    instance &operator=(instance const &) = delete;
    ~instance()                           = default;

  private:
    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _handle;
};
}

template <>
struct std::hash<vulkan::instance>
{
    std::size_t operator()(vulkan::instance const &instance) const noexcept
    {
      return std::hash<VkInstance>()(instance.get());
    }
};
