#include <glfw/except/api_unavailable.hpp>

#include <type_traits>

static_assert(std::is_nothrow_move_constructible_v<glfw::api_unavailable>);
static_assert(std::is_nothrow_move_assignable_v<glfw::api_unavailable>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::api_unavailable>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::api_unavailable>);

static_assert(std::is_base_of_v<glfw::exception, glfw::api_unavailable>);
static_assert(std::is_base_of_v<std::runtime_error, glfw::api_unavailable>);