#pragma once

#include "vk_common_handle.hpp"

#include <concepts>
#include <stdexcept>
#include <string>

namespace graphics::vk
{
template <class function_pointer>
auto invoke(common_handle<VkInstance> instance, std::string const &function_name, auto &&...function_args)
{
  if (PFN_vkVoidFunction function = vkGetInstanceProcAddr(instance.get(), function_name.c_str()))
    return std::invoke(reinterpret_cast<function_pointer>(function), std::move(function_args)...);
  throw std::runtime_error("failed to find protocol address for " + function_name);
}
}