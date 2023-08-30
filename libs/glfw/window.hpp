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

    GLFWwindow *get() const noexcept;

    attribute get_attrib(attribute attribute) const noexcept;

    scale get_content_scale() const noexcept;

    dimensions get_framebuffer_size() const noexcept;

    distance get_frame_size() const noexcept;

    monitor get_monitor() const;

    float get_opacity() const noexcept;

    coordinates get_position() const noexcept;

    dimensions get_size() const noexcept;

    bool has_content_scale_changed() noexcept;

    bool has_framebuffer_resized() noexcept;

    bool has_gained_focus() noexcept;

    bool has_iconified() noexcept;

    bool has_lost_focus() noexcept;

    bool has_maximized() noexcept;

    bool has_moved() noexcept;

    bool has_resized() noexcept;

    bool has_restored_from_iconify() noexcept;

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

    bool should_refresh() noexcept;

    void show() noexcept;

  private:
    window(GLFWwindow *&&window) noexcept;

    std::unique_ptr<GLFWwindow, decltype([](GLFWwindow *window) { glfwDestroyWindow(window); })> _window;
    std::bitset<12>                                                                              _flags;
};
}
