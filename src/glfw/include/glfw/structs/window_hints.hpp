#pragma once

#include <glfw/types/hertz.hpp>

#include <string>

namespace glfw
{
struct window_hints
{
    enum class client_api_type
    {
      opengl_api,
      opengl_es_api,
      no_api
    };

    enum class context_creation_api_type
    {
      native,
      egl,
      osmesa
    };

    enum class context_robustness_type
    {
      no_robustness,
      no_reset_notification,
      lose_context_on_reset
    };

    enum class context_release_behavior_type
    {
      any,
      flush,
      none
    };

    enum class opengl_profile_type
    {
      any,
      compat,
      core
    };

    bool                          resizable                = true;
    bool                          visible                  = true;
    bool                          decorated                = true;
    bool                          focused                  = true;
    bool                          auto_iconify             = true;
    bool                          floating                 = false;
    bool                          maximized                = false;
    bool                          center_cursor            = true;
    bool                          transparent_framebuffer  = false;
    bool                          focus_on_show            = true;
    bool                          scale_to_monitor         = false;
    int                           red_bits                 = 8;
    int                           green_bits               = 8;
    int                           blue_bits                = 8;
    int                           alpha_bits               = 8;
    int                           depth_bits               = 24;
    int                           stencil_bits             = 8;
    int                           samples                  = 0;
    hertz                         refresh_rate             = hertz{-1};
    bool                          stereo                   = false;
    bool                          srgb_capable             = false;
    bool                          doublebuffer             = true;
    client_api_type               client_api               = client_api_type::opengl_api;
    context_creation_api_type     context_creation_api     = context_creation_api_type::native;
    int                           context_version_major    = 1;
    int                           context_version_minor    = 0;
    context_robustness_type       context_robustness       = context_robustness_type::no_robustness;
    context_release_behavior_type context_release_behavior = context_release_behavior_type::any;
    bool                          opengl_forward_compat    = false;
    bool                          opengl_debug_context     = false;
    opengl_profile_type           opengl_profile           = opengl_profile_type::any;
    bool                          cocoa_retina_framebuffer = true;
    std::string                   cocoa_frame_name;
    bool                          cocoa_graphics_switching = false;
    std::string                   x11_class_name;
    std::string                   x11_shared_instance_name;
};
}
