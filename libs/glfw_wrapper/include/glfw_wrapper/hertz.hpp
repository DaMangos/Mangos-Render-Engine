#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class hertz : int
{
};

[[nodiscard]]
constexpr hertz to_hertz(int const value) noexcept
{
  return static_cast<hertz>(value);
}

[[nodiscard]]
constexpr int to_int(hertz const value) noexcept
{
  return static_cast<int>(value);
}

inline namespace literals
{
inline namespace hertz_literals
{
constexpr hertz operator"" _hz(unsigned long long const value) noexcept
{
  return static_cast<hertz>(value);
}

constexpr hertz operator"" _khz(unsigned long long const value) noexcept
{
  return static_cast<hertz>(value * 1'000);
}

constexpr hertz operator"" _mhz(unsigned long long const value) noexcept
{
  return static_cast<hertz>(value * 1'000'000);
}

constexpr hertz operator"" _ghz(unsigned long long const value) noexcept
{
  return static_cast<hertz>(value * 1'000'000'000);
}
}
}
}

constexpr std::strong_ordering operator<=>(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_int(lhs) <=> glfw::to_int(rhs);
}

constexpr glfw::hertz operator+(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_hertz(glfw::to_int(lhs) + glfw::to_int(rhs));
}

constexpr glfw::hertz operator-(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_hertz(glfw::to_int(lhs) - glfw::to_int(rhs));
}

constexpr glfw::hertz operator*(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_hertz(glfw::to_int(lhs) * glfw::to_int(rhs));
}

constexpr glfw::hertz operator/(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_hertz(glfw::to_int(lhs) / glfw::to_int(rhs));
}

constexpr glfw::hertz operator%(glfw::hertz const lhs, glfw::hertz const rhs) noexcept
{
  return glfw::to_hertz(glfw::to_int(lhs) % glfw::to_int(rhs));
}

constexpr glfw::hertz & operator+=(glfw::hertz & lhs, glfw::hertz const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr glfw::hertz & operator-=(glfw::hertz & lhs, glfw::hertz const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr glfw::hertz & operator*=(glfw::hertz & lhs, glfw::hertz const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr glfw::hertz & operator/=(glfw::hertz & lhs, glfw::hertz const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr glfw::hertz & operator%=(glfw::hertz & lhs, glfw::hertz const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr int operator+(glfw::hertz const value) noexcept
{
  return glfw::to_int(value);
}

constexpr glfw::hertz operator-(glfw::hertz const value) noexcept
{
  return glfw::to_hertz(-glfw::to_int(value));
}

constexpr glfw::hertz & operator++(glfw::hertz & value) noexcept
{
  using namespace glfw::hertz_literals;
  return value += 1_hz;
}

constexpr glfw::hertz operator++(glfw::hertz & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr glfw::hertz & operator--(glfw::hertz & value) noexcept
{
  using namespace glfw::hertz_literals;
  return value -= 1_hz;
}

constexpr glfw::hertz operator--(glfw::hertz & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <>
struct std::hash<glfw::hertz>
{
    std::size_t operator()(glfw::hertz const value) const noexcept
    {
      return std::hash<int>{}(glfw::to_int(value));
    }
};

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, glfw::hertz const value)
{
  return os << glfw::to_int(value) << "Hz";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, glfw::hertz & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'H' and is.get() == 'z')
    value = glfw::to_hertz(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
