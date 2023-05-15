#pragma once

#include <glfw/common_handle.hpp>
#include <string_view>
#include <vector>
#include <vk/ext/deleter.hpp>
#include <vk/unique_handle.hpp>

namespace graphics::vk
{
class instance final
{
  public:
    constexpr explicit instance(VkInstanceCreateInfo create_info);

    [[nodiscard]]
    constexpr common_handle<VkInstance> get() const noexcept;

    [[nodiscard]]
    std::vector<common_handle<VkPhysicalDevice>> enumerate_Physical_device() const;

    [[nodiscard]]
    unique_handle<VkDebugUtilsMessengerEXT> create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    [[nodiscard]]
    unique_handle<VkDebugReportCallbackEXT> create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    [[nodiscard]]
    unique_handle<VkSurfaceKHR> create_surface(glfw::common_handle<GLFWwindow> window) const;

    template <class function_pointer>
    auto invoke(std::string const &function_name, auto &&...function_args) const
    {
      return graphics::vk::invoke<function_pointer>(get(), function_name, std::move(function_args)...);
    }

  private:
    unique_handle<VkInstance> _underling_instance;
};
}