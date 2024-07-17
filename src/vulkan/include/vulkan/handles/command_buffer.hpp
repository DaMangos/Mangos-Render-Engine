#pragma once

#include <vulkan/handles/nullhandle.hpp>
#include <vulkan/vulkan.h>

#include <compare>
#include <memory>

namespace vulkan
{
class device;

class command_buffer
{
  public:
    [[nodiscard]]
    VkCommandBuffer get() const noexcept;

    [[nodiscard]]
    std::uint32_t array_index() const noexcept;

    [[nodiscard]]
    std::uint32_t array_size() const noexcept;

    [[nodiscard]]
    VkCommandBuffer const * array_data() const noexcept;

    void reset() noexcept;

    command_buffer() noexcept = default;

    command_buffer(nullhandle_t) noexcept;

    command_buffer(command_buffer &&) noexcept = default;

    command_buffer(command_buffer const &) noexcept = delete;

    command_buffer & operator=(nullhandle_t) noexcept;

    command_buffer & operator=(command_buffer &&) noexcept = default;

    command_buffer & operator=(command_buffer const &) noexcept = delete;

    ~command_buffer() noexcept = default;

    std::strong_ordering operator<=>(command_buffer const & other) const noexcept;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::shared_ptr<VkCommandBuffer[]> _shared_command_buffers;
    std::uint32_t                      _array_size  = 0;
    std::uint32_t                      _array_index = 0;

    friend device;
};
}