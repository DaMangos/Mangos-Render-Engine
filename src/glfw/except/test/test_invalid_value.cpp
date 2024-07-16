#include <glfw/except/invalid_value.hpp>

#include <type_traits>

static_assert(std::is_nothrow_move_constructible_v<glfw::invalid_value>);
static_assert(std::is_nothrow_move_assignable_v<glfw::invalid_value>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::invalid_value>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::invalid_value>);

static_assert(std::is_base_of_v<glfw::exception, glfw::invalid_value>);
static_assert(std::is_base_of_v<std::invalid_argument, glfw::invalid_value>);