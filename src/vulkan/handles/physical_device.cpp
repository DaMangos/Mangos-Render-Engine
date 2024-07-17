#include "vulkan/handles/device.hpp"
#include <vulkan/handles/physical_device.hpp>

VkPhysicalDevice vulkan::physical_device::get() const noexcept
{
  return _physical_device;
}

VkAllocationCallbacks const * vulkan::physical_device::get_allocation_callbacks() const noexcept
{
  return _shared_allocation_callbacks.get();
}

std::pair<vulkan::device, VkResult const> vulkan::physical_device::create_shared_instance(VkDeviceCreateInfo const & info)
{
  VkDevice   handle = VK_NULL_HANDLE;
  auto const result = vkCreateDevice(_physical_device, &info, _shared_allocation_callbacks.get(), &handle);

  if(static_cast<int>(result))
    return {nullhandle, result};

  std::shared_ptr<VkDevice_T> shared_device(handle,
                                            [shared_allocation_callbacks = _shared_allocation_callbacks](auto const handle)
                                            { vkDestroyDevice(handle, shared_allocation_callbacks.get()); });

  device device;
  device._shared_instance             = _shared_instance;
  device._shared_device               = shared_device;
  device._shared_allocation_callbacks = _shared_allocation_callbacks;
  return {std::move(device), result};
}

void vulkan::physical_device::reset() noexcept
{
  _shared_instance.reset();
  _physical_device = VK_NULL_HANDLE;
  _shared_allocation_callbacks.reset();
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
