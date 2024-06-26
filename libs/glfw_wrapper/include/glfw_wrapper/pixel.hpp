#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class pixel : int
{
};

[[nodiscard]]
constexpr pixel to_pixel(int const value) noexcept
{
  return static_cast<pixel>(value);
}

[[nodiscard]]
constexpr int to_int(pixel const value) noexcept
{
  return static_cast<int>(value);
}

inline namespace literals
{
inline namespace pixel_literals
{
constexpr pixel operator"" _px(unsigned long long const value) noexcept
{
  return static_cast<pixel>(value);
}
}
}
}

constexpr std::strong_ordering operator<=>(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_int(lhs) <=> glfw::to_int(rhs);
}

constexpr glfw::pixel operator+(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_pixel(glfw::to_int(lhs) + glfw::to_int(rhs));
}

constexpr glfw::pixel operator-(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_pixel(glfw::to_int(lhs) - glfw::to_int(rhs));
}

constexpr glfw::pixel operator*(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_pixel(glfw::to_int(lhs) * glfw::to_int(rhs));
}

constexpr glfw::pixel operator/(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_pixel(glfw::to_int(lhs) / glfw::to_int(rhs));
}

constexpr glfw::pixel operator%(glfw::pixel const lhs, glfw::pixel const rhs) noexcept
{
  return glfw::to_pixel(glfw::to_int(lhs) % glfw::to_int(rhs));
}

constexpr glfw::pixel & operator+=(glfw::pixel & lhs, glfw::pixel const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr glfw::pixel & operator-=(glfw::pixel & lhs, glfw::pixel const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr glfw::pixel & operator*=(glfw::pixel & lhs, glfw::pixel const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr glfw::pixel & operator/=(glfw::pixel & lhs, glfw::pixel const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr glfw::pixel & operator%=(glfw::pixel & lhs, glfw::pixel const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr int operator+(glfw::pixel const value) noexcept
{
  return glfw::to_int(value);
}

constexpr glfw::pixel operator-(glfw::pixel const value) noexcept
{
  return glfw::to_pixel(-glfw::to_int(value));
}

constexpr glfw::pixel & operator++(glfw::pixel & value) noexcept
{
  using namespace glfw::pixel_literals;
  return value += 1_px;
}

constexpr glfw::pixel operator++(glfw::pixel & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr glfw::pixel & operator--(glfw::pixel & value) noexcept
{
  using namespace glfw::pixel_literals;
  return value -= 1_px;
}

constexpr glfw::pixel operator--(glfw::pixel & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <>
struct std::hash<glfw::pixel>
{
    std::size_t operator()(glfw::pixel const value) const noexcept
    {
      return std::hash<int>{}(glfw::to_int(value));
    }
};

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, glfw::pixel const value)
{
  return os << glfw::to_int(value) << "px";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, glfw::pixel & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'p' and is.get() == 'x')
    value = glfw::to_pixel(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
