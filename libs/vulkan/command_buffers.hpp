#pragma once

#include "non_dispatchable_handle.hpp"

#include <iterator>

namespace vulkan
{
struct command_buffers
{
    using element_type = VkCommandBuffer;
    using pointer      = VkCommandBuffer *;

    VkCommandBuffer const *get() const noexcept;

    VkDevice get_device() const noexcept;

    VkCommandPool get_command_pool() const noexcept;

    std::uint32_t size() const noexcept;

    VkCommandBuffer const *data() const noexcept;

    VkCommandBuffer const *begin() const noexcept;

    VkCommandBuffer const *end() const noexcept;

    VkCommandBuffer const *cbegin() const noexcept;

    VkCommandBuffer const *cend() const noexcept;

    std::reverse_iterator<VkCommandBuffer const *> rbegin() const noexcept;

    std::reverse_iterator<VkCommandBuffer const *> rend() const noexcept;

    std::reverse_iterator<VkCommandBuffer const *> crbegin() const noexcept;

    std::reverse_iterator<VkCommandBuffer const *> crend() const noexcept;

    VkCommandBuffer at(std::uint32_t i) const;

    VkCommandBuffer operator[](std::uint32_t i) const noexcept;

  private:
    friend struct device;

    command_buffers(command_pool_handle command_pool, command_buffers_handle command_buffers);

    command_pool_handle    _command_pool;
    command_buffers_handle _command_buffers;
};
}