#pragma once

#include <glfw_wrapper/composites/extent.hpp>
#include <glfw_wrapper/handles/hints/library_hints.hpp>
#include <glfw_wrapper/handles/hints/window_hints.hpp>
#include <glfw_wrapper/handles/nullhandle.hpp>

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

    window create_window(extent<int> const size, std::string const & title) const noexcept;

    window create_window(extent<int> const size, std::string const & title, monitor const & monitor) const noexcept;

    window create_window(extent<int> const size, std::string const & title, window const & share) const noexcept;

    window create_window(extent<int> const size, std::string const & title, monitor const & monitor, window const & share) const noexcept;

    window create_window(extent<int> const size, std::string const & title, window_hints const & hints) const noexcept;

    window create_window(extent<int> const size, std::string const & title, monitor const & monitor, window_hints const & hints) const noexcept;

    window create_window(extent<int> const size, std::string const & title, window const & share, window_hints const & hints) const noexcept;

    window create_window(extent<int> const    size,
                         std::string const &  title,
                         monitor const &      monitor,
                         window const &       share,
                         window_hints const & hints) const noexcept;

    monitor get_primary_monitor() const noexcept;

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