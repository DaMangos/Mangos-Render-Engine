#pragma once

#include <glfw_wrapper/pixel.hpp>
#include <glfw_wrapper/version_3_4/coordinates.hpp>
#include <glfw_wrapper/version_3_4/extent.hpp>
#include <glfw_wrapper/version_3_4/image.hpp>
#include <glfw_wrapper/version_3_4/library_hints.hpp>
#include <glfw_wrapper/version_3_4/nullhandle.hpp>
#include <glfw_wrapper/version_3_4/window_hints.hpp>

#include <compare>
#include <string>
#include <vector>

namespace glfw
{
inline namespace version_3_4
{
class window;
class monitor;
class cursor;

class library
{
  public:
    [[nodiscard]]
    long use_count() const noexcept;

    void reset() noexcept;

    [[nodiscard]]
    cursor create_cursor(image image, coordinates<pixel> const & hotspot) const noexcept;

    [[nodiscard]]
    cursor create_standard_arrow_cursor() const noexcept;

    [[nodiscard]]
    cursor create_standard_i_beam_cursor() const noexcept;

    [[nodiscard]]
    cursor create_standard_crosshair_cursor() const noexcept;

    [[nodiscard]]
    cursor create_standard_hand_cursor() const noexcept;

    [[nodiscard]]
    cursor create_standard_horizontal_resize_cursor() const noexcept;

    [[nodiscard]]
    cursor create_standard_vertical_resize_cursor() const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window const & share) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor, window const & share) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window_hints const & hints) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, monitor const & monitor, window_hints const & hints) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const & size, std::string const & title, window const & share, window_hints const & hints) const noexcept;

    [[nodiscard]]
    window create_window(extent<int> const &  size,
                         std::string const &  title,
                         monitor const &      monitor,
                         window const &       share,
                         window_hints const & hints) const noexcept;

    [[nodiscard]]
    monitor get_primary_monitor() const noexcept;

    [[nodiscard]]
    std::vector<monitor> get_monitors() const noexcept;

    library() noexcept;

    library(struct library_hints const & hints) noexcept;

    library(library &&) noexcept;

    library(library const &) noexcept;

    library & operator=(library &&) noexcept;

    library & operator=(library const &) noexcept;

    ~library() noexcept;

    constexpr std::strong_ordering operator<=>(library const & other) const noexcept = default;
};
}
}