#pragma once

#include <glfw/composites/coordinates.hpp>
#include <glfw/composites/extent.hpp>
#include <glfw/composites/image.hpp>
#include <glfw/composites/offset.hpp>
#include <glfw/composites/scale.hpp>
#include <glfw/handles/library.hpp>
#include <glfw/input/action.hpp>
#include <glfw/input/keyboard.hpp>
#include <glfw/input/modifiers.hpp>
#include <glfw/input/mouse.hpp>
#include <glfw/units/pixel.hpp>

#include <filesystem>
#include <functional>
#include <optional>
#include <span>
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace glfw
{
inline namespace version_3_4
{
class window
{
  public:
    [[nodiscard]]
    GLFWwindow * get() const noexcept;

    [[nodiscard]]
    coordinates<int> get_position() const noexcept;

    [[nodiscard]]
    extent<int> get_size() const noexcept;

    [[nodiscard]]
    extent<pixel> get_framebuffer_size() const noexcept;

    [[nodiscard]]
    scale<float> get_content_scale() const noexcept;

    [[nodiscard]]
    std::string get_title() const noexcept;

    [[nodiscard]]
    std::string get_clipboard() const noexcept;

    [[nodiscard]]
    monitor get_monitor() const noexcept;

    [[nodiscard]]
    float get_opacity() const noexcept;

    [[nodiscard]]
    bool are_framebuffers_transparent() const noexcept;

    [[nodiscard]]
    bool is_closed() const noexcept;

    [[nodiscard]]
    bool is_maximized() const noexcept;

    [[nodiscard]]
    bool is_minimized() const noexcept;

    [[nodiscard]]
    bool is_restored() const noexcept;

    [[nodiscard]]
    bool is_visible() const noexcept;

    [[nodiscard]]
    bool is_cursor_hovered() const noexcept;

    [[nodiscard]]
    bool is_resizeable() const noexcept;

    [[nodiscard]]
    bool is_decorated() const noexcept;

    [[nodiscard]]
    bool is_auto_iconify() const noexcept;

    [[nodiscard]]
    bool is_floating() const noexcept;

    [[nodiscard]]
    bool is_framebuffer_transparent() const noexcept;

    [[nodiscard]]
    bool is_focus_on_show() const noexcept;

    [[nodiscard]]
    bool should_close() const noexcept;

    void close() noexcept;

    void focus() noexcept;

    void hide() noexcept;

    void maximize() noexcept;

    void iconify() noexcept;

    void request_attention() noexcept;

    void reset_aspect_ratio() noexcept;

    void reset_icon() noexcept;

    void reset_size_limits() noexcept;

    void restore() noexcept;

    void set_aspect_ratio(extent<int> const aspect_ratio) noexcept;

    void set_icon(std::span<image> const icons) noexcept;

    void set_opacity(float const alpha) noexcept;

    void set_position(coordinates<int> const position) noexcept;

    void set_size(extent<int> const size) noexcept;

    void set_size_limits(extent<int> const min_size, extent<int> const max_size) noexcept;

    void set_title(std::string const & title) noexcept;

    void set_clipboard(std::string const & clipboard) noexcept;

    void show() noexcept;

    void swap_buffers() noexcept;

    void reset() noexcept;

    window() noexcept;

    window(nullhandle_t) noexcept;

    window(window && other) noexcept;

    window(window const &) noexcept = delete;

    window & operator=(nullhandle_t) noexcept;

    window & operator=(window && other) noexcept;

    window & operator=(window const &) noexcept = delete;

    ~window() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(window const & other) const noexcept;

    explicit operator bool() const noexcept;

    enum class focused_state
    {
      gained,
      lost
    };

    enum class iconified_state
    {
      iconified,
      restored
    };

    enum class maximized_state
    {
      maximized,
      restored
    };

    enum class cursor_location_state
    {
      entered_window,
      exited_window,
    };

    std::function<void(window &, coordinates<int> const)>                              on_position_update;
    std::function<void(window &, coordinates<int> const)>                              on_size_update;
    std::function<void(window &)>                                                      on_close;
    std::function<void(window &)>                                                      on_refresh_required;
    std::function<void(window &, focused_state const)>                                 on_focus_update;
    std::function<void(window &, iconified_state const)>                               on_iconify_update;
    std::function<void(window &, maximized_state const)>                               on_maximize_update;
    std::function<void(window &, extent<pixel> const)>                                 on_framebuffer_size_update;
    std::function<void(window &, scale<float> const)>                                  on_content_scale_update;
    std::function<void(window &, mouse_button const, action const, modifiers const)>   on_mouse_button_action;
    std::function<void(window &, coordinates<double> const)>                           on_cursor_position_update;
    std::function<void(window &, cursor_location_state const)>                         on_cursor_location_update;
    std::function<void(window &, offset<double> const)>                                on_scroll_update;
    std::function<void(window &, int const, key const, action const, modifiers const)> on_key_action;
    std::function<void(window &, unsigned int const)>                                  on_char_input;
    std::function<void(window &, std::vector<std::filesystem::path> const &)>          on_file_drop;

  private:
    window(GLFWwindow * const window, library const library) noexcept;

    std::optional<library>                              _library;
    std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> _window;

    friend class library;
};
}
}