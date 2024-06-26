#pragma once

#include <glfw_wrapper/millimetre.hpp>
#include <glfw_wrapper/version_3_4/coordinates.hpp>
#include <glfw_wrapper/version_3_4/library.hpp>
#include <glfw_wrapper/version_3_4/scale.hpp>
#include <glfw_wrapper/version_3_4/video_mode.hpp>
#include <glfw_wrapper/version_3_4/workarea.hpp>

#include <functional>
#include <optional>
#include <span>
#include <string>
#include <vector>

typedef struct GLFWmonitor GLFWmonitor;

namespace glfw
{
inline namespace version_3_4
{
class monitor
{
  public:
    [[nodiscard]]
    GLFWmonitor * get() const noexcept;

    [[nodiscard]]
    coordinates<int> get_position() const noexcept;

    [[nodiscard]]
    workarea<int> get_workarea() const noexcept;

    [[nodiscard]]
    extent<millimetre> get_physical_size() const noexcept;

    [[nodiscard]]
    scale<float> get_content_scale() const noexcept;

    [[nodiscard]]
    std::string get_name() const noexcept;

    [[nodiscard]]
    std::vector<video_mode> get_video_modes() const noexcept;

    [[nodiscard]]
    std::optional<video_mode> get_video_mode() const noexcept;

    [[nodiscard]]
    std::vector<channel<unsigned short>> get_gamma_ramp() const noexcept;

    void set_gamma(float const gamma) noexcept;

    void set_gamma_ramp(std::span<channel<unsigned short>> const ramp);

    void reset() noexcept;

    monitor() noexcept = default;

    monitor(nullhandle_t) noexcept;

    monitor(monitor && other) noexcept;

    monitor(monitor const &) noexcept = delete;

    monitor & operator=(nullhandle_t) noexcept;

    monitor & operator=(monitor && other) noexcept;

    monitor & operator=(monitor const &) noexcept = delete;

    ~monitor() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(monitor const & other) const noexcept;

    explicit operator bool() const noexcept;

    enum struct action_type
    {
      connected,
      disconnected,
      unknown
    };

    static std::function<void(monitor, monitor::action_type const)> on_monitor_connect;

  private:
    monitor(GLFWmonitor * const monitor, library const library);

    std::optional<library> _library;
    GLFWmonitor *          _monitor = nullptr;

    friend class library;
    friend class window;
};
}
}