#include <glfw/except/format_unavailable.hpp>

#include <type_traits>

static_assert(std::is_nothrow_move_constructible_v<glfw::format_unavailable>);
static_assert(std::is_nothrow_move_assignable_v<glfw::format_unavailable>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::format_unavailable>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::format_unavailable>);

static_assert(std::is_base_of_v<glfw::exception, glfw::format_unavailable>);
static_assert(std::is_base_of_v<std::exception, glfw::format_unavailable>);