#pragma once

#include <vector>

namespace graphics::internal::vulkan_config
{
struct instance_extensions_flags
{
    bool enable_debug       = false;
    bool enable_portability = false;
};

[[nodiscard]]
std::vector<char const *> get_required_instance_extensions(instance_extensions_flags const & flags = {});
}