#pragma once

#include <glfw/structs/channel.hpp>
#include <glfw/structs/extent.hpp>
#include <glfw/types/hertz.hpp>

namespace glfw
{
struct video_mode
{
    extent<int>  size;
    channel<int> channel;
    hertz        refresh_rate;
};
}