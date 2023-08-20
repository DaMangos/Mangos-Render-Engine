#pragma once

#include "device.hpp"
#include "non_dispatchable_handle.hpp"

namespace vulkan
{
template <>
struct non_dispatchable_handle<device_handle, descriptor_sets_handle>
{
    using element_type = typename descriptor_sets_handle::element_type;
    using pointer      = typename descriptor_sets_handle::pointer;

    VkDescriptorSet const *get() const noexcept
    {
      return _descriptor_sets.get();
    }

    VkDevice get_device() const noexcept
    {
      return _descriptor_sets.get_deleter().get_arg<0>();
    }

    VkDescriptorPool get_descriptor_pool() const noexcept
    {
      return _descriptor_sets.get_deleter().get_arg<1>();
    }

    std::uint32_t size() const noexcept
    {
      return _descriptor_sets.get_deleter().get_arg<2>();
    }

    VkDescriptorSet const *data() const noexcept
    {
      return get();
    }

    VkDescriptorSet const *begin() const noexcept
    {
      return data();
    }

    VkDescriptorSet const *end() const noexcept
    {
      return data() + size();
    }

    VkDescriptorSet const *cbegin() const noexcept
    {
      return data();
    }

    VkDescriptorSet const *cend() const noexcept
    {
      return data() + size();
    }

    std::reverse_iterator<VkDescriptorSet const *> rbegin() const noexcept
    {
      return std::reverse_iterator<VkDescriptorSet const *>(begin());
    }

    std::reverse_iterator<VkDescriptorSet const *> rend() const noexcept
    {
      return std::reverse_iterator<VkDescriptorSet const *>(end());
    }

    std::reverse_iterator<VkDescriptorSet const *> crbegin() const noexcept
    {
      return std::reverse_iterator<VkDescriptorSet const *>(cbegin());
    }

    std::reverse_iterator<VkDescriptorSet const *> crend() const noexcept
    {
      return std::reverse_iterator<VkDescriptorSet const *>(cend());
    }

    VkDescriptorSet at(std::uint32_t i) const
    {
      if(i >= size())
        throw std::out_of_range("descriptor_sets::at");
      return data()[i];
    }

    VkDescriptorSet operator[](std::uint32_t i) const noexcept
    {
      return data()[i];
    }

  private:
    friend struct device;

    non_dispatchable_handle(descriptor_pool_handle descriptor_pool, descriptor_sets_handle descriptor_sets)
    : _descriptor_pool(descriptor_pool),
      _descriptor_sets(std::move(descriptor_sets))
    {
    }

    descriptor_pool_handle _descriptor_pool;
    descriptor_sets_handle _descriptor_sets;
};
}