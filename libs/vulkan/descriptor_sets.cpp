#include "descriptor_sets.hpp"

namespace vulkan
{
std::uint32_t descriptor_sets::size() const noexcept
{
  return static_cast<std::uint32_t>(_descriptor_sets.get<2>().size());
}

VkDescriptorSet const *descriptor_sets::data() const noexcept
{
  return _descriptor_sets.get<2>().data();
}

std::vector<VkDescriptorSet>::const_iterator descriptor_sets::begin() const noexcept
{
  return _descriptor_sets.get<2>().begin();
}

std::vector<VkDescriptorSet>::const_iterator descriptor_sets::end() const noexcept
{
  return _descriptor_sets.get<2>().end();
}

std::vector<VkDescriptorSet>::const_iterator descriptor_sets::cbegin() const noexcept
{
  return _descriptor_sets.get<2>().cbegin();
}

std::vector<VkDescriptorSet>::const_iterator descriptor_sets::cend() const noexcept
{
  return _descriptor_sets.get<2>().cend();
}

std::vector<VkDescriptorSet>::const_reverse_iterator descriptor_sets::rbegin() const noexcept
{
  return _descriptor_sets.get<2>().rbegin();
}

std::vector<VkDescriptorSet>::const_reverse_iterator descriptor_sets::rend() const noexcept
{
  return _descriptor_sets.get<2>().rend();
}

std::vector<VkDescriptorSet>::const_reverse_iterator descriptor_sets::crbegin() const noexcept
{
  return _descriptor_sets.get<2>().crbegin();
}

std::vector<VkDescriptorSet>::const_reverse_iterator descriptor_sets::crend() const noexcept
{
  return _descriptor_sets.get<2>().crend();
}

VkDescriptorSet descriptor_sets::at(std::uint32_t i) const
{
  return _descriptor_sets.get<2>().at(i);
}

VkDescriptorSet descriptor_sets::operator[](std::uint32_t i) const noexcept
{
  return _descriptor_sets.get<2>()[i];
}

descriptor_sets::descriptor_sets(VkDevice                       device,
                                 VkDescriptorPool               descriptor_pool,
                                 std::vector<VkDescriptorSet> &&descriptor_sets) noexcept
: _descriptor_sets(device, descriptor_pool, std::move(descriptor_sets))
{
}
}