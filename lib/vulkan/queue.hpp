#pragma once

#include "non_dispatchable.hpp"

namespace vulkan
{
struct queue final
{
    [[nodiscard]]
    VkQueue get() const noexcept;

    bool operator==(queue const &) const noexcept;

    bool operator!=(queue const &) const noexcept;

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
    std::size_t operator()(vulkan::queue const &obj) const noexcept
    {
      return std::hash<VkQueue>{}(obj.get());
    }
};
