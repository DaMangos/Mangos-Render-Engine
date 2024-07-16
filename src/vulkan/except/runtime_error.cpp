
#include <vulkan/except/runtime_error.hpp>

#include <source_location>
#include <stdexcept>

namespace vulkan
{
template <VkResult Result>
runtime_error<Result>::runtime_error()
: std::runtime_error(std::source_location::current().function_name())
{
}

template <VkResult Result>
runtime_error<Result>::runtime_error(char const * const what_arg)
: std::runtime_error(what_arg)
{
}

template <VkResult Result>
runtime_error<Result>::runtime_error(std::string const & what_arg)
: std::runtime_error(what_arg)
{
}

template <VkResult Result>
char const * runtime_error<Result>::what() const noexcept
{
  return std::runtime_error::what();
}
}

template class vulkan::runtime_error<VK_ERROR_OUT_OF_HOST_MEMORY>;
template class vulkan::runtime_error<VK_ERROR_OUT_OF_DEVICE_MEMORY>;
template class vulkan::runtime_error<VK_ERROR_INITIALIZATION_FAILED>;
template class vulkan::runtime_error<VK_ERROR_DEVICE_LOST>;
template class vulkan::runtime_error<VK_ERROR_MEMORY_MAP_FAILED>;
template class vulkan::runtime_error<VK_ERROR_LAYER_NOT_PRESENT>;
template class vulkan::runtime_error<VK_ERROR_EXTENSION_NOT_PRESENT>;
template class vulkan::runtime_error<VK_ERROR_FEATURE_NOT_PRESENT>;
template class vulkan::runtime_error<VK_ERROR_INCOMPATIBLE_DRIVER>;
template class vulkan::runtime_error<VK_ERROR_TOO_MANY_OBJECTS>;
template class vulkan::runtime_error<VK_ERROR_FORMAT_NOT_SUPPORTED>;
template class vulkan::runtime_error<VK_ERROR_FRAGMENTED_POOL>;
template class vulkan::runtime_error<VK_ERROR_UNKNOWN>;
template class vulkan::runtime_error<VK_ERROR_INVALID_EXTERNAL_HANDLE>;
template class vulkan::runtime_error<VK_ERROR_FRAGMENTATION>;
template class vulkan::runtime_error<VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS>;
template class vulkan::runtime_error<VK_ERROR_SURFACE_LOST_KHR>;
template class vulkan::runtime_error<VK_ERROR_NATIVE_WINDOW_IN_USE_KHR>;
template class vulkan::runtime_error<VK_ERROR_OUT_OF_DATE_KHR>;
template class vulkan::runtime_error<VK_ERROR_INCOMPATIBLE_DISPLAY_KHR>;
template class vulkan::runtime_error<VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_NOT_PERMITTED_KHR>;
template class vulkan::runtime_error<VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR>;
template class vulkan::runtime_error<VK_ERROR_OUT_OF_POOL_MEMORY_KHR>;
template class vulkan::runtime_error<VK_ERROR_VALIDATION_FAILED_EXT>;
template class vulkan::runtime_error<VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT>;
template class vulkan::runtime_error<VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT>;
template class vulkan::runtime_error<VK_ERROR_COMPRESSION_EXHAUSTED_EXT>;
template class vulkan::runtime_error<VK_ERROR_INVALID_SHADER_NV>;
