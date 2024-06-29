#include <gtest/gtest.h>

#include "../to_modifiers.hpp"
#include <random>

TEST(glfw_version_3_4, int_to_modifiers)
{
  std::random_device rd;

  auto const random = static_cast<int>(std::default_random_engine(rd())());

  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_SHIFT).Shift);
  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_CONTROL).Control);
  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_ALT).Alt);
  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_SUPER).Super);
  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_CAPS_LOCK).Caps_Lock);
  ASSERT_TRUE(glfw::to_modifiers(random | GLFW_MOD_NUM_LOCK).Num_Lock);

  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_SHIFT).Shift);
  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_CONTROL).Control);
  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_ALT).Alt);
  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_SUPER).Super);
  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_CAPS_LOCK).Caps_Lock);
  ASSERT_FALSE(glfw::to_modifiers(random & ~GLFW_MOD_NUM_LOCK).Num_Lock);
}

static_assert(glfw::to_modifiers(GLFW_MOD_SHIFT).Shift);
static_assert(glfw::to_modifiers(GLFW_MOD_CONTROL).Control);
static_assert(glfw::to_modifiers(GLFW_MOD_ALT).Alt);
static_assert(glfw::to_modifiers(GLFW_MOD_SUPER).Super);
static_assert(glfw::to_modifiers(GLFW_MOD_CAPS_LOCK).Caps_Lock);
static_assert(glfw::to_modifiers(GLFW_MOD_NUM_LOCK).Num_Lock);
