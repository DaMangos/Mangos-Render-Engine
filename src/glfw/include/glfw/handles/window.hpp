#pragma once

#include <glfw/enums/action.hpp>
#include <glfw/enums/key.hpp>
#include <glfw/enums/mouse_button.hpp>
#include <glfw/handles/library.hpp>
#include <glfw/handles/nullhandle.hpp>
#include <glfw/structs/coordinates.hpp>
#include <glfw/structs/extent.hpp>
#include <glfw/structs/image.hpp>
#include <glfw/structs/modifiers.hpp>
#include <glfw/structs/offset.hpp>
#include <glfw/structs/scale.hpp>
#include <glfw/types/pixel.hpp>

#include <filesystem>
#include <functional>
#include <optional>
#include <span>
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace glfw
{
class window
{
  public:
    [[nodiscard]]
    GLFWwindow * get() const noexcept;

    [[nodiscard]]
    coordinates<int> get_position() const;

    [[nodiscard]]
    extent<int> get_size() const;

    [[nodiscard]]
    extent<pixel> get_framebuffer_size() const;

    [[nodiscard]]
    scale<float> get_content_scale() const;

    [[nodiscard]]
    std::string get_title() const;

    [[nodiscard]]
    std::string get_clipboard() const;

    [[nodiscard]]
    monitor get_monitor() const;

    [[nodiscard]]
    float get_opacity() const;

    [[nodiscard]]
    bool are_framebuffers_transparent() const;

    [[nodiscard]]
    bool is_closed() const noexcept;

    [[nodiscard]]
    bool is_maximized() const;

    [[nodiscard]]
    bool is_minimized() const;

    [[nodiscard]]
    bool is_restored() const;

    [[nodiscard]]
    bool is_visible() const;

    [[nodiscard]]
    bool is_cursor_hovered() const;

    [[nodiscard]]
    bool is_resizeable() const;

    [[nodiscard]]
    bool is_decorated() const;

    [[nodiscard]]
    bool is_auto_iconify() const;

    [[nodiscard]]
    bool is_floating() const;

    [[nodiscard]]
    bool is_framebuffer_transparent() const;

    [[nodiscard]]
    bool is_focus_on_show() const;

    [[nodiscard]]
    bool should_close() const;

    void close() noexcept;

    void focus();

    void hide();

    void maximize();

    void iconify();

    void request_attention();

    void reset_aspect_ratio();

    void reset_size_limits();

    void restore();

    void set_aspect_ratio(extent<int> const & aspect_ratio);

    void set_cursor(cursor const & cursor);

    void set_icon(std::span<image> const icons);

    void set_opacity(float const alpha);

    void set_position(coordinates<int> const & position);

    void set_size(extent<int> const & size);

    void set_size_limits(extent<int> const & min_size, extent<int> const & max_size);

    void set_title(std::string const & title);

    void set_clipboard(std::string const & clipboard);

    void show();

    void swap_buffers();

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

    std::function<void(window &, coordinates<int>)>                           on_position_update;
    std::function<void(window &, coordinates<int>)>                           on_size_update;
    std::function<void(window &)>                                             on_close;
    std::function<void(window &)>                                             on_refresh_required;
    std::function<void(window &, focused_state)>                              on_focus_update;
    std::function<void(window &, iconified_state)>                            on_iconify_update;
    std::function<void(window &, maximized_state)>                            on_maximize_update;
    std::function<void(window &, extent<pixel>)>                              on_framebuffer_size_update;
    std::function<void(window &, scale<float>)>                               on_content_scale_update;
    std::function<void(window &, mouse_button, action, modifiers)>            on_mouse_button_action;
    std::function<void(window &, coordinates<double>)>                        on_cursor_position_update;
    std::function<void(window &, cursor_location_state)>                      on_cursor_location_update;
    std::function<void(window &, offset<double>)>                             on_scroll_update;
    std::function<void(window &, int, key, action, modifiers)>                on_key_action;
    std::function<void(window &, unsigned int)>                               on_char_input;
    std::function<void(window &, std::vector<std::filesystem::path> const &)> on_file_drop;

  private:
    window(GLFWwindow * const window, library const library) noexcept;

    std::optional<library>                              _library;
    std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> _window;

    friend class library;
};
}
