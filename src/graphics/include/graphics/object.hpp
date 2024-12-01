#pragma once

#include <array>

namespace graphics
{
struct object
{
    std::array<float, 3> position;
    std::array<float, 3> color;
};
}