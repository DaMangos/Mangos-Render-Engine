#pragma once

#include <vulkan/except/exception.hpp>
#include <vulkan/vulkan.h>

#include <stdexcept>

namespace vulkan
{
template <VkResult Result>
class runtime_error : public exception, public std::runtime_error
{
    static_assert(static_cast<int>(Result) < 0);

  public:
    runtime_error();

    runtime_error(char const * const what_arg);

    runtime_error(std::string const & what_arg);

    [[nodiscard]]
    char const * what() const noexcept override;
};

using out_of_host_memory             = runtime_error<VK_ERROR_OUT_OF_HOST_MEMORY>;
using out_of_shared_instance_memory  = runtime_error<VK_ERROR_OUT_OF_DEVICE_MEMORY>;
using initialization_failed          = runtime_error<VK_ERROR_INITIALIZATION_FAILED>;
using device_lost                    = runtime_error<VK_ERROR_DEVICE_LOST>;
using memory_map_failed              = runtime_error<VK_ERROR_MEMORY_MAP_FAILED>;
using layer_not_present              = runtime_error<VK_ERROR_LAYER_NOT_PRESENT>;
using extension_not_present          = runtime_error<VK_ERROR_EXTENSION_NOT_PRESENT>;
using feature_not_present            = runtime_error<VK_ERROR_FEATURE_NOT_PRESENT>;
using incompatible_driver            = runtime_error<VK_ERROR_INCOMPATIBLE_DRIVER>;
using too_many_objects               = runtime_error<VK_ERROR_TOO_MANY_OBJECTS>;
using format_not_supported           = runtime_error<VK_ERROR_FORMAT_NOT_SUPPORTED>;
using fragmented_pool                = runtime_error<VK_ERROR_FRAGMENTED_POOL>;
using unknown_error                  = runtime_error<VK_ERROR_UNKNOWN>;
using invalid_external_handle        = runtime_error<VK_ERROR_INVALID_EXTERNAL_HANDLE>;
using fragmentation                  = runtime_error<VK_ERROR_FRAGMENTATION>;
using invalid_opaque_capture_address = runtime_error<VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS>;
}

namespace vulkan::khr
{
using surface_lost                          = runtime_error<VK_ERROR_SURFACE_LOST_KHR>;
using native_window_in_use                  = runtime_error<VK_ERROR_NATIVE_WINDOW_IN_USE_KHR>;
using out_of_date                           = runtime_error<VK_ERROR_OUT_OF_DATE_KHR>;
using incompatible_display                  = runtime_error<VK_ERROR_INCOMPATIBLE_DISPLAY_KHR>;
using image_usage_not_supported             = runtime_error<VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR>;
using video_picture_layout_not_supported    = runtime_error<VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR>;
using video_profile_operation_not_supported = runtime_error<VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR>;
using video_profile_format_not_supported    = runtime_error<VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR>;
using video_profile_codec_not_supported     = runtime_error<VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR>;
using video_std_version_not_supported       = runtime_error<VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR>;
using not_permitted                         = runtime_error<VK_ERROR_NOT_PERMITTED_KHR>;
using invalid_video_std_parameters          = runtime_error<VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR>;
using out_of_pool_memory                    = runtime_error<VK_ERROR_OUT_OF_POOL_MEMORY_KHR>;
using invalid_external_handle               = runtime_error<VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR>;
using invalid_opaque_capture_address        = runtime_error<VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR>;
}

namespace vulkan::ext
{
using validation_failed                        = runtime_error<VK_ERROR_VALIDATION_FAILED_EXT>;
using invalid_drm_format_modifier_plane_layout = runtime_error<VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT>;
using full_screen_exclusive_mode_lost          = runtime_error<VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT>;
using compression_exhausted                    = runtime_error<VK_ERROR_COMPRESSION_EXHAUSTED_EXT>;
using fragmentation                            = runtime_error<VK_ERROR_FRAGMENTATION_EXT>;
using not_permitted                            = runtime_error<VK_ERROR_NOT_PERMITTED_EXT>;
using invalid_shared_instance_address          = runtime_error<VK_ERROR_INVALID_DEVICE_ADDRESS_EXT>;
}

namespace vulkan::nv
{
using invalid_shader = runtime_error<VK_ERROR_INVALID_SHADER_NV>;
}
