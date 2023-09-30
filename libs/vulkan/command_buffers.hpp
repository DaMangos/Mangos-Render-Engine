#pragma once

#include "device.hpp"
#include "non_dispatchable.hpp"

#include <iterator>
#include <memory>

namespace vulkan
{
struct command_buffers
{
    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    VkCommandBuffer const *data() const noexcept;

    [[nodiscard]]
    VkCommandBuffer const *begin() const noexcept;

    [[nodiscard]]
    VkCommandBuffer const *end() const noexcept;

    [[nodiscard]]
    VkCommandBuffer at(std::uint32_t i) const;

    VkCommandBuffer operator[](std::uint32_t i) const noexcept;

    ~command_buffers();

    command_buffers(command_buffers &&)                 = default;
    command_buffers(command_buffers const &)            = delete;
    command_buffers &operator=(command_buffers &&)      = default;
    command_buffers &operator=(command_buffers const &) = delete;

  private:
    friend struct device;

    command_buffers(std::shared_ptr<std::pointer_traits<VkCommandPool>::element_type> const &dispatcher_handle,
                    std::uint32_t                                                            count,
                    std::unique_ptr<VkCommandBuffer[]>                                       ptrs) noexcept;

    std::shared_ptr<std::pointer_traits<VkCommandPool>::element_type> _dispatcher_handle;
    std::uint32_t                                                     _count;
    std::unique_ptr<VkCommandBuffer[]>                                _ptrs;
};
}