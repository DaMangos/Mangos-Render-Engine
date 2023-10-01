#include "descriptor_sets.hpp"

namespace vulkan
{
std::uint32_t descriptor_sets::size() const noexcept
{
  return _count;
}

VkDescriptorSet const *descriptor_sets::data() const noexcept
{
  return _ptrs.get();
}

VkDescriptorSet const *descriptor_sets::begin() const noexcept
{
  return data();
}

VkDescriptorSet const *descriptor_sets::end() const noexcept
{
  return std::next(data(), size());
}

VkDescriptorSet descriptor_sets::at(std::uint32_t i) const
{
  if(i >= size())
    throw std::out_of_range("vulkan::descriptor_sets::at");
  return _ptrs[i];
}

VkDescriptorSet descriptor_sets::operator[](std::uint32_t i) const noexcept
{
  return _ptrs[i];
}

descriptor_sets::~descriptor_sets()
{
  vkFreeDescriptorSets(std::get_deleter<descriptor_pool::deleter>(_dispatcher_handle)->_dispatcher_handle.get(),
                       _dispatcher_handle.get(),
                       size(),
                       data());
}

descriptor_sets::descriptor_sets(std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> const &dispatcher_handle,
                                 std::uint32_t                                                               count,
                                 std::unique_ptr<VkDescriptorSet[]>                                          ptrs) noexcept
: _dispatcher_handle(dispatcher_handle),
  _count(count),
  _ptrs(std::move(ptrs))
{
}
}