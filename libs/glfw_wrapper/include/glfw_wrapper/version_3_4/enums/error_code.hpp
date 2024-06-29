#pragma once

namespace glfw
{
inline namespace version_3_4
{
enum class error_code
{
  no_error,
  not_initialized,
  no_current_context,
  invalid_enum,
  invalid_value,
  out_of_memory,
  api_unavailable,
  version_unavailable,
  platform_error,
  format_unavailable,
  no_window_context,
};
}
}