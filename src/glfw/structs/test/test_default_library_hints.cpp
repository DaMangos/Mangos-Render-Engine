#include <glfw/structs/library_hints.hpp>
#include <gtest/gtest.h>

TEST(Glfw, defaultLibraryHints)
{
  glfw::library_hints const hints = {};

  ASSERT_TRUE(hints.joystick_hat_buttons);
  ASSERT_TRUE(hints.cocoa_chdir_resources);
  ASSERT_TRUE(hints.cocoa_menubar);
  ASSERT_EQ(hints.wayland_libdecor, glfw::library_hints::wayland_libdecor_type::prefer);
}