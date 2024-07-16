#pragma once

#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/handles/shared_dispatcher.hpp>

#include <compare>

namespace vulkan
{
namespace internal
{
struct make_shared_handle_t;
struct create_shared_handle_t;
}

template <class Dispatcher, class Handle, auto DeleteHandle>
class unique_handle;

template <class Dispatcher, class Handle, auto DeleteHandle>
class shared_handle
{
  public:
    [[nodiscard]]
    Handle get() const noexcept;

    [[nodiscard]]
    VkAllocationCallbacks const * get_allocation_callbacks() const noexcept;

    void reset() noexcept;

    shared_handle() noexcept = default;

    shared_handle(nullhandle_t) noexcept;

    shared_handle(shared_handle &&) noexcept = default;

    shared_handle(shared_handle const &) noexcept = delete;

    shared_handle & operator=(nullhandle_t) noexcept;

    shared_handle & operator=(shared_handle &&) noexcept = default;

    shared_handle & operator=(shared_handle const &) noexcept = delete;

    ~shared_handle() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(shared_handle const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::shared_ptr<unique_handle<Dispatcher, Handle, DeleteHandle>> _shared;

    friend internal::make_shared_handle_t;
    friend internal::create_shared_handle_t;
};

using command_pool    = shared_handle<VkDevice, VkCommandPool, vkDestroyCommandPool>;
using descriptor_pool = shared_handle<VkDevice, VkDescriptorPool, vkDestroyDescriptorPool>;
}