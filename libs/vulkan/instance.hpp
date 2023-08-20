#pragma once

#include "fwd.hpp"

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
    function_pointer get_proc_addr(std::string const &function_name) const
    {
      if(PFN_vkVoidFunction function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return reinterpret_cast<function_pointer>(function);
      throw std::runtime_error("failed get protocol address: " + function_name);
    }

    instance &operator=(instance const &) = delete;
    instance &operator=(instance &&)      = default;
    instance(instance const &)            = delete;
    instance(instance &&)                 = default;
    ~instance()                           = default;

  private:
    instance_handle _instance;
};
}