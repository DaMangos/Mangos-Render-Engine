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
    std::uint32_t array_index() const noexcept;

    [[nodiscard]]
    std::uint32_t array_size() const noexcept;

    [[nodiscard]]
    Handle const * array_data() const noexcept;

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
    std::shared_ptr<Handle[]> _shared_handles;
    std::uint32_t             _array_size  = 0;
    std::uint32_t             _array_index = 0;

    friend internal::make_range_element_handle_t;
};

using descriptor_set = range_element_handle<VkDescriptorSet>;
}