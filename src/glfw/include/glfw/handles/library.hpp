#pragma once

#include <glfw/enums/key.hpp>
#include <glfw/enums/platform.hpp>
#include <glfw/enums/printable_key.hpp>
#include <glfw/structs/coordinates.hpp>
#include <glfw/structs/extent.hpp>
#include <glfw/structs/image.hpp>
#include <glfw/structs/library_hints.hpp>
#include <glfw/structs/version.hpp>
#include <glfw/structs/window_hints.hpp>
#include <glfw/types/pixel.hpp>

#include <compare>
#include <vector>

namespace glfw
{
class cursor;
class window;
class monitor;

class library
{
  public:
    [[nodiscard]]
    long use_count() const noexcept;

    [[nodiscard]]
    cursor create_cursor(image image, coordinates<pixel> const & hotspot) const;

    [[nodiscard]]
    cursor create_standard_arrow_cursor() const;

    [[nodiscard]]
    cursor create_standard_i_beam_cursor() const;

    [[nodiscard]]
    cursor create_standard_crosshair_cursor() const;

    [[nodiscard]]
    cursor create_standard_hand_cursor() const;

    [[nodiscard]]
    cursor create_standard_horizontal_resize_cursor() const;

    [[nodiscard]]
    cursor create_standard_vertical_resize_cursor() const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window const & share) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor, window const & share) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window_hints const & hints) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor, window_hints const & hints) const;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window const & share, window_hints const & hints) const;

    [[nodiscard]]
    window create_window(extent<int> const &  size,
                         std::string const &  title,
                         monitor const &      monitor,
                         window const &       share,
                         window_hints const & hints) const;

    window get_current_context() const;

    [[nodiscard]]
    monitor get_primary_monitor() const;

    [[nodiscard]]
    std::vector<monitor> get_monitors() const;

    [[nodiscard]]
    version get_version();

    [[nodiscard]]
    static std::string get_version_string();

    [[nodiscard]]
    platform get_platform() const;

    [[nodiscard]]
    static bool is_platform_supported(platform const platform);

    [[nodiscard]]
    bool is_raw_mouse_motion_supported() const;

    [[nodiscard]]
    bool is_extension_supported(std::string const & extension) const;

    [[nodiscard]]
    bool is_vulkan_supported() const;

    [[nodiscard]]
    std::vector<std::string> get_required_instance_extensions() const;

    [[nodiscard]]
    int get_key_scancode(key const key) const;

    [[nodiscard]]
    std::string get_key_name(int const scancode) const;

    [[nodiscard]]
    std::string get_key_name(printable_key const printable_key) const;

    void swap_interval(int const interval) const;

    void poll_events() const;

    void wait_events() const;

    void wait_events_timeout(double const timeout) const;

    void post_empty_event() const;

    library();

    library(struct library_hints const & hints);

    library(library &&) noexcept;

    library(library const &) noexcept;

    library & operator=(library &&) noexcept;

    library & operator=(library const &) noexcept;

    ~library() noexcept;

    constexpr std::strong_ordering operator<=>(library const & other) const noexcept = default;
};
}
