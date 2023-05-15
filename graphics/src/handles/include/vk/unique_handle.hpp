#pragma once

#include <vk/deleter.hpp>

namespace graphics::vk
{
template <class managed_type>
class unique_handle final
{
  public:
    typedef managed_type     pointer;
    typedef deleter<pointer> deleter_type;

    constexpr explicit unique_handle(auto &&...deleter_args) noexcept
    : _managed(VK_NULL_HANDLE),
      _deleter(std::move(deleter_args)...)
    {
    }

    constexpr unique_handle(unique_handle &&other) noexcept
    : _managed(other.release()),
      _deleter(other._deleter)
    {
    }

    constexpr unique_handle &operator=(unique_handle &&other) noexcept
    {
      reset(other.release());
      _deleter = other._deleter;
      return *this;
    }

    constexpr ~unique_handle()
    {
      reset();
    }

    [[nodiscard]]
    constexpr pointer get() const noexcept
    {
      return _managed;
    }

    [[nodiscard]]
    constexpr pointer * override() noexcept
    {
      reset();
      return &_managed;
    }

    [[nodiscard]]
    constexpr pointer release() noexcept
    {
      pointer managed = _managed;
      _managed        = VK_NULL_HANDLE;
      return managed;
    }

    constexpr void reset(pointer managed = VK_NULL_HANDLE) noexcept
    {
      if (_managed != VK_NULL_HANDLE)
        _deleter(_managed);
      _managed = managed;
    }

    constexpr void swap(unique_handle &other) noexcept
    {
      std::swap(other._managed, _managed);
      std::swap(other._deleter, _deleter);
    }

    unique_handle(unique_handle const &) = delete;

    unique_handle &operator=(unique_handle const &) = delete;

  private:
    pointer          _managed;
    deleter<pointer> _deleter;
};
}

template <class managed_type>
struct std::hash<graphics::vk::unique_handle<managed_type>>
{
    constexpr std::size_t operator()(graphics::vk::unique_handle<managed_type> const &handle) const noexcept
    {
      return std::hash<managed_type>{}(handle.get());
    }
};