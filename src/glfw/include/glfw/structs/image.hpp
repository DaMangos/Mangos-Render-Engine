#pragma once

#include <glfw/structs/extent.hpp>

#include <vector>

namespace glfw
{
struct image
{
    extent<int>            size;
    std::vector<std::byte> pixels;
};
}
