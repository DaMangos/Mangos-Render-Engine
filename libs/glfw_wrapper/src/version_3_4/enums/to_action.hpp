#pragma once

#include <glfw_wrapper/version_3_4/enums/action.hpp>

#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
inline namespace version_3_4
{
[[nodiscard]]
constexpr action to_action(int const action)
{
  switch(action)
  {
    case(GLFW_PRESS) :
      return action::press;
    case(GLFW_RELEASE) :
      return action::release;
    case(GLFW_REPEAT) :
      return action::repeat;
  }
  throw std::invalid_argument("invalid action");
}
}
}