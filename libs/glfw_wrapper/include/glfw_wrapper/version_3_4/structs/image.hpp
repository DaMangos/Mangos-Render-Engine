#pragma once

#include <glfw_wrapper/version_3_4/structs/extent.hpp>

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
