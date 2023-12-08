#include "descriptor_sets.hpp"

namespace vulkan
{
bool descriptor_sets::empty() const noexcept
{
  return _ptrs.empty();
}

std::uint32_t descriptor_sets::size() const noexcept
{
  return static_cast<std::uint32_t>(_ptrs.size());
}

VkDescriptorSet const *descriptor_sets::data() const noexcept
{
  return _ptrs.data();
}

VkDescriptorSet const *descriptor_sets::begin() const noexcept
{
  return data();
}

VkDescriptorSet const *descriptor_sets::end() const noexcept
{
  return std::next(data(), size());
}

VkDescriptorSet descriptor_sets::at(std::uint32_t const i) const
{
  return _ptrs.at(i);
}

VkDescriptorSet descriptor_sets::operator[](std::uint32_t const i) const noexcept
{
  return _ptrs[i];
}

descriptor_sets::~descriptor_sets()
{
  vkFreeDescriptorSets(std::get_deleter<descriptor_pool::deleter>(_dispatcher_handle)->dispatcher_handle.get(),
                       _dispatcher_handle.get(),
                       size(),
                       data());
}

descriptor_sets::descriptor_sets(std::shared_ptr<std::pointer_traits<VkDescriptorPool>::element_type> const &dispatcher_handle,
                                 std::vector<VkDescriptorSet>                                              &&ptrs) noexcept
: _dispatcher_handle(dispatcher_handle),
  _ptrs(std::move(ptrs))
{
}
}