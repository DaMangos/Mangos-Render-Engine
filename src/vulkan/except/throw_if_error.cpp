#include <vulkan/except/runtime_error.hpp>
#include <vulkan/except/throw_if_error.hpp>

#include <cassert>

VkResult vulkan::throw_if_error_t::operator()(VkResult const result) const
{
  switch(result)
  {
    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw out_of_host_memory();
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw out_of_shared_instance_memory();
    case VK_ERROR_INITIALIZATION_FAILED :
      throw initialization_failed();
    case VK_ERROR_DEVICE_LOST :
      throw device_lost();
    case VK_ERROR_MEMORY_MAP_FAILED :
      throw memory_map_failed();
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw layer_not_present();
    case VK_ERROR_EXTENSION_NOT_PRESENT :
      throw extension_not_present();
    case VK_ERROR_FEATURE_NOT_PRESENT :
      throw feature_not_present();
    case VK_ERROR_INCOMPATIBLE_DRIVER :
      throw incompatible_driver();
    case VK_ERROR_TOO_MANY_OBJECTS :
      throw too_many_objects();
    case VK_ERROR_FORMAT_NOT_SUPPORTED :
      throw format_not_supported();
    case VK_ERROR_FRAGMENTED_POOL :
      throw fragmented_pool();
    case VK_ERROR_UNKNOWN :
      throw unknown_error();
    case VK_ERROR_INVALID_EXTERNAL_HANDLE :
      throw invalid_external_handle();
    case VK_ERROR_FRAGMENTATION :
      throw fragmentation();
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS :
      throw invalid_opaque_capture_address();
    case VK_ERROR_SURFACE_LOST_KHR :
      throw khr::surface_lost();
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
      throw khr::native_window_in_use();
    case VK_ERROR_OUT_OF_DATE_KHR :
      throw khr::out_of_date();
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR :
      throw khr::incompatible_display();
    case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR :
      throw khr::image_usage_not_supported();
    case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR :
      throw khr::video_picture_layout_not_supported();
    case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR :
      throw khr::video_profile_operation_not_supported();
    case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR :
      throw khr::video_profile_format_not_supported();
    case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR :
      throw khr::video_profile_codec_not_supported();
    case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR :
      throw khr::video_std_version_not_supported();
    case VK_ERROR_NOT_PERMITTED_KHR :
      throw khr::not_permitted();
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR :
      throw khr::invalid_video_std_parameters();
    case VK_ERROR_OUT_OF_POOL_MEMORY_KHR :
      throw khr::out_of_pool_memory();
    case VK_ERROR_VALIDATION_FAILED_EXT :
      throw ext::validation_failed();
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT :
      throw ext::invalid_drm_format_modifier_plane_layout();
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT :
      throw ext::full_screen_exclusive_mode_lost();
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT :
      throw ext::compression_exhausted();
    case VK_ERROR_INVALID_SHADER_NV :
      throw nv::invalid_shader();
    default :
    {
      assert(static_cast<int>(result) >= 0);
      return result;
    }
  }
}