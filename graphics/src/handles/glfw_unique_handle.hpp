#pragma once

#include <memory>

namespace graphics::glfw
{
template <class managed_type>
using unique_handle = std::unique_ptr<managed_type, void (*)(managed_type *)>;
}