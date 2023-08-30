#pragma once

#include "non_dispatchable.hpp"
#include "physical_device.hpp"

#include <string>

namespace vulkan
{
struct instance final
{
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

  private:
    instance(VkInstance &&instance) noexcept;

    mgo::apply_in_destructor<[](VkInstance instance) { vkDestroyInstance(instance, nullptr); }, VkInstance> _instance;
};
}