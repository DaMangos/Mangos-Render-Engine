#pragma once

#include "non_dispatchable_handle.hpp"

#include <string>

namespace vulkan
{

struct instance
{
    using element_type = typename instance_handle::element_type;
    using pointer      = typename instance_handle::pointer;

    instance(VkInstanceCreateInfo create_info);

    VkInstance get() const noexcept;

    std::vector<physical_device> enumerate_physical_device() const;

    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    khr::surface create_surface(GLFWwindow *window) const;

    template <class function_pointer>
    auto invoke(std::string const &function_name, auto &&...args)
    {
      if(PFN_vkVoidFunction function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return std::invoke(reinterpret_cast<function_pointer>(function), std::forward<decltype(args)>(args)...);
      throw std::runtime_error("failed to find: " + function_name);
    }

  private:
    instance_handle _instance;
};
}