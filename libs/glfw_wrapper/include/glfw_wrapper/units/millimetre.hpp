#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class millimetre : int
{
};

[[nodiscard]]
constexpr millimetre to_millimetre(int const value) noexcept
{
  return static_cast<millimetre>(value);
}

[[nodiscard]]
constexpr int to_int(millimetre const value) noexcept
{
  return static_cast<int>(value);
}

inline namespace literals
{
inline namespace millimetre_literals
{
constexpr millimetre operator"" _mm(unsigned long long const value) noexcept
{
  return static_cast<millimetre>(value);
}
}
}
}

constexpr std::strong_ordering operator<=>(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_int(lhs) <=> glfw::to_int(rhs);
}

constexpr glfw::millimetre operator+(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_millimetre(glfw::to_int(lhs) + glfw::to_int(rhs));
}

constexpr glfw::millimetre operator-(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_millimetre(glfw::to_int(lhs) - glfw::to_int(rhs));
}

constexpr glfw::millimetre operator*(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_millimetre(glfw::to_int(lhs) * glfw::to_int(rhs));
}

constexpr glfw::millimetre operator/(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_millimetre(glfw::to_int(lhs) / glfw::to_int(rhs));
}

constexpr glfw::millimetre operator%(glfw::millimetre const lhs, glfw::millimetre const rhs) noexcept
{
  return glfw::to_millimetre(glfw::to_int(lhs) % glfw::to_int(rhs));
}

constexpr glfw::millimetre & operator+=(glfw::millimetre & lhs, glfw::millimetre const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr glfw::millimetre & operator-=(glfw::millimetre & lhs, glfw::millimetre const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr glfw::millimetre & operator*=(glfw::millimetre & lhs, glfw::millimetre const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr glfw::millimetre & operator/=(glfw::millimetre & lhs, glfw::millimetre const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr glfw::millimetre & operator%=(glfw::millimetre & lhs, glfw::millimetre const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr int operator+(glfw::millimetre const value) noexcept
{
  return glfw::to_int(value);
}

constexpr glfw::millimetre operator-(glfw::millimetre const value) noexcept
{
  return glfw::to_millimetre(-glfw::to_int(value));
}

constexpr glfw::millimetre & operator++(glfw::millimetre & value) noexcept
{
  using namespace glfw::millimetre_literals;
  return value += 1_mm;
}

constexpr glfw::millimetre operator++(glfw::millimetre & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr glfw::millimetre & operator--(glfw::millimetre & value) noexcept
{
  using namespace glfw::millimetre_literals;
  return value -= 1_mm;
}

constexpr glfw::millimetre operator--(glfw::millimetre & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <>
struct std::hash<glfw::millimetre>
{
    std::size_t operator()(glfw::millimetre const value) const noexcept
    {
      return std::hash<int>{}(glfw::to_int(value));
    }
};

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, glfw::millimetre const value)
{
  return os << glfw::to_int(value) << "mm";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, glfw::millimetre & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'm' and is.get() == 'm')
    value = glfw::to_millimetre(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
