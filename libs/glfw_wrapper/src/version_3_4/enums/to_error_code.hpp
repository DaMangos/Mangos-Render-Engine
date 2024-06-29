#pragma once

#include <glfw_wrapper/version_3_4/enums/error_code.hpp>

#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
inline namespace version_3_4
{
[[nodiscard]]
constexpr error_code to_error_code(int const error_code)
{
  switch(error_code)
  {
    case(GLFW_NO_ERROR) :
      return error_code::no_error;
    case(GLFW_NOT_INITIALIZED) :
      return error_code::not_initialized;
    case(GLFW_NO_CURRENT_CONTEXT) :
      return error_code::no_current_context;
    case(GLFW_INVALID_ENUM) :
      return error_code::invalid_enum;
    case(GLFW_INVALID_VALUE) :
      return error_code::invalid_value;
    case(GLFW_OUT_OF_MEMORY) :
      return error_code::out_of_memory;
    case(GLFW_API_UNAVAILABLE) :
      return error_code::api_unavailable;
    case(GLFW_VERSION_UNAVAILABLE) :
      return error_code::version_unavailable;
    case(GLFW_PLATFORM_ERROR) :
      return error_code::platform_error;
    case(GLFW_FORMAT_UNAVAILABLE) :
      return error_code::format_unavailable;
    case(GLFW_NO_WINDOW_CONTEXT) :
      return error_code::no_window_context;
  }
  throw std::invalid_argument("invalid error_code");
}
}
}