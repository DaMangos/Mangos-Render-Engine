#pragma once

#include <glfw/composites/extent.hpp>

#include <functional>
#include <vector>

namespace glfw
{
inline namespace version_3_4
{
struct image
{
    extent<int>            size;
    std::vector<std::byte> pixels;
};
}
}
