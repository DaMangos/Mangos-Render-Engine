#pragma once

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN

#include <functional>
#include <GLFW/glfw3.h>
#include <logging.hpp>
#include <ranges>
#include <stdexcept>
#include <string>

namespace graphics::vulkan
{
template <class function_pointer>
auto invoke(VkInstance instance, std::string const &function_name, auto &&...function_args)
{
  if(PFN_vkVoidFunction function = vkGetInstanceProcAddr(instance, function_name.c_str()))
    return std::invoke(reinterpret_cast<function_pointer>(function), std::forward<decltype(function_args)>(function_args)...);
  throw std::runtime_error("failed to find protocol address for " + function_name);
}

constexpr std::uint32_t to_count(std::ranges::contiguous_range auto &container)
{
  if(container.size() < std::numeric_limits<std::uint32_t>::max())
    return static_cast<std::uint32_t>(container.size());
  throw std::out_of_range("container size is too large");
}

auto return_or_throw(VkResult result, std::string const &function_name, auto &&return_value)
{
  switch(result)
  {
    case VK_SUCCESS :
      return std::forward<decltype(return_value)>(return_value);
    case VK_NOT_READY :
      logging::debug_warning << function_name + " returned: VK_NOT_READY";
      return std::forward<decltype(return_value)>(return_value);
    case VK_TIMEOUT :
      logging::debug_warning << function_name + " returned: VK_TIMEOUT";
      return std::forward<decltype(return_value)>(return_value);
    case VK_EVENT_SET :
      logging::debug_warning << function_name + " returned: VK_EVENT_SET";
      return std::forward<decltype(return_value)>(return_value);
    case VK_EVENT_RESET :
      logging::debug_warning << function_name + " returned: VK_EVENT_RESET";
      return std::forward<decltype(return_value)>(return_value);
    case VK_INCOMPLETE :
      logging::debug_warning << function_name + " returned: VK_INCOMPLETE";
      return std::forward<decltype(return_value)>(return_value);
    case VK_PIPELINE_COMPILE_REQUIRED :
      logging::debug_warning << function_name + " returned: VK_PIPELINE_COMPILE_REQUIRED";
      return std::forward<decltype(return_value)>(return_value);
    case VK_SUBOPTIMAL_KHR :
      logging::debug_warning << function_name + " returned: VK_SUBOPTIMAL_KHR";
      return std::forward<decltype(return_value)>(return_value);
    case VK_THREAD_IDLE_KHR :
      logging::debug_warning << function_name + " returned: VK_THREAD_IDLE_KHR";
      return std::forward<decltype(return_value)>(return_value);
    case VK_THREAD_DONE_KHR :
      logging::debug_warning << function_name + " returned: VK_THREAD_DONE_KHR";
      return std::forward<decltype(return_value)>(return_value);
    case VK_OPERATION_DEFERRED_KHR :
      logging::debug_warning << function_name + " returned: VK_OPERATION_DEFERRED_KHR";
      return std::forward<decltype(return_value)>(return_value);
    case VK_OPERATION_NOT_DEFERRED_KHR :
      logging::debug_warning << function_name + " returned: VK_OPERATION_NOT_DEFERRED_KHR";
      return std::forward<decltype(return_value)>(return_value);
    case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT :
      logging::debug_warning << function_name + " returned: VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT";
      return std::forward<decltype(return_value)>(return_value);

    case VK_ERROR_OUT_OF_HOST_MEMORY :
      throw std::runtime_error(function_name + " returned: VK_ERROR_OUT_OF_HOST_MEMORY");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY :
      throw std::runtime_error(function_name + " returned: VK_ERROR_OUT_OF_DEVICE_MEMORY");
    case VK_ERROR_INITIALIZATION_FAILED :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INITIALIZATION_FAILED");
    case VK_ERROR_DEVICE_LOST :
      throw std::runtime_error(function_name + " returned: VK_ERROR_DEVICE_LOST");
    case VK_ERROR_MEMORY_MAP_FAILED :
      throw std::runtime_error(function_name + " returned: VK_ERROR_MEMORY_MAP_FAILED");
    case VK_ERROR_LAYER_NOT_PRESENT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_LAYER_NOT_PRESENT");
    case VK_ERROR_EXTENSION_NOT_PRESENT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_EXTENSION_NOT_PRESENT");
    case VK_ERROR_FEATURE_NOT_PRESENT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_FEATURE_NOT_PRESENT");
    case VK_ERROR_INCOMPATIBLE_DRIVER :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INCOMPATIBLE_DRIVER");
    case VK_ERROR_TOO_MANY_OBJECTS :
      throw std::runtime_error(function_name + " returned: VK_ERROR_TOO_MANY_OBJECTS");
    case VK_ERROR_FORMAT_NOT_SUPPORTED :
      throw std::runtime_error(function_name + " returned: VK_ERROR_FORMAT_NOT_SUPPORTED");
    case VK_ERROR_FRAGMENTED_POOL :
      throw std::runtime_error(function_name + " returned: VK_ERROR_FRAGMENTED_POOL");
    case VK_ERROR_UNKNOWN :
      throw std::runtime_error(function_name + " returned: VK_ERROR_UNKNOWN");
    case VK_ERROR_OUT_OF_POOL_MEMORY :
      throw std::runtime_error(function_name + " returned: VK_ERROR_OUT_OF_POOL_MEMORY");
    case VK_ERROR_INVALID_EXTERNAL_HANDLE :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INVALID_EXTERNAL_HANDLE");
    case VK_ERROR_FRAGMENTATION :
      throw std::runtime_error(function_name + " returned: VK_ERROR_FRAGMENTATION");
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS");
    case VK_ERROR_SURFACE_LOST_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_SURFACE_LOST_KHR");
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
    case VK_ERROR_OUT_OF_DATE_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_OUT_OF_DATE_KHR");
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
    case VK_ERROR_VALIDATION_FAILED_EXT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VALIDATION_FAILED_EXT");
    case VK_ERROR_INVALID_SHADER_NV :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INVALID_SHADER_NV");
    case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR");
    case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR");
    case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR");
    case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR");
    case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR");
    case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR");
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT");
    case VK_ERROR_NOT_PERMITTED_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_NOT_PERMITTED_KHR");
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT");
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR :
      throw std::runtime_error(function_name + " returned: VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR");
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT :
      throw std::runtime_error(function_name + " returned: VK_ERROR_COMPRESSION_EXHAUSTED_EXT");
    case VK_RESULT_MAX_ENUM :
      throw std::runtime_error(function_name + " returned: VK_RESULT_MAX_ENUM");
  }
}
}
