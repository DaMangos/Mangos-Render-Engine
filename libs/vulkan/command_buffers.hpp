#pragma once

#include "non_dispatchable.hpp"

#include <vector>

namespace vulkan
{
struct command_buffers
{
    std::uint32_t size() const noexcept;

    VkCommandBuffer const *data() const noexcept;

    std::vector<VkCommandBuffer>::const_iterator begin() const noexcept;

    std::vector<VkCommandBuffer>::const_iterator end() const noexcept;

    std::vector<VkCommandBuffer>::const_iterator cbegin() const noexcept;

    std::vector<VkCommandBuffer>::const_iterator cend() const noexcept;

    std::vector<VkCommandBuffer>::const_reverse_iterator rbegin() const noexcept;

    std::vector<VkCommandBuffer>::const_reverse_iterator rend() const noexcept;

    std::vector<VkCommandBuffer>::const_reverse_iterator crbegin() const noexcept;

    std::vector<VkCommandBuffer>::const_reverse_iterator crend() const noexcept;

    VkCommandBuffer at(std::uint32_t i) const;

    VkCommandBuffer get(std::uint32_t i) const noexcept;

    VkCommandBuffer operator[](std::uint32_t i) const noexcept;

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