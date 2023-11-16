#pragma once

#include "non_dispatchable.hpp"

#include <vector>

namespace vulkan
{
struct descriptor_sets final
{
    using value_type = VkDescriptorSet;

    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *data() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *begin() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *end() const noexcept;

    [[nodiscard]]
    VkDescriptorSet at(std::uint32_t const i) const;

    VkDescriptorSet operator[](std::uint32_t const i) const noexcept;

    ~descriptor_sets();

    descriptor_sets(descriptor_sets &&)                 = default;
    descriptor_sets(descriptor_sets const &)            = delete;
    descriptor_sets &operator=(descriptor_sets &&)      = default;
    descriptor_sets &operator=(descriptor_sets const &) = delete;

  private:
    friend struct device;

    descriptor_sets(std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> const &dispatcher_handle,
                    std::vector<VkDescriptorSet>                                              &&ptrs) noexcept;

    std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> _dispatcher_handle;
    std::vector<VkDescriptorSet>                                         _ptrs;
};
}