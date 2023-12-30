#pragma once

#include "data_types.hpp"
#include "exception.hpp"

#include <bitset>
#include <limits>
#include <memory>
#include <utility>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
struct window final
{
    using value_type = GLFWwindow *;

    inline window(dimensions const &size, std::string const &title)
    : _smart_ptr(glfwCreateWindow(to_int(size.width), to_int(size.height), title.c_str(), nullptr, nullptr))
    {
      if(not _smart_ptr)
        throw bad_handle_access();

      glfwSetWindowUserPointer(_smart_ptr.get(), this);

      glfwSetWindowCloseCallback(_smart_ptr.get(),
                                 [](auto const window)
                                 { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::should_closed, true); });

      glfwSetWindowRefreshCallback(_smart_ptr.get(),
                                   [](auto const window)
                                   { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::should_refresh, true); });

      glfwSetWindowPosCallback(_smart_ptr.get(),
                               [](auto const window, int, int)
                               { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_moved, true); });

      glfwSetWindowSizeCallback(_smart_ptr.get(),
                                [](auto const window, int, int)
                                { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_resized, true); });

      glfwSetFramebufferSizeCallback(
        _smart_ptr.get(),
        [](auto const window, int, int)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_framebuffer_resized, true); });

      glfwSetWindowContentScaleCallback(
        _smart_ptr.get(),
        [](auto const window, float, float)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_content_scale_changed, true); });

      glfwSetWindowIconifyCallback(_smart_ptr.get(),
                                   [](auto const window, int const has_iconified)
                                   {
                                     static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                       ->set_flag(has_iconified == GLFW_TRUE ? flag_index::has_iconified : flag_index::has_restored_from_iconify,
                                                  true);
                                   });

      glfwSetWindowMaximizeCallback(_smart_ptr.get(),
                                    [](auto const window, int const has_maximized)
                                    {
                                      static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                        ->set_flag(has_maximized == GLFW_TRUE ? flag_index::has_maximized : flag_index::has_restored_from_maximize,
                                                   true);
                                    });

      glfwSetWindowFocusCallback(_smart_ptr.get(),
                                 [](auto const window, int const has_gained_focus)
                                 {
                                   static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
                                     ->set_flag(has_gained_focus == GLFW_TRUE ? flag_index::has_gained_focus : flag_index::has_lost_focus, true);
                                 });
    }

    [[nodiscard]]
    constexpr auto get() const
    {
      return _smart_ptr ? _smart_ptr.get() : throw bad_handle_access();
    }

    [[nodiscard]]
    constexpr auto get_attrib(attribute attribute) const
    {
      return glfwGetWindowAttrib(get(), attribute);
    }

    [[nodiscard]]
    constexpr auto get_content_scale() const
    {
      float x = 0.f, y = 0.f;
      glfwGetWindowContentScale(get(), &x, &y);
      return scale{x, y};
    }

    [[nodiscard]]
    constexpr auto get_framebuffer_size() const
    {
      int x = 0, y = 0;
      glfwGetFramebufferSize(get(), &x, &y);
      return dimensions{static_cast<std::uint16_t>(y), static_cast<std::uint32_t>(y)};
    }

    [[nodiscard]]
    constexpr auto get_frame_size() const
    {
      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(get(), &left, &top, &right, &bottom);
      return distance{static_cast<std::uint32_t>(left),
                      static_cast<std::uint32_t>(top),
                      static_cast<std::uint32_t>(right),
                      static_cast<std::uint32_t>(bottom)};
    }

    [[nodiscard]]
    constexpr float get_opacity() const
    {
      return glfwGetWindowOpacity(get());
    }

    [[nodiscard]]
    constexpr auto get_position() const
    {
      int x = 0, y = 0;
      glfwGetWindowPos(get(), &x, &y);
      return coordinates{static_cast<std::int32_t>(y), static_cast<std::int32_t>(y)};
    }

    [[nodiscard]]
    constexpr auto get_size() const
    {
      int x = 0, y = 0;
      glfwGetWindowSize(get(), &x, &y);
      return dimensions{static_cast<std::uint32_t>(y), static_cast<std::uint32_t>(y)};
    }

    [[nodiscard]]
    constexpr bool has_content_scale_changed() const
    {
      return get_flag(flag_index::has_content_scale_changed);
    }

    [[nodiscard]]
    constexpr bool has_framebuffer_resized() const
    {
      return get_flag(flag_index::has_framebuffer_resized);
    }

    [[nodiscard]]
    constexpr bool has_gained_focus() const
    {
      return get_flag(flag_index::has_gained_focus);
    }

    [[nodiscard]]
    constexpr bool has_iconified() const
    {
      return get_flag(flag_index::has_iconified);
    }

    [[nodiscard]]
    constexpr bool has_lost_focus() const
    {
      return get_flag(flag_index::has_lost_focus);
    }

    [[nodiscard]]
    constexpr bool has_maximized() const
    {
      return get_flag(flag_index::has_maximized);
    }

    [[nodiscard]]
    constexpr bool has_moved() const
    {
      return get_flag(flag_index::has_moved);
    }

    [[nodiscard]]
    constexpr bool has_resized() const
    {
      return get_flag(flag_index::has_resized);
    }

    [[nodiscard]]
    constexpr bool has_restored_from_iconify() const
    {
      return get_flag(flag_index::has_restored_from_iconify);
    }

    [[nodiscard]]
    constexpr bool has_restored_from_maximize() const
    {
      return get_flag(flag_index::has_restored_from_maximize);
    }

    [[nodiscard]]
    constexpr bool should_close() const
    {
      return get_flag(flag_index::should_closed);
    }

    [[nodiscard]]
    constexpr bool should_refresh() const
    {
      return get_flag(flag_index::should_refresh);
    }

    constexpr bool is_closed() const noexcept
    {
      return _smart_ptr == nullptr;
    }

    constexpr void close() noexcept
    {
      _flags.reset();
      _smart_ptr.reset();
    }

    constexpr void focus()
    {
      glfwFocusWindow(get());
    }

    constexpr void hide()
    {
      glfwHideWindow(get());
    }

    constexpr void iconify()
    {
      glfwIconifyWindow(get());
    }

    constexpr void maximize()
    {
      glfwMaximizeWindow(get());
    }

    constexpr void request_attention()
    {
      glfwRequestWindowAttention(get());
    }

    constexpr void restore()
    {
      glfwRestoreWindow(get());
    }

    constexpr void show()
    {
      glfwShowWindow(get());
    }

    constexpr void set_aspect_ratio(dimensions const &ratio)
    {
      glfwSetWindowAspectRatio(get(), to_int(ratio.width), to_int(ratio.height));
    }

    constexpr void set_attrib(attribute const attribute, value const value)
    {
      glfwSetWindowAttrib(get(), attribute, value);
    }

    constexpr void set_opacity(float const opacity)
    {
      glfwSetWindowOpacity(get(), opacity);
    }

    constexpr void set_position(coordinates const &position)
    {
      glfwSetWindowPos(get(), static_cast<int>(position.x), static_cast<int>(position.y));
    }

    constexpr void set_size(dimensions const &size)
    {
      glfwSetWindowSize(get(), to_int(size.width), to_int(size.height));
    }

    constexpr void set_size_limits(dimensions const &min_size, dimensions const &max_size)
    {
      glfwSetWindowSizeLimits(get(),
                              static_cast<int>(min_size.width),
                              static_cast<int>(min_size.height),
                              static_cast<int>(max_size.width),
                              static_cast<int>(max_size.height));
    }

    constexpr void set_title(std::string const &title)
    {
      glfwSetWindowTitle(get(), title.c_str());
    }

    constexpr auto operator<=>(window const &other) const noexcept
    {
      return _smart_ptr <=> other._smart_ptr;
    }

  private:
    template <class>
    friend struct std::hash;

    enum struct flag_index : std::size_t
    {
      should_closed,
      should_refresh,
      has_moved,
      has_resized,
      has_framebuffer_resized,
      has_content_scale_changed,
      has_iconified,
      has_restored_from_iconify,
      has_maximized,
      has_restored_from_maximize,
      has_gained_focus,
      has_lost_focus
    };

    constexpr void set_flag(flag_index const index, bool value) const
    {
      _flags.set(std::to_underlying(index), value);
    }

    [[nodiscard]]
    constexpr bool get_flag(flag_index const index) const
    {
      bool const flag = _flags[std::to_underlying(index)];
      _flags.reset(std::to_underlying(index));
      return _smart_ptr ? flag : throw bad_handle_access();
    }

    [[nodiscard]]
    static constexpr int to_int(std::uint32_t const value)
    {
      return std::in_range<int>(value) ? static_cast<int>(value) : std::numeric_limits<int>::max();
    }

    std::unique_ptr<GLFWwindow, decltype([](value_type const ptr) { glfwDestroyWindow(ptr); })> _smart_ptr;
    std::bitset<12> mutable _flags;
};
}

template <>
struct std::hash<glfw::window>
{
    constexpr std::size_t operator()(glfw::window const &window) const
    {
      return std::hash<decltype(window._smart_ptr)>{}(window._smart_ptr);
    }
};
