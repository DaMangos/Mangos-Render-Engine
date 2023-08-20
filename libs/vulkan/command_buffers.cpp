#include "command_buffers.hpp"

#include "non_dispatchable_handle.hpp"

namespace vulkan
{
VkCommandBuffer const *command_buffers::get() const noexcept
{
  return _command_buffers.get();
}

VkDevice command_buffers::get_device() const noexcept
{
  return _command_buffers.get_deleter().get_arg<0>();
}

VkCommandPool command_buffers::get_command_pool() const noexcept
{
  return _command_buffers.get_deleter().get_arg<1>();
}

std::uint32_t command_buffers::size() const noexcept
{
  return _command_buffers.get_deleter().get_arg<2>();
}

VkCommandBuffer const *command_buffers::data() const noexcept
{
  return get();
}

VkCommandBuffer const *command_buffers::begin() const noexcept
{
  return data();
}

VkCommandBuffer const *command_buffers::end() const noexcept
{
  return data() + size();
}

VkCommandBuffer const *command_buffers::cbegin() const noexcept
{
  return data();
}

VkCommandBuffer const *command_buffers::cend() const noexcept
{
  return data() + size();
}

std::reverse_iterator<VkCommandBuffer const *> command_buffers::rbegin() const noexcept
{
  return std::reverse_iterator<VkCommandBuffer const *>(begin());
}

std::reverse_iterator<VkCommandBuffer const *> command_buffers::rend() const noexcept
{
  return std::reverse_iterator<VkCommandBuffer const *>(end());
}

std::reverse_iterator<VkCommandBuffer const *> command_buffers::crbegin() const noexcept
{
  return std::reverse_iterator<VkCommandBuffer const *>(cbegin());
}

std::reverse_iterator<VkCommandBuffer const *> command_buffers::crend() const noexcept
{
  return std::reverse_iterator<VkCommandBuffer const *>(cend());
}

command_buffers::element_type command_buffers::at(std::uint32_t i) const
{
  if(i >= size())
    throw std::out_of_range("command_buffers::at");
  return data()[i];
}

command_buffers::element_type command_buffers::operator[](std::uint32_t i) const noexcept
{
  return data()[i];
}

command_buffers::command_buffers(command_pool_handle command_pool, command_buffers_handle command_buffers)
: _command_pool(command_pool),
  _command_buffers(std::move(command_buffers))
{
}
}