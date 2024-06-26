#include "internal.hpp"

#include <vulkan_wrapper/version_1_0/physical_device.hpp>

VkPhysicalDevice vulkan::physical_device::get() const noexcept
{
  return _physical_device;
}

VkAllocationCallbacks const * vulkan::physical_device::get_allocation_callbacks() const noexcept
{
  return _allocation_callbacks.get();
}

std::pair<vulkan::device, VkResult const> vulkan::physical_device::create_device(VkDeviceCreateInfo const & info) noexcept
{
  try
  {
    VkDevice   handle = VK_NULL_HANDLE;
    auto const result = vkCreateDevice(_physical_device, &info, _allocation_callbacks.get(), &handle);

    if(static_cast<int>(result))
      return {nullhandle, result};

    return {internal::make_device(_instance,
                                  std::shared_ptr<VkDevice_T>(handle,
                                                              [shared_allocation_callbacks = _allocation_callbacks](auto const handle)
                                                              { vkDestroyDevice(handle, shared_allocation_callbacks.get()); }),
                                  _allocation_callbacks),
            result};
  }
  catch(std::exception const &)
  {
    return {nullhandle, VK_ERROR_UNKNOWN};
  }
}

void vulkan::physical_device::reset() noexcept
{
  _instance.reset();
  _physical_device = VK_NULL_HANDLE;
  _allocation_callbacks.reset();
}

vulkan::physical_device & vulkan::physical_device::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

std::strong_ordering vulkan::physical_device::operator<=>(physical_device const & other) const noexcept
{
  return _physical_device <=> other._physical_device;
}

std::strong_ordering vulkan::physical_device::operator<=>(nullhandle_t) const noexcept
{
  return _physical_device <=> static_cast<VkPhysicalDevice>(VK_NULL_HANDLE);
}

vulkan::physical_device::operator bool() const noexcept
{
  return _physical_device != VK_NULL_HANDLE;
}
