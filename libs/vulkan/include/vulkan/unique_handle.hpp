#pragma once

#include "shared_dispatcher.hpp"

#include <compare>
#include <optional>

namespace vulkan
{
template <class Dispatcher, class Handle, auto DeleteHandle>
class unique_handle
{
  public:
    [[nodiscard]]
    Handle get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    void reset() noexcept;

    unique_handle() noexcept = default;

    unique_handle(nullhandle_t) noexcept;

    unique_handle(unique_handle && other) noexcept;

    unique_handle(unique_handle const &) noexcept = delete;

    unique_handle & operator=(nullhandle_t) noexcept;

    unique_handle & operator=(unique_handle && other) noexcept;

    unique_handle & operator=(unique_handle const &) noexcept = delete;

    ~unique_handle() noexcept;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(unique_handle const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    shared_dispatcher<Dispatcher>                _dispatcher;
    Handle                                       _handle = VK_NULL_HANDLE;
    std::shared_ptr<VkAllocationCallbacks const> _allocation_callbacks;

    friend struct internal;
};
}
