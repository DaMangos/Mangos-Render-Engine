#pragma once

#include <glfw_wrapper/types/hertz.hpp>
#include <glfw_wrapper/version_3_4/structs/channel.hpp>
#include <glfw_wrapper/version_3_4/structs/extent.hpp>

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