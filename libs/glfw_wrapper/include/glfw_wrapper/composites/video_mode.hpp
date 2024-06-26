#pragma once

#include <glfw_wrapper/composites/channel.hpp>
#include <glfw_wrapper/composites/extent.hpp>
#include <glfw_wrapper/units/hertz.hpp>

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