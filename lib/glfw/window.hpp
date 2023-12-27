#pragma once

#include "data_types.hpp"

#include <bitset>
#include <limits>
#include <memory>
#include <source_location>
#include <utility>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
struct window final
{
    using element_type = GLFWwindow;
    using pointer      = GLFWwindow *;

    constexpr window(dimensions const &size, std::string const &title)
    : _handle(glfwCreateWindow(to_int(size.width), to_int(size.height), title.c_str(), nullptr, nullptr))
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to create a window");

      glfwSetWindowUserPointer(_handle.get(), this);

      glfwSetWindowCloseCallback(
        _handle.get(),
        [](GLFWwindow *window)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::should_closed, true); });

      glfwSetWindowRefreshCallback(
        _handle.get(),
        [](GLFWwindow *window)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::should_refresh, true); });

      glfwSetWindowPosCallback(
        _handle.get(),
        [](GLFWwindow *const window, int const, int const)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_moved, true); });

      glfwSetWindowSizeCallback(
        _handle.get(),
        [](GLFWwindow *const window, int const, int const)
        { static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_resized, true); });

      glfwSetFramebufferSizeCallback(
        _handle.get(),
        [](GLFWwindow *const window, int const, int const) {
          static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_framebuffer_resized, true);
        });

      glfwSetWindowContentScaleCallback(
        _handle.get(),
        [](GLFWwindow *const window, float const, float const) {
          static_cast<decltype(this)>(glfwGetWindowUserPointer(window))->set_flag(flag_index::has_content_scale_changed, true);
        });

      glfwSetWindowIconifyCallback(
        _handle.get(),
        [](GLFWwindow *window, int has_iconified)
        {
          static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
            ->set_flag(has_iconified == GLFW_TRUE ? flag_index::has_iconified : flag_index::has_restored_from_iconify, true);
        });

      glfwSetWindowMaximizeCallback(
        _handle.get(),
        [](GLFWwindow *const window, int const has_maximized)
        {
          static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
            ->set_flag(has_maximized == GLFW_TRUE ? flag_index::has_maximized : flag_index::has_restored_from_maximize, true);
        });

      glfwSetWindowFocusCallback(
        _handle.get(),
        [](GLFWwindow *const window, int const has_gained_focus)
        {
          static_cast<decltype(this)>(glfwGetWindowUserPointer(window))
            ->set_flag(has_gained_focus == GLFW_TRUE ? flag_index::has_gained_focus : flag_index::has_lost_focus, true);
        });
    }

    [[nodiscard]]
    constexpr GLFWwindow *get() noexcept
    {
      return _handle.get();
    }

    [[nodiscard]]
    constexpr attribute get_attrib(attribute attribute) const noexcept
    {
      return glfwGetWindowAttrib(_handle.get(), attribute);
    }

    [[nodiscard]]
    constexpr scale get_content_scale() const noexcept
    {
      float x = 0.f, y = 0.f;
      glfwGetWindowContentScale(_handle.get(), &x, &y);
      return scale{x, y};
    }

    [[nodiscard]]
    constexpr dimensions get_framebuffer_size() const noexcept
    {
      int x = 0, y = 0;
      glfwGetFramebufferSize(_handle.get(), &x, &y);
      return dimensions{static_cast<std::uint16_t>(y), static_cast<std::uint32_t>(y)};
    }

    [[nodiscard]]
    constexpr distance get_frame_size() const noexcept
    {
      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(_handle.get(), &left, &top, &right, &bottom);
      return distance{static_cast<std::uint32_t>(left),
                      static_cast<std::uint32_t>(top),
                      static_cast<std::uint32_t>(right),
                      static_cast<std::uint32_t>(bottom)};
    }

    [[nodiscard]]
    constexpr float get_opacity() const noexcept
    {
      return glfwGetWindowOpacity(_handle.get());
    }

    [[nodiscard]]
    constexpr coordinates get_position() const noexcept
    {
      int x = 0, y = 0;
      glfwGetWindowPos(_handle.get(), &x, &y);
      return coordinates{static_cast<std::int32_t>(y), static_cast<std::int32_t>(y)};
    }

    [[nodiscard]]
    constexpr dimensions get_size() const noexcept
    {
      int x = 0, y = 0;
      glfwGetWindowSize(_handle.get(), &x, &y);
      return dimensions{static_cast<std::uint32_t>(y), static_cast<std::uint32_t>(y)};
    }

    [[nodiscard]]
    constexpr bool has_content_scale_changed() const noexcept
    {
      return get_flag(flag_index::has_content_scale_changed);
    }

    [[nodiscard]]
    constexpr bool has_framebuffer_resized() const noexcept
    {
      return get_flag(flag_index::has_framebuffer_resized);
    }

    [[nodiscard]]
    constexpr bool has_gained_focus() const noexcept
    {
      return get_flag(flag_index::has_gained_focus);
    }

    [[nodiscard]]
    constexpr bool has_iconified() const noexcept
    {
      return get_flag(flag_index::has_iconified);
    }

    [[nodiscard]]
    constexpr bool has_lost_focus() const noexcept
    {
      return get_flag(flag_index::has_lost_focus);
    }

    [[nodiscard]]
    constexpr bool has_maximized() const noexcept
    {
      return get_flag(flag_index::has_maximized);
    }

    [[nodiscard]]
    constexpr bool has_moved() const noexcept
    {
      return get_flag(flag_index::has_moved);
    }

    [[nodiscard]]
    constexpr bool has_resized() const noexcept
    {
      return get_flag(flag_index::has_resized);
    }

    [[nodiscard]]
    constexpr bool has_restored_from_iconify() const noexcept
    {
      return get_flag(flag_index::has_restored_from_iconify);
    }

    [[nodiscard]]
    constexpr bool has_restored_from_maximize() const noexcept
    {
      return get_flag(flag_index::has_restored_from_maximize);
    }

    [[nodiscard]]
    constexpr bool should_close() const noexcept
    {
      return get_flag(flag_index::should_closed);
    }

    [[nodiscard]]
    constexpr bool should_refresh() const noexcept
    {
      return get_flag(flag_index::should_refresh);
    }

    constexpr bool is_closed() const noexcept
    {
      return _handle == nullptr;
    }

    constexpr void close() noexcept
    {
      _flags.reset();
      _handle.reset();
    }

    constexpr void focus()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to focus window");
      glfwFocusWindow(_handle.get());
    }

    constexpr void hide()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to hide window");
      glfwHideWindow(_handle.get());
    }

    constexpr void iconify()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to iconify window");
      glfwIconifyWindow(_handle.get());
    }

    constexpr void maximize()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to maximize window");
      glfwMaximizeWindow(_handle.get());
    }

    constexpr void request_attention()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to request window attention");
      glfwRequestWindowAttention(_handle.get());
    }

    constexpr void restore()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to restore window");
      glfwRestoreWindow(_handle.get());
    }

    constexpr void show()
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to show window");
      glfwShowWindow(_handle.get());
    }

    constexpr void set_aspect_ratio(dimensions const &ratio)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window aspect ratio");
      glfwSetWindowAspectRatio(_handle.get(), to_int(ratio.width), to_int(ratio.height));
    }

    constexpr void set_attrib(attribute const attribute, value const value)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window attribute");
      glfwSetWindowAttrib(_handle.get(), attribute, value);
    }

    constexpr void set_opacity(float const opacity)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window opacity");
      glfwSetWindowOpacity(_handle.get(), opacity);
    }

    constexpr void set_position(coordinates const &position)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window position");
      glfwSetWindowPos(_handle.get(), static_cast<int>(position.x), static_cast<int>(position.y));
    }

    constexpr void set_size(dimensions const &size)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window size");
      glfwSetWindowSize(_handle.get(), to_int(size.width), to_int(size.height));
    }

    constexpr void set_size_limits(dimensions const &min_size, dimensions const &max_size)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window size limits");
      glfwSetWindowSizeLimits(_handle.get(),
                              static_cast<int>(min_size.width),
                              static_cast<int>(min_size.height),
                              static_cast<int>(max_size.width),
                              static_cast<int>(max_size.height));
    }

    constexpr void set_title(std::string const &title)
    {
      if(is_closed())
        throw std::runtime_error(std::string(std::source_location::current().function_name()) +
                                 ":\033[1;31m error:\033[0m glfw failed to set window title");
      glfwSetWindowTitle(_handle.get(), title.c_str());
    }

    constexpr bool operator==(window const &other) const noexcept
    {
      return _handle == other._handle;
    }

    constexpr bool operator!=(window const &other) const noexcept
    {
      return _handle != other._handle;
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

    constexpr void set_flag(flag_index const index, bool value) const noexcept
    {
      _flags.set(std::to_underlying(index), value);
    }

    [[nodiscard]]
    constexpr bool get_flag(flag_index const index) const noexcept
    {
      bool const flag = _flags[std::to_underlying(index)];
      _flags.reset(std::to_underlying(index));
      return flag;
    }

    [[nodiscard]]
    static constexpr int to_int(std::uint32_t const value) noexcept
    {
      return std::in_range<int>(value) ? static_cast<int>(value) : std::numeric_limits<int>::max();
    }

    std::unique_ptr<GLFWwindow, decltype([](GLFWwindow *const ptr) { glfwDestroyWindow(ptr); })> _handle;
    std::bitset<12> mutable _flags;
};
}

template <>
struct std::hash<glfw::window>
{
    constexpr std::size_t operator()(glfw::window const &window) const noexcept
    {
      return std::hash<decltype(window._handle)>{}(window._handle);
    }
};
