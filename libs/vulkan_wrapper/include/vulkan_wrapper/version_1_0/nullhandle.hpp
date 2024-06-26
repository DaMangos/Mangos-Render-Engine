#pragma once

#include <compare>

namespace vulkan
{
struct nullhandle_t final
{
    constexpr explicit nullhandle_t(int) noexcept
    {
    }

    constexpr std::strong_ordering operator<=>(nullhandle_t) noexcept
    {
      return std::strong_ordering::equal;
    }
};

inline constexpr auto nullhandle = nullhandle_t(0);
}
