#pragma once

#include "physical_device.hpp"

namespace vulkan
{
template <class>
struct dispatchable_handle;

template <>
struct dispatchable_handle<VkInstance> final
{
    using value_type = VkInstance;

    dispatchable_handle(VkInstanceCreateInfo const &info)
    : _smart_ptr(
        [&info]()
        {
          value_type ptr;
          auto const result = vkCreateInstance(&info, nullptr, &ptr);
          return std::to_underlying(result) >= 0 ? ptr : throw bad_result(result);
        }(),
        [](auto &&ptr) { vkDestroyInstance(std::forward<decltype(ptr)>(ptr), nullptr); })
    {
    }

    [[nodiscard]]
    constexpr auto get() const
    {
      return _smart_ptr ? _smart_ptr.get() : throw bad_handle_access();
    }

    [[nodiscard]]
    auto enumerate_physical_devices() const
    {
      if(not _smart_ptr)
        throw bad_handle_access();
      std::uint32_t count  = 0;
      auto const    result = vkEnumeratePhysicalDevices(get(), &count, nullptr);
      if(std::to_underlying(result) < 0)
        throw bad_result(result);
      auto ptrs           = std::vector<VkPhysicalDevice>(count);
      auto return_value   = std::pair<std::vector<physical_device>, VkResult>{};
      return_value.second = vkEnumeratePhysicalDevices(get(), &count, ptrs.data());
      std::ranges::transform(ptrs, std::back_inserter(return_value.first), [this](auto const ptr) { return physical_device(_smart_ptr, ptr); });
      return return_value;
    }

    [[nodiscard]]
    auto create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &info) const
    {
      return _smart_ptr ? ext::debug_utils_messenger(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &info) const
    {
      return _smart_ptr ? ext::debug_report_callback(_smart_ptr, &info) : throw bad_handle_access();
    }

    [[nodiscard]]
    auto create_surface(GLFWwindow *const window) const
    {
      return _smart_ptr ? khr::surface(_smart_ptr, window) : throw bad_handle_access();
    }

    template <class fn>
    [[nodiscard]]
    auto get_proc_addr(std::string const &function_name) const
    {
      if(auto const function = fn(vkGetInstanceProcAddr(get(), function_name.data())))
        return function;
      throw not_found(function_name);
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    auto operator<=>(dispatchable_handle const &) const         = default;
    dispatchable_handle(dispatchable_handle &&)                 = default;
    dispatchable_handle(dispatchable_handle const &)            = delete;
    dispatchable_handle &operator=(dispatchable_handle &&)      = default;
    dispatchable_handle &operator=(dispatchable_handle const &) = delete;
    ~dispatchable_handle()                                      = default;

  private:
    std::shared_ptr<std::pointer_traits<value_type>::element_type> _smart_ptr;
};

using instance = dispatchable_handle<VkInstance>;
}