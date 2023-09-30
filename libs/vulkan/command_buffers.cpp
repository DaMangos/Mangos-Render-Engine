#include "command_buffers.hpp"

namespace vulkan
{
std::uint32_t command_buffers::size() const noexcept
{
  return _count;
}

VkCommandBuffer const *command_buffers::data() const noexcept
{
  return _ptrs.get();
}

VkCommandBuffer const *command_buffers::begin() const noexcept
{
  return data();
}

VkCommandBuffer const *command_buffers::end() const noexcept
{
  return data() + size();
}

VkCommandBuffer command_buffers::at(std::uint32_t i) const
{
  if(i >= size())
    throw std::out_of_range("vulkan::command_buffers::at");
  return _ptrs[i];
}

VkCommandBuffer command_buffers::operator[](std::uint32_t i) const noexcept
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
                                 std::uint32_t                                                            count,
                                 std::unique_ptr<VkCommandBuffer[]>                                       ptrs) noexcept
: _dispatcher_handle(dispatcher_handle),
  _count(count),
  _ptrs(std::move(ptrs))
{
}

}