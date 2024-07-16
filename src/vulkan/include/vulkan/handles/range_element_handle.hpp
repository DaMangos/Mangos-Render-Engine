#pragma once

#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/vulkan.h>

#include <compare>
#include <memory>

namespace vulkan
{
namespace internal
{
struct make_range_element_handle_t;
}

template <class Handle>
class range_element_handle
{
  public:
    [[nodiscard]]
    Handle get() const noexcept;

    [[nodiscard]]
    std::uint32_t index() const noexcept;

    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    Handle const * data() const noexcept;

    void reset() noexcept;

    range_element_handle() noexcept = default;

    range_element_handle(nullhandle_t) noexcept;

    range_element_handle(range_element_handle &&) noexcept = default;

    range_element_handle(range_element_handle const &) noexcept = delete;

    range_element_handle & operator=(nullhandle_t) noexcept;

    range_element_handle & operator=(range_element_handle &&) noexcept = default;

    range_element_handle & operator=(range_element_handle const &) noexcept = delete;

    ~range_element_handle() noexcept = default;

    std::strong_ordering operator<=>(range_element_handle const & other) const noexcept;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::shared_ptr<Handle[]> _handles;
    std::uint32_t             _size  = 0;
    std::uint32_t             _index = 0;

    friend internal::make_range_element_handle_t;
};

using command_buffer = range_element_handle<VkCommandBuffer>;
using descriptor_set = range_element_handle<VkDescriptorSet>;
}