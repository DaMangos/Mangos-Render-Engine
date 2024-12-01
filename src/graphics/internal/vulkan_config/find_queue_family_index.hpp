#include <vulkan/vulkan.hpp>

#include <optional>

namespace graphics::internal::vulkan_config
{
std::optional<std::uint32_t> find_queue_family_index(std::vector<vk::QueueFamilyProperties> const & queue_properties,
                                                     vk::QueueFlagBits const                        flags_bit);

std::optional<std::uint32_t> find_surface_support_queue_family_index(vk::PhysicalDevice const physical_device, vk::SurfaceKHR const surface);
}