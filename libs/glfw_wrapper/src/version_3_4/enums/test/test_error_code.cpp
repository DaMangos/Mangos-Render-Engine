#include <gtest/gtest.h>

#include "../to_error_code.hpp"

TEST(glfw_version_3_4, int_to_error_code)
{
  ASSERT_THROW(std::ignore = glfw::to_error_code(-1), std::invalid_argument);
}

static_assert(glfw::to_error_code(GLFW_NO_ERROR) == glfw::error_code::no_error);
static_assert(glfw::to_error_code(GLFW_NOT_INITIALIZED) == glfw::error_code::not_initialized);
static_assert(glfw::to_error_code(GLFW_NO_CURRENT_CONTEXT) == glfw::error_code::no_current_context);
static_assert(glfw::to_error_code(GLFW_INVALID_ENUM) == glfw::error_code::invalid_enum);
static_assert(glfw::to_error_code(GLFW_INVALID_VALUE) == glfw::error_code::invalid_value);
static_assert(glfw::to_error_code(GLFW_OUT_OF_MEMORY) == glfw::error_code::out_of_memory);
static_assert(glfw::to_error_code(GLFW_API_UNAVAILABLE) == glfw::error_code::api_unavailable);
static_assert(glfw::to_error_code(GLFW_VERSION_UNAVAILABLE) == glfw::error_code::version_unavailable);
static_assert(glfw::to_error_code(GLFW_PLATFORM_ERROR) == glfw::error_code::platform_error);
