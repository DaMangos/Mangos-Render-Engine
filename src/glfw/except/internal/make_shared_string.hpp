#pragma once

#include <memory>

namespace glfw::internal
{
[[nodiscard]]
std::shared_ptr<char const[]> make_shared_string(char const * const str);
}