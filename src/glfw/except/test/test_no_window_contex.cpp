#include <glfw/except/no_window_context.hpp>

#include <type_traits>

static_assert(std::is_nothrow_move_constructible_v<glfw::no_window_context>);
static_assert(std::is_nothrow_move_assignable_v<glfw::no_window_context>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::no_window_context>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::no_window_context>);

static_assert(std::is_base_of_v<glfw::exception, glfw::no_window_context>);
static_assert(std::is_base_of_v<std::logic_error, glfw::no_window_context>);