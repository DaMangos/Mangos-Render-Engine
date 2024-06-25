#pragma once

namespace glfw
{
inline namespace version_3_4
{
struct library_hints
{
    enum class wayland_libdecor_type
    {
      prefer,
      disable
    };

    bool                  joystick_hat_buttons  = true;
    bool                  cocoa_chdir_resources = true;
    bool                  cocoa_menubar         = true;
    wayland_libdecor_type wayland_libdecor      = wayland_libdecor_type::prefer;
};
}
}