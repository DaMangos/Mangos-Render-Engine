#pragma once

#include "non_dispatchable.hpp"

#include <string>

namespace vulkan
{
struct physical_device;

struct instance final
{
    instance(VkInstanceCreateInfo const &create_info);

    [[nodiscard]]
    VkInstance get() const noexcept
    {
      return _handle.get();
    }

    [[nodiscard]]
    std::pair<std::vector<physical_device>, VkResult> enumerate_physical_devices() const;

    [[nodiscard]]
    ext::debug_utils_messenger create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const &create_info) const;

    [[nodiscard]]
    ext::debug_report_callback create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const &create_info) const;

    [[nodiscard]]
    khr::surface create_surface(GLFWwindow *const window_ptr) const;

    template <class function_pointer>
    [[nodiscard]]
    auto get_proc_addr(std::string const &function_name) const
      requires std::is_function_v<std::remove_pointer_t<function_pointer>>
    {
      // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
      if(PFN_vkVoidFunction function = vkGetInstanceProcAddr(get(), function_name.c_str()))
        return reinterpret_cast<function_pointer>(function);
      throw std::runtime_error("failed get protocol address: " + function_name);
      // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
    }

    instance(instance &&)                 = default;
    instance(instance const &)            = delete;
    instance &operator=(instance &&)      = default;
    instance &operator=(instance const &) = delete;
    ~instance()                           = default;

  private:
    std::shared_ptr<std::pointer_traits<VkInstance>::element_type> _handle;
};
}
