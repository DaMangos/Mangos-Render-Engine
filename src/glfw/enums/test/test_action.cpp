#include <glfw/enums/action.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static_assert(static_cast<int>(glfw::action::release) == GLFW_RELEASE);
static_assert(static_cast<int>(glfw::action::press) == GLFW_PRESS);
static_assert(static_cast<int>(glfw::action::repeat) == GLFW_REPEAT);
