#include "command_buffers.hpp"

namespace vulkan
{
command_buffers::command_buffers(size_type count, pointer ptr, deleter_type &&deleter)
: _count(count),
  _command_buffers(ptr, deleter)
{
}

command_buffers::size_type command_buffers::size() const noexcept
{
  return _count;
}

command_buffers::pointer command_buffers::get() const noexcept
{
  return _command_buffers.get();
}

command_buffers::pointer command_buffers::data() const noexcept
{
  return get();
}

command_buffers::reference command_buffers::operator[](size_type i) const noexcept
{
  return data()[i];
}

command_buffers::reference command_buffers::at(size_type i) const
{
  if(i < _count)
    return data()[i];
  throw std::out_of_range("command_buffers::at");
}

command_buffers::iterator command_buffers::begin() const noexcept
{
  return data();
}

command_buffers::iterator command_buffers::end() const noexcept
{
  return data() + size();
}

command_buffers::iterator command_buffers::cbegin() const noexcept
{
  return begin();
}

command_buffers::iterator command_buffers::cend() const noexcept
{
  return begin();
}

command_buffers::reverse_iterator command_buffers::command_buffers::rbegin() const noexcept
{
  return reverse_iterator(end());
}

command_buffers::reverse_iterator command_buffers::rend() const noexcept
{
  return reverse_iterator(begin());
}

command_buffers::reverse_iterator command_buffers::crbegin() const noexcept
{
  return rbegin();
}

command_buffers::reverse_iterator command_buffers::crend() const noexcept
{
  return rbegin();
}
}