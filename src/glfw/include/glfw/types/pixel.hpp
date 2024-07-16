#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class pixel : int
{
};

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

constexpr std::strong_ordering operator<=>(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<int>(lhs) <=> static_cast<int>(rhs);
}

constexpr pixel operator+(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<pixel>(static_cast<int>(lhs) + static_cast<int>(rhs));
}

constexpr pixel operator-(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<pixel>(static_cast<int>(lhs) - static_cast<int>(rhs));
}

constexpr pixel operator*(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<pixel>(static_cast<int>(lhs) * static_cast<int>(rhs));
}

constexpr pixel operator/(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<pixel>(static_cast<int>(lhs) / static_cast<int>(rhs));
}

constexpr pixel operator%(pixel const lhs, pixel const rhs) noexcept
{
  return static_cast<pixel>(static_cast<int>(lhs) % static_cast<int>(rhs));
}

constexpr pixel & operator+=(pixel & lhs, pixel const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr pixel & operator-=(pixel & lhs, pixel const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr pixel & operator*=(pixel & lhs, pixel const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr pixel & operator/=(pixel & lhs, pixel const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr pixel & operator%=(pixel & lhs, pixel const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr pixel operator-(pixel const value) noexcept
{
  return static_cast<pixel>(-static_cast<int>(value));
}

constexpr pixel & operator++(pixel & value) noexcept
{
  using namespace pixel_literals;
  return value += 1_px;
}

constexpr pixel operator++(pixel & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr pixel & operator--(pixel & value) noexcept
{
  using namespace pixel_literals;
  return value -= 1_px;
}

constexpr pixel operator--(pixel & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, pixel const value)
{
  return os << static_cast<int>(value) << "px";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, pixel & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'p' and is.get() == 'x')
    value = static_cast<pixel>(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
}

template <>
struct std::hash<glfw::pixel>
{
    std::size_t operator()(glfw::pixel const value) const noexcept
    {
      return std::hash<int>{}(static_cast<int>(value));
    }
};