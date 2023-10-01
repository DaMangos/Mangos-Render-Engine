#pragma once

#include "data_types.hpp"
#include "GLFW/glfw3.h"

#include <bitset>
#include <memory>

namespace glfw
{
struct window
{
    window(dimensions size, std::string const &title);

    [[nodiscard]]
    GLFWwindow *get() const noexcept;

    [[nodiscard]]
    attribute get_attrib(attribute attribute) const noexcept;

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

    void set_aspect_ratio(dimensions ratio) noexcept;

    void set_attrib(attribute attribute, value value) noexcept;

    void set_icon(std::vector<GLFWimage> images);

    void set_opacity(float opacity) noexcept;

    void set_position(coordinates position) noexcept;

    void set_size(dimensions size) noexcept;

    void set_size_limits(dimensions min_size, dimensions max_size) noexcept;

    void set_title(std::string const &title) noexcept;

  private:
    std::unique_ptr<GLFWwindow, decltype([](GLFWwindow *ptr) { glfwDestroyWindow(ptr); })> _handle;
    std::bitset<12> mutable _flags;
};
}
