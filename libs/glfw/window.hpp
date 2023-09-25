#pragma once

#include "data_types.hpp"
#include "GLFW/glfw3.h"

#include <bitset>
#include <memory>

namespace glfw
{
struct monitor;

struct window
{
    void close() noexcept;

    void focus() noexcept;

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
    monitor get_monitor() const;

    [[nodiscard]]
    float get_opacity() const noexcept;

    [[nodiscard]]
    coordinates get_position() const noexcept;

    [[nodiscard]]
    dimensions get_size() const noexcept;

    [[nodiscard]]
    bool has_content_scale_changed() noexcept;

    [[nodiscard]]
    bool has_framebuffer_resized() noexcept;

    [[nodiscard]]
    bool has_gained_focus() noexcept;

    [[nodiscard]]
    bool has_iconified() noexcept;

    [[nodiscard]]
    bool has_lost_focus() noexcept;

    [[nodiscard]]
    bool has_maximized() noexcept;

    [[nodiscard]]
    bool has_moved() noexcept;

    [[nodiscard]]
    bool has_resized() noexcept;

    [[nodiscard]]
    bool has_restored_from_iconify() noexcept;

    [[nodiscard]]
    bool has_restored_from_maximizes() noexcept;

    void hide() noexcept;

    void iconify() noexcept;

    void maximize() noexcept;

    void request_attention() noexcept;

    void restore() noexcept;

    void set_aspect_ratio(dimensions ratio) noexcept;

    void set_attrib(attribute attribute, value value) noexcept;

    void set_icon(std::vector<GLFWimage> images);

    void set_monitor(GLFWmonitor *monitor, coordinates position, dimensions size, int refreshRate) noexcept;

    void set_opacity(float opacity) noexcept;

    void set_position(coordinates position) noexcept;

    void set_size(dimensions size) noexcept;

    void set_size_limits(dimensions min_size, dimensions max_size) noexcept;

    void set_title(std::string const &title) noexcept;

    bool should_close() noexcept;

    [[nodiscard]]
    bool should_refresh() noexcept;

    void show() noexcept;

  private:
    window(GLFWwindow *&&window) noexcept;

    std::unique_ptr<GLFWwindow, decltype([](GLFWwindow *window) { glfwDestroyWindow(window); })> window_;
    std::bitset<12>                                                                              flags_;
};
}
