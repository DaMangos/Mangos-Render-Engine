#include "command_buffers.hpp"

namespace vulkan
{
std::uint32_t command_buffers::size() const noexcept
{
  return static_cast<std::uint32_t>(_command_buffers.get<2>().size());
}

VkCommandBuffer const *command_buffers::data() const noexcept
{
  return _command_buffers.get<2>().data();
}

std::vector<VkCommandBuffer>::const_iterator command_buffers::begin() const noexcept
{
  return _command_buffers.get<2>().begin();
}

std::vector<VkCommandBuffer>::const_iterator command_buffers::end() const noexcept
{
  return _command_buffers.get<2>().end();
}

std::vector<VkCommandBuffer>::const_iterator command_buffers::cbegin() const noexcept
{
  return _command_buffers.get<2>().cbegin();
}

std::vector<VkCommandBuffer>::const_iterator command_buffers::cend() const noexcept
{
  return _command_buffers.get<2>().cend();
}

std::vector<VkCommandBuffer>::const_reverse_iterator command_buffers::rbegin() const noexcept
{
  return _command_buffers.get<2>().rbegin();
}

std::vector<VkCommandBuffer>::const_reverse_iterator command_buffers::rend() const noexcept
{
  return _command_buffers.get<2>().rend();
}

std::vector<VkCommandBuffer>::const_reverse_iterator command_buffers::crbegin() const noexcept
{
  return _command_buffers.get<2>().crbegin();
}

std::vector<VkCommandBuffer>::const_reverse_iterator command_buffers::crend() const noexcept
{
  return _command_buffers.get<2>().crend();
}

VkCommandBuffer command_buffers::at(std::uint32_t i) const
{
  return _command_buffers.get<2>().at(i);
}

VkCommandBuffer command_buffers::operator[](std::uint32_t i) const noexcept
{
  return _command_buffers.get<2>()[i];
}

command_buffers::command_buffers(VkDevice                       device,
                                 VkCommandPool                  command_pool,
                                 std::vector<VkCommandBuffer> &&command_buffers) noexcept
: _command_buffers(device, command_pool, std::move(command_buffers))
{
}
}