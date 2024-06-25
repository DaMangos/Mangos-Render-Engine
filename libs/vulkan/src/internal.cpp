#include "internal.hpp"

vulkan::instance vulkan::internal::make_instance(std::shared_ptr<VkInstance_T> const &                instance,
                                                 std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept
{
  ::vulkan::instance result;
  result._instance             = instance;
  result._allocation_callbacks = allocation_callbacks;
  return result;
}

vulkan::physical_device vulkan::internal::make_physical_device(std::shared_ptr<VkInstance_T> const &                instance,
                                                               VkPhysicalDevice const                               physical_device,
                                                               std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept
{
  ::vulkan::physical_device result;
  result._instance             = instance;
  result._physical_device      = physical_device;
  result._allocation_callbacks = allocation_callbacks;
  return result;
}

vulkan::device vulkan::internal::make_device(
  std::shared_ptr<VkInstance_T> const &                instance,
  std::shared_ptr<VkDevice_T> const &                  device,
  std::shared_ptr<VkAllocationCallbacks const> const & allocation_callbacks) noexcept(std::is_nothrow_default_constructible_v<vulkan::device>)
{
  ::vulkan::device result;
  result._instance             = instance;
  result._device               = device;
  result._allocation_callbacks = allocation_callbacks;
  return result;
}
