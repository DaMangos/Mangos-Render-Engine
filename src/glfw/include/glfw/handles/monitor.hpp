#pragma once

#include <glfw/handles/library.hpp>
#include <glfw/handles/nullhandle.hpp>
#include <glfw/structs/channel.hpp>
#include <glfw/structs/coordinates.hpp>
#include <glfw/structs/scale.hpp>
#include <glfw/structs/video_mode.hpp>
#include <glfw/structs/workarea.hpp>
#include <glfw/types/millimetre.hpp>

#include <functional>
#include <optional>
#include <span>
#include <string>
#include <vector>

typedef struct GLFWmonitor GLFWmonitor;

namespace glfw
{

class monitor
{
  public:
    [[nodiscard]]
    GLFWmonitor * get() const noexcept;

    [[nodiscard]]
    coordinates<int> get_position() const;

    [[nodiscard]]
    workarea<int> get_workarea() const;

    [[nodiscard]]
    extent<millimetre> get_physical_size() const;

    [[nodiscard]]
    scale<float> get_content_scale() const;

    [[nodiscard]]
    std::string get_name() const;

    [[nodiscard]]
    std::vector<video_mode> get_video_modes() const;

    [[nodiscard]]
    std::optional<video_mode> get_video_mode() const;

    [[nodiscard]]
    std::vector<channel<unsigned short>> get_gamma_ramp() const;

    void set_gamma(float const gamma);

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
