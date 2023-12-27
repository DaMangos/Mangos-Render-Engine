#pragma once

#include "non_dispatchable_handles.hpp"

namespace vulkan
{
struct physical_device;

struct instance final
{
    using pointer      = typename std::pointer_traits<VkInstance>::pointer;
    using element_type = typename std::pointer_traits<VkInstance>::element_type;

    instance(VkInstanceCreateInfo const &info);

    [[nodiscard]]
    std::pair<std::vector<physical_device>, VkResult const> enumerate_physical_devices() const;

    [[nodiscard]]
    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &info) const;

    [[nodiscard]]
    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &info) const;

    [[nodiscard]]
    khr::surface create_surface(GLFWwindow *const window_ptr) const;

    template <class fn>
    [[nodiscard]]
    auto get_proc_addr(std::string const &function_name) const
    {
      if(auto const function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return reinterpret_cast<fn>(function);
      throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                               ":\033[1;31m error:\033[0m vulkan failed to find " + function_name);
    }

    [[nodiscard]]
    constexpr VkInstance get() const noexcept
    {
      return _smart_ptr.get();
    }

    constexpr operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    constexpr bool operator==(instance const &other) noexcept
    {
      return _smart_ptr == other._smart_ptr;
    }

    constexpr bool operator!=(instance const &other) noexcept
    {
      return _smart_ptr != other._smart_ptr;
    }

    instance(instance &&)                 = default;
    instance(instance const &)            = delete;
    instance &operator=(instance &&)      = default;
    instance &operator=(instance const &) = delete;
    ~instance()                           = default;

  private:
    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _smart_ptr;
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
