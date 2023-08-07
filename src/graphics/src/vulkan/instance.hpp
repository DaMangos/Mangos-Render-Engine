#pragma once
#include "deleter.hpp"
#include "unique_handle.hpp"

namespace graphics::vulkan
{
unique_handle<VkInstance> create_instance(VkInstanceCreateInfo create_info);

struct instance
{
    instance(unique_handle<VkInstance> underling_instance) noexcept;

    VkInstance get() const noexcept;

    std::vector<VkPhysicalDevice> enumerate_Physical_device() const;

    unique_handle<VkDebugUtilsMessengerEXT> create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    unique_handle<VkDebugReportCallbackEXT> create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    unique_handle<VkSurfaceKHR> create_surface(GLFWwindow *window) const;

    template <class function_pointer>
    auto invoke(std::string const &function_name, auto &&...function_args) const
    {
      return graphics::vulkan::invoke<function_pointer>(get(),
                                                        function_name,
                                                        std::forward<decltype(function_args)>(function_args)...);
    }

  private:
    unique_handle<VkInstance> _underling_instance;
};
}