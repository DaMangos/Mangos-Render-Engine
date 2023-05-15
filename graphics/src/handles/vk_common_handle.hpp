#pragma once

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#undef GLFW_INCLUDE_VULKAN
#undef VK_ENABLE_BETA_EXTENSIONS

#include <utility>

namespace graphics::vk
{
template <class managed_type>
class common_handle final
{
  public:
    typedef managed_type pointer;

    constexpr explicit common_handle(pointer managed = VK_NULL_HANDLE) noexcept
    : _managed(managed)
    {
    }

    [[nodiscard]]
    constexpr pointer get() const noexcept
    {
      return _managed;
    }

    [[nodiscard]]
    constexpr pointer const * override() noexcept
    {
      return &_managed;
    }

    [[nodiscard]]
    constexpr pointer release() noexcept
    {
      pointer managed = _managed;
      _managed        = VK_NULL_HANDLE;
      return managed;
    }

    constexpr void reset(pointer managed = VK_NULL_HANDLE) noexcept
    {
      _managed = managed;
    }

    constexpr void swap(common_handle &other) noexcept
    {
      std::swap(other._managed, _managed);
    }

  private:
    pointer _managed;
};
}

template <class managed_type>
struct std::hash<graphics::vk::common_handle<managed_type>>
{
    constexpr std::size_t operator()(graphics::vk::common_handle<managed_type> const &handle) const noexcept
    {
      return std::hash<managed_type>{}(handle.get());
    }
};