#pragma once

#include "non_dispatchable_handles.hpp"

namespace vulkan
{
struct queue final
{
    using pointer      = typename std::pointer_traits<VkQueue>::pointer;
    using element_type = typename std::pointer_traits<VkQueue>::element_type;

    [[nodiscard]]
    constexpr VkQueue get() const noexcept
    {
      return _ptr;
    }

    constexpr operator bool() const noexcept
    {
      return static_cast<bool>(_ptr);
    }

    constexpr bool operator==(std::nullptr_t null) noexcept
    {
      return _ptr == null;
    }

    constexpr bool operator!=(std::nullptr_t null) noexcept
    {
      return _ptr != null;
    }

    constexpr bool operator==(queue const &other) noexcept
    {
      return _ptr == other._ptr;
    }

    constexpr bool operator!=(queue const &other) noexcept
    {
      return _ptr != other._ptr;
    }

    queue(queue &&)                 = default;
    queue(queue const &)            = delete;
    queue &operator=(queue &&)      = default;
    queue &operator=(queue const &) = delete;
    ~queue()                        = default;

  private:
    friend struct device;

    queue(std::shared_ptr<std::pointer_traits<VkDevice>::element_type> const &dispatcher, VkQueue const ptr) noexcept;

    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _dispatcher;
    VkQueue                                                      _ptr;
};
}

template <>
struct std::hash<vulkan::queue>
{
    constexpr std::size_t operator()(vulkan::queue const &obj) const noexcept
    {
      return std::hash<VkQueue>{}(obj.get());
    }
};
