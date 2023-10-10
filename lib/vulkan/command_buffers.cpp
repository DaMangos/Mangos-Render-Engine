#include "command_buffers.hpp"

namespace vulkan
{
std::uint32_t command_buffers::size() const noexcept
{
  return static_cast<std::uint32_t>(_ptrs.size());
}

VkCommandBuffer const *command_buffers::data() const noexcept
{
  return _ptrs.data();
}

VkCommandBuffer const *command_buffers::begin() const noexcept
{
  return data();
}

VkCommandBuffer const *command_buffers::end() const noexcept
{
  return std::next(data(), size());
}

VkCommandBuffer command_buffers::at(std::uint32_t const i) const
{
  return _ptrs.at(i);
}

VkCommandBuffer command_buffers::operator[](std::uint32_t const i) const noexcept
{
  return _ptrs[i];
}

command_buffers::~command_buffers()
{
  vkFreeCommandBuffers(std::get_deleter<command_pool::deleter>(_dispatcher_handle)->_dispatcher_handle.get(),
                       _dispatcher_handle.get(),
                       size(),
                       data());
}

command_buffers::command_buffers(std::shared_ptr<std::pointer_traits<VkCommandPool>::element_type> const &dispatcher_handle,
                                 std::vector<VkCommandBuffer>                                           &&ptrs) noexcept
: _dispatcher_handle(dispatcher_handle),
  _ptrs(std::move(ptrs))
{
}
}