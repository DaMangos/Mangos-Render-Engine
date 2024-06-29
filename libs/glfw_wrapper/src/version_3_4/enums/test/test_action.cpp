#include <gtest/gtest.h>

#include "../to_action.hpp"

TEST(glfw_version_3_4, int_to_action)
{
  ASSERT_THROW(std::ignore = glfw::to_action(-1), std::invalid_argument);
}

static_assert(glfw::to_action(GLFW_PRESS) == glfw::action::press);
static_assert(glfw::to_action(GLFW_RELEASE) == glfw::action::release);
static_assert(glfw::to_action(GLFW_REPEAT) == glfw::action::repeat);
