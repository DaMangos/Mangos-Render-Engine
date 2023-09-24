#pragma once

#include "non_dispatchable.hpp"
#include "physical_device.hpp"

#include <string>

namespace vulkan
{
struct instance final
{
    instance(VkInstanceCreateInfo create_info);

    [[nodiscard]]
    VkInstance get() const noexcept;

    [[nodiscard]]
    std::vector<physical_device> enumerate_physical_device() const;

    [[nodiscard]]
    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    [[nodiscard]]
    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    [[nodiscard]]
    khr::surface create_surface(GLFWwindow *window) const;

    template <class function_pointer>
    [[nodiscard]]
    function_pointer get_proc_addr(std::string const &function_name) const
    {
      if(PFN_vkVoidFunction function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return reinterpret_cast<function_pointer>(function);
      throw std::runtime_error("failed get protocol address: " + function_name);
    }

  private:
    instance(VkInstance &&instance) noexcept;

    mgo::apply_in_destructor<[](VkInstance instance) { vkDestroyInstance(instance, nullptr); }, VkInstance> instance_;
};
}