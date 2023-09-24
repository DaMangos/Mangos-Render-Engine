#pragma once

#include "non_dispatchable.hpp"

#include <vector>

namespace vulkan
{
struct descriptor_sets final
{
    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *data() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_iterator begin() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_iterator end() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_iterator cbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_iterator cend() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_reverse_iterator rbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_reverse_iterator rend() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_reverse_iterator crbegin() const noexcept;

    [[nodiscard]]
    std::vector<VkDescriptorSet>::const_reverse_iterator crend() const noexcept;

    [[nodiscard]]
    VkDescriptorSet at(std::uint32_t i) const;

    [[nodiscard]]
    VkDescriptorSet
    operator[](std::uint32_t i) const noexcept;

  private:
    friend struct device;

    descriptor_sets(VkDevice device, VkDescriptorPool descriptor_pool, std::vector<VkDescriptorSet> &&descriptor_sets) noexcept;

    mgo::apply_in_destructor<
      [](VkDevice device, VkDescriptorPool descriptor_pool, std::vector<VkDescriptorSet> &&descriptor_sets) {
        vkFreeDescriptorSets(device,
                             descriptor_pool,
                             static_cast<std::uint32_t>(descriptor_sets.size()),
                             descriptor_sets.data());
      },
      VkDevice,
      VkDescriptorPool,
      std::vector<VkDescriptorSet>>
      _descriptor_sets;
};
}