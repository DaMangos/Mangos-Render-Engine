#pragma once

#include <glfw_wrapper/version_3_4/enums/mouse_button.hpp>

#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
inline namespace version_3_4
{
[[nodiscard]]
constexpr mouse_button to_mouse_button(int const mouse_button)
{
  switch(mouse_button)
  {
    case GLFW_MOUSE_BUTTON_LEFT :
      return mouse_button::Left;
    case GLFW_MOUSE_BUTTON_RIGHT :
      return mouse_button::Right;
    case GLFW_MOUSE_BUTTON_MIDDLE :
      return mouse_button::Middle;
    case GLFW_MOUSE_BUTTON_4 :
      return mouse_button::Button_4;
    case GLFW_MOUSE_BUTTON_5 :
      return mouse_button::Button_5;
    case GLFW_MOUSE_BUTTON_6 :
      return mouse_button::Button_6;
    case GLFW_MOUSE_BUTTON_7 :
      return mouse_button::Button_7;
    case GLFW_MOUSE_BUTTON_8 :
      return mouse_button::Button_8;
  }
  throw std::invalid_argument("invalid mouse_button");
}
}
}