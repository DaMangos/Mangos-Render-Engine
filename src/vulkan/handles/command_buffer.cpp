#include <vulkan/handles/command_buffer.hpp>
#include <vulkan/vulkan.h>

VkCommandBuffer vulkan::command_buffer::get() const noexcept
{
  return _shared_command_buffers[static_cast<std::ptrdiff_t>(_array_index)];
}

std::uint32_t vulkan::command_buffer::array_index() const noexcept
{
  return _array_index;
}

std::uint32_t vulkan::command_buffer::array_size() const noexcept
{
  return _array_size;
}

VkCommandBuffer const * vulkan::command_buffer::array_data() const noexcept
{
  return _shared_command_buffers.get();
}

void vulkan::command_buffer::reset() noexcept
{
  _shared_command_buffers.reset();
  _array_size  = 0;
  _array_index = 0;
}

vulkan::command_buffer::command_buffer(nullhandle_t) noexcept
{
}

vulkan::command_buffer & vulkan::command_buffer::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

std::strong_ordering vulkan::command_buffer::operator<=>(command_buffer const & other) const noexcept
{
  return _shared_command_buffers <=> other._shared_command_buffers;
}

std::strong_ordering vulkan::command_buffer::operator<=>(nullhandle_t) const noexcept
{
  return _shared_command_buffers <=> nullptr;
}

vulkan::command_buffer::operator bool() const noexcept
{
  return static_cast<bool>(_shared_command_buffers);
}
