#include "physical_device.hpp"

#include "device.hpp"
#include "instance.hpp"

namespace vulkan
{
device physical_device::create_device(VkDeviceCreateInfo const &info) const
{
  auto       ptr    = VkDevice{};
  auto const result = vkCreateDevice(get(), &info, nullptr, &ptr);
  if(std::to_underlying(result) < 0)
    throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                             ":\033[1;31m error:\033[0m vulkan return a negative VkResult (" + std::to_string(result) + ")");
  return device(_dispatcher, ptr);
}

physical_device::physical_device(std::shared_ptr<std::pointer_traits<VkInstance>::element_type> const &instance,
                                 VkPhysicalDevice const                                                ptr) noexcept
: _dispatcher(instance),
  _ptr(ptr)
{
}
}