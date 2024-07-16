#pragma once

namespace glfw
{
class exception
{
  public:
    [[nodiscard]]
    virtual char const * what() const noexcept;

    exception() noexcept;

    exception(exception &&) noexcept = default;

    exception(exception const &) noexcept = default;

    exception & operator=(exception &&) noexcept = default;

    exception & operator=(exception const &) noexcept = default;

    virtual ~exception() noexcept = default;

  private:
    char const * _what_message;
};
}
