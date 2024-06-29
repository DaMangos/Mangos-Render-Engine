#include <gtest/gtest.h>

#include "../to_mouse_button.hpp"

TEST(glfw_version_3_4, to_mouse_button)
{
  ASSERT_THROW(std::ignore = glfw::to_mouse_button(-1), std::invalid_argument);
}

static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_LEFT) == glfw::mouse_button::Left);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_RIGHT) == glfw::mouse_button::Right);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_MIDDLE) == glfw::mouse_button::Middle);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_1) == glfw::mouse_button::Left);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_2) == glfw::mouse_button::Right);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_3) == glfw::mouse_button::Middle);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_4) == glfw::mouse_button::Button_4);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_5) == glfw::mouse_button::Button_5);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_6) == glfw::mouse_button::Button_6);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_7) == glfw::mouse_button::Button_7);
static_assert(glfw::to_mouse_button(GLFW_MOUSE_BUTTON_8) == glfw::mouse_button::Button_8);
