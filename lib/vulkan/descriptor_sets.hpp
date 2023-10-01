#pragma once

#include "non_dispatchable.hpp"

namespace vulkan
{
struct descriptor_sets final
{
    [[nodiscard]]
    std::uint32_t size() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *data() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *begin() const noexcept;

    [[nodiscard]]
    VkDescriptorSet const *end() const noexcept;

    [[nodiscard]]
    VkDescriptorSet at(std::uint32_t i) const;

    VkDescriptorSet operator[](std::uint32_t i) const noexcept;

    ~descriptor_sets();

    descriptor_sets(descriptor_sets &&)                 = default;
    descriptor_sets(descriptor_sets const &)            = delete;
    descriptor_sets &operator=(descriptor_sets &&)      = default;
    descriptor_sets &operator=(descriptor_sets const &) = delete;

  private:
    friend struct device;

    descriptor_sets(std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> const &dispatcher_handle,
                    std::uint32_t                                                               count,
                    std::unique_ptr<VkDescriptorSet[]>                                          ptrs) noexcept;

    std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> _dispatcher_handle;
    std::uint32_t                                                        _count;
    std::unique_ptr<VkDescriptorSet[]>                                   _ptrs;
};
}