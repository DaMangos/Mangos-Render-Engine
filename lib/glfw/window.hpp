#pragma once

#include "data_types.hpp"

#include <bitset>
#include <memory>

#define VK_ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace glfw
{
struct window
{
    window(dimensions const &size, std::string const &title);

    [[nodiscard]]
    constexpr GLFWwindow *get() const noexcept
    {
      return _handle.get();
    }

    [[nodiscard]]
    attribute get_attrib(attribute const attribute) const noexcept;

    [[nodiscard]]
    scale get_content_scale() const noexcept;

    [[nodiscard]]
    dimensions get_framebuffer_size() const noexcept;

    [[nodiscard]]
    distance get_frame_size() const noexcept;

    [[nodiscard]]
    float get_opacity() const noexcept;

    [[nodiscard]]
    coordinates get_position() const noexcept;

    [[nodiscard]]
    dimensions get_size() const noexcept;

    [[nodiscard]]
    bool has_content_scale_changed() const noexcept;

    [[nodiscard]]
    bool has_framebuffer_resized() const noexcept;

    [[nodiscard]]
    bool has_gained_focus() const noexcept;

    [[nodiscard]]
    bool has_iconified() const noexcept;

    [[nodiscard]]
    bool has_lost_focus() const noexcept;

    [[nodiscard]]
    bool has_maximized() const noexcept;

    [[nodiscard]]
    bool has_moved() const noexcept;

    [[nodiscard]]
    bool has_resized() const noexcept;

    [[nodiscard]]
    bool has_restored_from_iconify() const noexcept;

    [[nodiscard]]
    bool has_restored_from_maximize() const noexcept;

    [[nodiscard]]
    bool should_close() const noexcept;

    [[nodiscard]]
    bool should_refresh() const noexcept;

    void close() noexcept;

    void focus() noexcept;

    void hide() noexcept;

    void iconify() noexcept;

    void maximize() noexcept;

    void request_attention() noexcept;

    void restore() noexcept;

    void show() noexcept;

    void set_aspect_ratio(dimensions const &ratio) noexcept;

    void set_attrib(attribute const attribute, value const value) noexcept;

    void set_icon(std::ranges::contiguous_range auto const &images)
      requires std::same_as<std::ranges::range_value_t<decltype(images)>, GLFWimage>
    {
      if(std::ranges::size(images) > std::numeric_limits<int>::max())
        throw std::out_of_range("failed to set icon: too many GLFWimage");
      glfwSetWindowIcon(get(), static_cast<int>(std::ranges::size(images)), std::ranges::data(images));
    }

    void set_opacity(float const opacity) noexcept;

    void set_position(coordinates const &position) noexcept;

    void set_size(dimensions const &size) noexcept;

    void set_size_limits(dimensions const &min_size, dimensions const &max_size) noexcept;

    void set_title(std::string const &title) noexcept;

    void set_title(std::nullptr_t) = delete;

  private:
    std::unique_ptr<GLFWwindow, decltype([](GLFWwindow *ptr) { glfwDestroyWindow(ptr); })> _handle;
    std::bitset<12> mutable _flags;
};
}
