#pragma once

#include <cstdint>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
using value     = int;
using attribute = int;
using pixels    = std::uint32_t;

struct dimensions
{
    std::uint32_t width, height;
};

struct coordinates
{
    std::int32_t x, y;
};

struct scale
{
    float x, y;
};

struct distance
{
    std::uint32_t left, top, right, bottom;
};

struct size
{
    pixels x, y;
};
}