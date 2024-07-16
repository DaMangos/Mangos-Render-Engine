#include <gtest/gtest.h>
#include <vulkan/except/runtime_error.hpp>
#include <vulkan/except/throw_if_error.hpp>

TEST(Vulkan, ThrowIfBadResult)
{
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_OUT_OF_HOST_MEMORY), vulkan::out_of_host_memory);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_OUT_OF_DEVICE_MEMORY), vulkan::out_of_device_memory);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INITIALIZATION_FAILED), vulkan::initialization_failed);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_DEVICE_LOST), vulkan::device_lost);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_MEMORY_MAP_FAILED), vulkan::memory_map_failed);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_LAYER_NOT_PRESENT), vulkan::layer_not_present);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_EXTENSION_NOT_PRESENT), vulkan::extension_not_present);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FEATURE_NOT_PRESENT), vulkan::feature_not_present);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INCOMPATIBLE_DRIVER), vulkan::incompatible_driver);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_TOO_MANY_OBJECTS), vulkan::too_many_objects);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FORMAT_NOT_SUPPORTED), vulkan::format_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FRAGMENTED_POOL), vulkan::fragmented_pool);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_UNKNOWN), vulkan::unknown_error);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_EXTERNAL_HANDLE), vulkan::invalid_external_handle);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FRAGMENTATION), vulkan::fragmentation);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS), vulkan::invalid_opaque_capture_address);
}

TEST(Vulkan, ReturnIfGoodResult)
{
  EXPECT_EQ(vulkan::throw_if_error(VK_EVENT_RESET), VK_EVENT_RESET);
  EXPECT_EQ(vulkan::throw_if_error(VK_EVENT_SET), VK_EVENT_SET);
  EXPECT_EQ(vulkan::throw_if_error(VK_INCOMPLETE), VK_INCOMPLETE);
  EXPECT_EQ(vulkan::throw_if_error(VK_NOT_READY), VK_NOT_READY);
  EXPECT_EQ(vulkan::throw_if_error(VK_PIPELINE_COMPILE_REQUIRED), VK_PIPELINE_COMPILE_REQUIRED);
  EXPECT_EQ(vulkan::throw_if_error(VK_RESULT_MAX_ENUM), VK_RESULT_MAX_ENUM);
  EXPECT_EQ(vulkan::throw_if_error(VK_SUCCESS), VK_SUCCESS);
  EXPECT_EQ(vulkan::throw_if_error(VK_TIMEOUT), VK_TIMEOUT);
}

TEST(VulkanKHR, ThrowIfBadResult)
{
  namespace khr = vulkan::khr;

  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_SURFACE_LOST_KHR), khr::surface_lost);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR), khr::native_window_in_use);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_OUT_OF_DATE_KHR), khr::out_of_date);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR), khr::incompatible_display);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR), khr::image_usage_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR), khr::video_picture_layout_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR), khr::video_profile_operation_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR), khr::video_profile_format_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR), khr::video_profile_codec_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR), khr::video_std_version_not_supported);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_NOT_PERMITTED_KHR), khr::not_permitted);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR), khr::invalid_video_std_parameters);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_OUT_OF_POOL_MEMORY_KHR), khr::out_of_pool_memory);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR), khr::invalid_external_handle);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR), khr::invalid_opaque_capture_address);
}

TEST(VulkanKHR, ReturnIfGoodResult)
{
  EXPECT_EQ(vulkan::throw_if_error(VK_OPERATION_DEFERRED_KHR), VK_OPERATION_DEFERRED_KHR);
  EXPECT_EQ(vulkan::throw_if_error(VK_OPERATION_NOT_DEFERRED_KHR), VK_OPERATION_NOT_DEFERRED_KHR);
  EXPECT_EQ(vulkan::throw_if_error(VK_SUBOPTIMAL_KHR), VK_SUBOPTIMAL_KHR);
  EXPECT_EQ(vulkan::throw_if_error(VK_THREAD_DONE_KHR), VK_THREAD_DONE_KHR);
  EXPECT_EQ(vulkan::throw_if_error(VK_THREAD_IDLE_KHR), VK_THREAD_IDLE_KHR);
}

TEST(VulkanEXT, ThrowIfBadResult)
{
  namespace ext = vulkan::ext;

  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_VALIDATION_FAILED_EXT), ext::validation_failed);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT), ext::invalid_drm_format_modifier_plane_layout);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT), ext::full_screen_exclusive_mode_lost);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_COMPRESSION_EXHAUSTED_EXT), ext::compression_exhausted);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_FRAGMENTATION_EXT), ext::fragmentation);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_NOT_PERMITTED_EXT), ext::not_permitted);
  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_DEVICE_ADDRESS_EXT), ext::invalid_device_address);
}

TEST(VulkanEXT, ReturnIfGoodResult)
{
  EXPECT_EQ(vulkan::throw_if_error(VK_INCOMPATIBLE_SHADER_BINARY_EXT), VK_INCOMPATIBLE_SHADER_BINARY_EXT);
  EXPECT_EQ(vulkan::throw_if_error(VK_PIPELINE_COMPILE_REQUIRED_EXT), VK_PIPELINE_COMPILE_REQUIRED_EXT);
}

TEST(VulkanNV, ThrowIfBadResult)
{
  namespace nv = vulkan::nv;

  EXPECT_THROW(vulkan::throw_if_error(VK_ERROR_INVALID_SHADER_NV), nv::invalid_shader);
}