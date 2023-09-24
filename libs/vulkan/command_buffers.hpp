#pragma once

#include "non_dispatchable.hpp"

#include <vector>

namespace vulkan
{
struct command_buffers
{
    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    VkCommandBuffer const *data() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_iterator begin() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_iterator end() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_iterator cbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_iterator cend() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_reverse_iterator rbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_reverse_iterator rend() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_reverse_iterator crbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkCommandBuffer>::const_reverse_iterator crend() const noexcept;

    [[nodiscard]]
    VkCommandBuffer at(std::uint32_t i) const;

    [[nodiscard]]
    VkCommandBuffer
    operator[](std::uint32_t i) const noexcept;

  private:
    friend struct device;

    command_buffers(VkDevice device, VkCommandPool command_pool, std::vector<VkCommandBuffer> &&command_buffers) noexcept;

    mgo::apply_in_destructor<[](VkDevice device, VkCommandPool command_pool, std::vector<VkCommandBuffer> &&command_buffers) {
      vkFreeCommandBuffers(device, command_pool, static_cast<std::uint32_t>(command_buffers.size()), command_buffers.data());
    },
                             VkDevice,
                             VkCommandPool,
                             std::vector<VkCommandBuffer>>
      _command_buffers;
};
}