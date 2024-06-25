#pragma once

#include <glfw/composites/channel.hpp>
#include <glfw/composites/extent.hpp>
#include <glfw/units/hertz.hpp>

namespace glfw
{
inline namespace version_3_4
{
struct video_mode
{
    extent<int>  size;
    channel<int> channel;
    hertz        refresh_rate;
};
}
}