#pragma once

#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/handles/unique_handle.hpp>

#include <compare>
#include <memory>
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace vulkan
{
class instance;
class physical_device;

[[nodiscard]]
std::pair<instance, VkResult const> create_instance(VkInstanceCreateInfo const & info, VkAllocationCallbacks const & allocator);

[[nodiscard]]
std::pair<instance, VkResult const> create_instance(VkInstanceCreateInfo const & info);

class instance
{
  public:
    [[nodiscard]]
    VkInstance get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    template <class FunctionPointer>
    [[nodiscard]]
    FunctionPointer get_proc_addr(std::string const & name_function);

    template <class FunctionPointer, class... Args>
    std::invoke_result_t<FunctionPointer, Args...> invoke(std::string const & name_function, Args &&... args);

    [[nodiscard]]
    std::pair<ext::debug_report_callback, VkResult const> create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT const & info);

    [[nodiscard]]
    std::pair<ext::debug_utils_messenger, VkResult const> create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT const & info);

    [[nodiscard]]
    std::pair<khr::surface, VkResult const> create_surface(GLFWwindow * const window);

    [[nodiscard]]
    std::pair<std::vector<physical_device>, VkResult const> enumerate_physical_devices();

    void reset() noexcept;

    instance() noexcept = default;

    instance(nullhandle_t) noexcept;

    instance(instance &&) noexcept = default;

    instance(instance const &) noexcept = delete;

    instance & operator=(nullhandle_t) noexcept;

    instance & operator=(instance &&) noexcept = default;

    instance & operator=(instance const &) noexcept = delete;

    ~instance() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(instance const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::shared_ptr<VkInstance_T>                _instance;
    std::shared_ptr<VkAllocationCallbacks const> _allocation_callbacks;

    friend std::pair<instance, VkResult const> create_instance(VkInstanceCreateInfo const & info, VkAllocationCallbacks const & allocator);
    friend std::pair<instance, VkResult const> create_instance(VkInstanceCreateInfo const & info);
};
}

#pragma mark - Implementation

template <class FunctionPointer>
FunctionPointer vulkan::instance::get_proc_addr(std::string const & name_function)
{
  if(auto const function = reinterpret_cast<FunctionPointer>(vkGetInstanceProcAddr(get(), name_function.c_str())))
    return function;
  throw std::invalid_argument(name_function);
}

template <class FunctionPointer, class... Args>
std::invoke_result_t<FunctionPointer, Args...> vulkan::instance::invoke(std::string const & name_function, Args &&... args)
{
  static_assert(std::is_invocable_v<FunctionPointer, Args...>, "FunctionPointer must be invocable with args");
  return get_proc_addr<FunctionPointer>(name_function)(std::forward<Args>(args)...);
}