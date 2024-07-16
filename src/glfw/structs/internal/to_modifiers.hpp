#pragma once

#include <glfw/structs/modifiers.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw::internal
{
[[nodiscard]]
constexpr modifiers to_modifiers(int const mods) noexcept
{
  return {
    .Shift     = static_cast<bool>(mods & GLFW_MOD_SHIFT),
    .Control   = static_cast<bool>(mods & GLFW_MOD_CONTROL),
    .Alt       = static_cast<bool>(mods & GLFW_MOD_ALT),
    .Super     = static_cast<bool>(mods & GLFW_MOD_SUPER),
    .Caps_Lock = static_cast<bool>(mods & GLFW_MOD_CAPS_LOCK),
    .Num_Lock  = static_cast<bool>(mods & GLFW_MOD_NUM_LOCK),
  };
}
}
