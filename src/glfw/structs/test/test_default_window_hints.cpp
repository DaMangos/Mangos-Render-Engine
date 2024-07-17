#include <glfw/structs/window_hints.hpp>
#include <glfw/types/hertz.hpp>
#include <gtest/gtest.h>

TEST(Glfw, defaultWindowHints)
{
  using namespace glfw::hertz_literals;

  glfw::window_hints const hints = {};

  ASSERT_TRUE(hints.resizable);
  ASSERT_TRUE(hints.visible);
  ASSERT_TRUE(hints.decorated);
  ASSERT_TRUE(hints.focused);
  ASSERT_TRUE(hints.auto_iconify);
  ASSERT_FALSE(hints.floating);
  ASSERT_FALSE(hints.maximized);
  ASSERT_TRUE(hints.center_cursor);
  ASSERT_FALSE(hints.transparent_framebuffer);
  ASSERT_TRUE(hints.focus_on_show);
  ASSERT_FALSE(hints.scale_to_monitor);
  ASSERT_EQ(hints.red_bits, 8);
  ASSERT_EQ(hints.green_bits, 8);
  ASSERT_EQ(hints.blue_bits, 8);
  ASSERT_EQ(hints.alpha_bits, 8);
  ASSERT_EQ(hints.depth_bits, 24);
  ASSERT_EQ(hints.stencil_bits, 8);
  ASSERT_EQ(hints.samples, 0);
  ASSERT_EQ(hints.refresh_rate, -1_hz);
  ASSERT_FALSE(hints.stereo);
  ASSERT_FALSE(hints.srgb_capable);
  ASSERT_TRUE(hints.doublebuffer);
  ASSERT_EQ(hints.client_api, glfw::window_hints::client_api_type::opengl_api);
  ASSERT_EQ(hints.context_creation_api, glfw::window_hints::context_creation_api_type::native);
  ASSERT_EQ(hints.context_version_major, 1);
  ASSERT_EQ(hints.context_version_minor, 0);
  ASSERT_EQ(hints.context_robustness, glfw::window_hints::context_robustness_type::no_robustness);
  ASSERT_EQ(hints.context_release_behavior, glfw::window_hints::context_release_behavior_type::any);
  ASSERT_FALSE(hints.opengl_forward_compat);
  ASSERT_FALSE(hints.opengl_debug_context);
  ASSERT_EQ(hints.opengl_profile, glfw::window_hints::opengl_profile_type::any);
  ASSERT_TRUE(hints.cocoa_retina_framebuffer);
  ASSERT_TRUE(hints.cocoa_frame_name.empty());
  ASSERT_FALSE(hints.cocoa_graphics_switching);
  ASSERT_TRUE(hints.x11_class_name.empty());
  ASSERT_TRUE(hints.x11_shared_instance_name.empty());
}