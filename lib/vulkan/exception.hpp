#pragma once

#include <stdexcept>
#include <string>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
struct exception : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

struct bad_result final : exception
{
    bad_result(VkResult result);

    bad_result(VkResult result, std::string const &message);
};

struct bad_handle_access final : exception
{
    bad_handle_access();
};

struct not_found final : exception
{
    not_found(std::string const &name);
};
}