#pragma once

#include "../../deleter.hpp"

namespace vulkan
{
mgo::unique_handle<VkInstance> create_instance(VkInstanceCreateInfo create_info);

struct instance
{
    instance(mgo::unique_handle<VkInstance> underling_instance) noexcept;

    VkInstance get() const noexcept;

    mgo::shared_handle<VkInstance> get_handle() const noexcept;

    std::vector<VkPhysicalDevice> enumerate_Physical_device() const;

    mgo::unique_handle<VkDebugUtilsMessengerEXT>
    create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    mgo::unique_handle<VkDebugReportCallbackEXT>
    create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    mgo::unique_handle<VkSurfaceKHR> create_surface(GLFWwindow *window) const;

    template <class function_pointer>
    auto invoke(std::string const &function_name, auto &&...function_args) const
    {
      return vulkan::invoke<function_pointer>(get(), function_name, std::forward<decltype(function_args)>(function_args)...);
    }

  private:
    mgo::shared_handle<VkInstance> _underling_instance;
};
}