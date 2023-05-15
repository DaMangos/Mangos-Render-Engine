#pragma once

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#undef GLFW_INCLUDE_VULKAN
#undef VK_ENABLE_BETA_EXTENSIONS

#include <utility>

namespace graphics::glfw
{
template <class managed_type>
class common_handle final
{
  public:
    typedef managed_type *pointer;
    typedef managed_type  element_type;

    constexpr explicit common_handle(pointer managed_object = nullptr) noexcept
    : _managed_object(managed_object)
    {
    }

    [[nodiscard]]
    constexpr pointer get() const noexcept
    {
      return _managed_object;
    }

    [[nodiscard]]
    constexpr pointer release() noexcept
    {
      pointer managed_object = _managed_object;
      _managed_object        = nullptr;
      return managed_object;
    }

    constexpr void reset(pointer managed_object = nullptr) noexcept
    {
      _managed_object = managed_object;
    }

    constexpr void swap(common_handle &other) noexcept
    {
      std::swap(other._managed_object, _managed_object);
    }

  private:
    pointer _managed_object;
};
}

template <class managed_type>
struct std::hash<graphics::glfw::common_handle<managed_type>>
{
    constexpr std::size_t operator()(graphics::glfw::common_handle<managed_type> const &handle) const noexcept
    {
      return std::hash<managed_type>{}(handle.get());
    }
};