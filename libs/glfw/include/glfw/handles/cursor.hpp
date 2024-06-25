#pragma once

#include <glfw/handles/library.hpp>

#include <memory>

typedef struct GLFWcursor GLFWcursor;

namespace glfw
{
inline namespace version_3_4
{
class cursor
{
  public:
    GLFWcursor * get() const noexcept;

    void reset() noexcept;

    cursor() noexcept;

    cursor(nullhandle_t) noexcept;

    cursor(cursor &&) noexcept = default;

    cursor(cursor const &) noexcept = delete;

    cursor & operator=(nullhandle_t) noexcept;

    cursor & operator=(cursor &&) noexcept = default;

    cursor & operator=(cursor const &) noexcept = delete;

    ~cursor() noexcept = default;

    std::strong_ordering operator<=>(nullhandle_t) const noexcept;

    std::strong_ordering operator<=>(cursor const & other) const noexcept;

    explicit operator bool() const noexcept;

  private:
    std::optional<library>                              _library;
    std::unique_ptr<GLFWcursor, void (*)(GLFWcursor *)> _cursor;
};
}
}