#include <glfw/enums/mouse_button.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static_assert(static_cast<int>(glfw::mouse_button::Left) == GLFW_MOUSE_BUTTON_LEFT);
static_assert(static_cast<int>(glfw::mouse_button::Right) == GLFW_MOUSE_BUTTON_RIGHT);
static_assert(static_cast<int>(glfw::mouse_button::Middle) == GLFW_MOUSE_BUTTON_MIDDLE);
static_assert(static_cast<int>(glfw::mouse_button::Button_1) == GLFW_MOUSE_BUTTON_1);
static_assert(static_cast<int>(glfw::mouse_button::Button_2) == GLFW_MOUSE_BUTTON_2);
static_assert(static_cast<int>(glfw::mouse_button::Button_3) == GLFW_MOUSE_BUTTON_3);
static_assert(static_cast<int>(glfw::mouse_button::Button_4) == GLFW_MOUSE_BUTTON_4);
static_assert(static_cast<int>(glfw::mouse_button::Button_5) == GLFW_MOUSE_BUTTON_5);
static_assert(static_cast<int>(glfw::mouse_button::Button_6) == GLFW_MOUSE_BUTTON_6);
static_assert(static_cast<int>(glfw::mouse_button::Button_7) == GLFW_MOUSE_BUTTON_7);
static_assert(static_cast<int>(glfw::mouse_button::Button_8) == GLFW_MOUSE_BUTTON_8);
