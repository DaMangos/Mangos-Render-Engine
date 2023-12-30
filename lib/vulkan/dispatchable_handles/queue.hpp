#pragma once

#include "../non_dispatchable_handle.hpp"

namespace vulkan
{
template <class>
struct dispatchable_handle;

template <>
struct dispatchable_handle<VkQueue> final
{
    using value_type = VkQueue;

    [[nodiscard]]
    constexpr auto get() const
    {
      return _dispatcher ? _ptr : throw bad_handle_access();
    }

    constexpr explicit operator bool() const noexcept
    {
      return static_cast<bool>(_ptr);
    }

    auto operator<=>(dispatchable_handle const &other) const    = default;
    dispatchable_handle(dispatchable_handle &&)                 = default;
    dispatchable_handle(dispatchable_handle const &)            = delete;
    dispatchable_handle &operator=(dispatchable_handle &&)      = default;
    dispatchable_handle &operator=(dispatchable_handle const &) = delete;
    ~dispatchable_handle()                                      = default;

  private:
    friend struct dispatchable_handle<VkDevice>;

    dispatchable_handle(std::shared_ptr<std::pointer_traits<VkDevice>::element_type> const &dispatcher, auto &&info)
    : _dispatcher(dispatcher),
      _ptr(
        [&dispatcher, &info]()
        {
          value_type ptr;
          auto const result = vkGetDeviceQueue2(dispatcher.get(), std::forward<decltype(info)>(info), &ptr);
          return std::to_underlying(result) >= 0 ? ptr : throw bad_result(result);
        }())
    {
    }

    std::shared_ptr<std::pointer_traits<VkDevice>::element_type> _dispatcher;
    value_type                                                   _ptr;
};

using queue = dispatchable_handle<VkQueue>;
}