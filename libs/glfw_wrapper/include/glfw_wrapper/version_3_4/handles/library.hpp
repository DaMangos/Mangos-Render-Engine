#pragma once

#include <glfw_wrapper/structs/version.hpp>
#include <glfw_wrapper/types/pixel.hpp>
#include <glfw_wrapper/version_3_4/enums/error_code.hpp>
#include <glfw_wrapper/version_3_4/enums/key.hpp>
#include <glfw_wrapper/version_3_4/enums/platform.hpp>
#include <glfw_wrapper/version_3_4/structs/coordinates.hpp>
#include <glfw_wrapper/version_3_4/structs/extent.hpp>
#include <glfw_wrapper/version_3_4/structs/image.hpp>
#include <glfw_wrapper/version_3_4/structs/library_hints.hpp>
#include <glfw_wrapper/version_3_4/structs/window_hints.hpp>

#include <compare>
#include <string>
#include <vector>

typedef struct VkPhysicalDevice_T * VkPhysicalDevice;
typedef struct VkInstance_T *       VkInstance;

namespace glfw
{
inline namespace version_3_4
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

    window get_current_context() const noexcept;

    [[nodiscard]]
    monitor get_primary_monitor() const noexcept;

    [[nodiscard]]
    std::vector<monitor> get_monitors() const noexcept;

    [[nodiscard]]
    static version get_version() noexcept;

    [[nodiscard]]
    static std::string get_version_string() noexcept;

    [[nodiscard]]
    static std::pair<error_code, std::string> get_last_error() noexcept;

    [[nodiscard]]
    platform get_platform() const noexcept;

    [[nodiscard]]
    static bool is_platform_supported(platform const platform) noexcept;

    [[nodiscard]]
    bool is_raw_mouse_motion_supported() const noexcept;

    [[nodiscard]]
    bool is_extension_supported(std::string const & extension) const noexcept;

    [[nodiscard]]
    bool is_vulkan_supported() const noexcept;

    [[nodiscard]]
    std::vector<std::string> get_required_instance_extensions() const noexcept;

    [[nodiscard]]
    int get_key_scancode(key const key) const noexcept;

    [[nodiscard]]
    std::string get_key_name(key const key, int const scancode) const noexcept;

    void swap_interval(int const interval) const noexcept;

    void poll_events() const noexcept;

    void wait_events() const noexcept;

    void wait_events_timeout(double const timeout) const noexcept;

    void post_empty_event() const noexcept;

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