#include "set_hints.hpp"

#include <GLFW/glfw3.h>

namespace
{
[[nodiscard]]
constexpr int to_int(glfw::window_hints::client_api_type const type) noexcept
{
  switch(type)
  {
    case glfw::window_hints::client_api_type::no_api :
      return GLFW_NO_API;
    case glfw::window_hints::client_api_type::opengl_api :
      return GLFW_OPENGL_API;
    case glfw::window_hints::client_api_type::opengl_es_api :
      return GLFW_OPENGL_ES_API;
    default :
      return GLFW_NO_API;
  }
}

[[nodiscard]]
constexpr int to_int(glfw::window_hints::context_creation_api_type const type) noexcept
{
  switch(type)
  {
    case glfw::window_hints::context_creation_api_type::native :
      return GLFW_NATIVE_CONTEXT_API;
    case glfw::window_hints::context_creation_api_type::egl :
      return GLFW_EGL_CONTEXT_API;
    case glfw::window_hints::context_creation_api_type::osmesa :
      return GLFW_OSMESA_CONTEXT_API;
    default :
      return GLFW_NATIVE_CONTEXT_API;
  }
}

[[nodiscard]]
constexpr int to_int(glfw::window_hints::context_robustness_type const type) noexcept
{
  switch(type)
  {
    case glfw::window_hints::context_robustness_type::no_robustness :
      return GLFW_NO_ROBUSTNESS;
    case glfw::window_hints::context_robustness_type::no_reset_notification :
      return GLFW_NO_RESET_NOTIFICATION;
    case glfw::window_hints::context_robustness_type::lose_context_on_reset :
      return GLFW_LOSE_CONTEXT_ON_RESET;
    default :
      return GLFW_NO_ROBUSTNESS;
  }
}

[[nodiscard]]
constexpr int to_int(glfw::window_hints::context_release_behavior_type const type) noexcept
{
  switch(type)
  {
    case glfw::window_hints::context_release_behavior_type::any :
      return GLFW_ANY_RELEASE_BEHAVIOR;
    case glfw::window_hints::context_release_behavior_type::flush :
      return GLFW_RELEASE_BEHAVIOR_FLUSH;
    case glfw::window_hints::context_release_behavior_type::none :
      return GLFW_RELEASE_BEHAVIOR_NONE;
    default :
      return GLFW_ANY_RELEASE_BEHAVIOR;
  }
}

[[nodiscard]]
constexpr int to_int(glfw::window_hints::opengl_profile_type const type) noexcept
{
  switch(type)
  {
    case glfw::window_hints::opengl_profile_type::any :
      return GLFW_OPENGL_ANY_PROFILE;
    case glfw::window_hints::opengl_profile_type::compat :
      return GLFW_OPENGL_COMPAT_PROFILE;
    case glfw::window_hints::opengl_profile_type::core :
      return GLFW_OPENGL_CORE_PROFILE;
    default :
      return GLFW_OPENGL_ANY_PROFILE;
  }
}

[[nodiscard]]
constexpr int to_int(glfw::library_hints::wayland_libdecor_type const type) noexcept
{
  switch(type)
  {
    case glfw::library_hints::wayland_libdecor_type::prefer :
      return GLFW_WAYLAND_PREFER_LIBDECOR;
    case glfw::library_hints::wayland_libdecor_type::disable :
      return GLFW_WAYLAND_DISABLE_LIBDECOR;
    default :
      return GLFW_WAYLAND_PREFER_LIBDECOR;
  }
}
}

void glfw::set_hints(window_hints const & hints) noexcept
{
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_RESIZABLE, hints.resizable ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_VISIBLE, hints.visible ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED, hints.decorated ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_FOCUSED, hints.focused ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_AUTO_ICONIFY, hints.auto_iconify ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_FLOATING, hints.floating ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, hints.maximized ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_CENTER_CURSOR, hints.center_cursor ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, hints.transparent_framebuffer ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, hints.focus_on_show ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, hints.scale_to_monitor ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_RED_BITS, hints.red_bits);
  glfwWindowHint(GLFW_GREEN_BITS, hints.green_bits);
  glfwWindowHint(GLFW_BLUE_BITS, hints.blue_bits);
  glfwWindowHint(GLFW_ALPHA_BITS, hints.alpha_bits);
  glfwWindowHint(GLFW_DEPTH_BITS, hints.depth_bits);
  glfwWindowHint(GLFW_STENCIL_BITS, hints.stencil_bits);
  glfwWindowHint(GLFW_SAMPLES, hints.samples);
  glfwWindowHint(GLFW_REFRESH_RATE, static_cast<int>(hints.refresh_rate));
  glfwWindowHint(GLFW_STEREO, hints.stereo ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_SRGB_CAPABLE, hints.srgb_capable ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, hints.doublebuffer ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_CLIENT_API, ::to_int(hints.client_api));
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, ::to_int(hints.context_creation_api));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hints.context_version_minor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.context_version_major);
  glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, ::to_int(hints.context_robustness));
  glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, ::to_int(hints.context_release_behavior));
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, hints.opengl_forward_compat ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, hints.opengl_debug_context ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, ::to_int(hints.opengl_profile));
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, hints.cocoa_retina_framebuffer ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHintString(GLFW_COCOA_FRAME_NAME, hints.cocoa_frame_name.c_str());
  glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, hints.cocoa_graphics_switching ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHintString(GLFW_X11_CLASS_NAME, hints.x11_class_name.c_str());
  glfwWindowHintString(GLFW_X11_INSTANCE_NAME, hints.x11_instance_name.c_str());
}

void glfw::set_hints(library_hints const & hints) noexcept
{
  glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, hints.joystick_hat_buttons ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, hints.cocoa_chdir_resources ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_COCOA_MENUBAR, hints.cocoa_menubar ? GLFW_TRUE : GLFW_FALSE);
  glfwInitHint(GLFW_WAYLAND_LIBDECOR, ::to_int(hints.wayland_libdecor));
}