#pragma once

#include "unique_deleter.hpp"

#include <ranges>
#include <utility>
#include <vector>

namespace graphics::vulkan
{
template <class managed_type>
struct handle_deleter;

template <class managed_type>
struct unique_handle;

template <class managed_type>
struct unique_handle<managed_type *>
{
    using deleter_type = handle_deleter<managed_type *>;
    using element_type = managed_type;
    using pointer      = managed_type *;

    unique_handle(pointer pointer, auto &&...deleter_args) noexcept
    : _pointer(pointer),
      _deleter(std::forward<decltype(deleter_args)>(deleter_args)...)
    {
    }

    unique_handle(unique_handle &&other) noexcept
    : _pointer(other.release()),
      _deleter(std::move(other._deleter))
    {
    }

    unique_handle &operator=(unique_handle &&other) noexcept
    {
      reset(other.release());
      _deleter = std::move(other._deleter);
      return *this;
    }

    ~unique_handle()
    {
      reset();
    }

    pointer get() const noexcept
    {
      return _pointer;
    }

    explicit operator bool() const noexcept
    {
      return _pointer != nullptr;
    }

    [[nodiscard]]
    pointer release() noexcept
    {
      pointer old_pointer = _pointer;
      _pointer            = nullptr;
      return old_pointer;
    }

    void reset(pointer new_pointer = nullptr) noexcept
    {
      if(_pointer)
        _deleter(_pointer);
      _pointer = new_pointer;
    }

    void swap(unique_handle &other) noexcept
    {
      std::swap(_pointer, other._pointer);
      std::swap(_deleter, other._deleter);
    }

    unique_handle(unique_handle const &)            = delete;
    unique_handle &operator=(unique_handle const &) = delete;

  private:
    pointer      _pointer;
    deleter_type _deleter;
};

template <class managed_type>
struct unique_handle<managed_type *[]>
{
  using deleter_type = handle_deleter<managed_type *[]>;
  using element_type = managed_type;
  using pointer      = managed_type *;

  unique_handle(std::vector<pointer> & array, auto &&...deleter_args) noexcept
  : _array(std::move(array)),
    _deleter(std::forward<decltype(deleter_args)>(deleter_args)...)
  {
  }

  unique_handle(std::nullptr_t, auto &&...deleter_args) noexcept
  : _array(),
    _deleter(std::forward<decltype(deleter_args)>(deleter_args)...)
  {
  }

  unique_handle(unique_handle && other) noexcept
  : _array(std::move(other._array)),
    _deleter(std::move(other._deleter))
  {
  }

  unique_handle &operator=(unique_handle &&other) noexcept
  {
    reset(other.release());
    _deleter = std::move(other._deleter);
    return *this;
  }

  ~unique_handle()
  {
    reset();
  }

  pointer get() const noexcept
  {
    return _array.data();
  }

  pointer operator[](typename std::vector<pointer>::size_type i) const noexcept
  {
    return _array[i];
  }

  explicit operator bool() const noexcept
  {
    return _array.empty();
  }

  [[nodiscard]]
  std::vector<pointer> release() noexcept
  {
    return std::move(_array);
  }

  void reset(std::vector<pointer> & new_array) noexcept
  {
    if(_array.empty())
      _deleter(_array);
    _array = std::move(new_array);
  }

  void reset() noexcept
  {
    if(_array.empty())
      _deleter(_array);
    _array.clear();
  }

  void swap(unique_handle & other) noexcept
  {
    std::swap(_array, other._array);
    std::swap(_deleter, other._deleter);
  }

  unique_handle(unique_handle const &)            = delete;
  unique_handle &operator=(unique_handle const &) = delete;

private:
  std::vector<pointer> _array;
  deleter_type         _deleter;
};

template <class managed_type>
inline auto operator<=>(unique_handle<managed_type> const &lhs, unique_handle<managed_type> const &rhs)
{
  return lhs.get() <=> rhs.get();
}

template <class managed_type>
unique_handle<managed_type> make_handle_for_overwrite(auto &&...deleter_args)
{
  return unique_handle<managed_type>({}, std::forward<decltype(deleter_args)>(deleter_args)...);
}
}

template <class managed_type>
struct std::hash<graphics::vulkan::unique_handle<managed_type>>
{
    std::size_t operator()(graphics::vulkan::unique_handle<managed_type> const &handle) const noexcept
    {
      return std::hash<typename graphics::vulkan::unique_handle<managed_type>::pointer>()(handle.get());
    }
};
