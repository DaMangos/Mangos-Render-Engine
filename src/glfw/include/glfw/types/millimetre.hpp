#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class millimetre : int
{
};

inline namespace literals
{
inline namespace millimetre_literals
{
constexpr millimetre operator"" _mm(unsigned long long const value) noexcept
{
  return static_cast<millimetre>(value);
}

constexpr millimetre operator"" _cm(unsigned long long const value) noexcept
{
  return static_cast<millimetre>(value * 10);
}

constexpr millimetre operator"" _m(unsigned long long const value) noexcept
{
  return static_cast<millimetre>(value * 1'000);
}

constexpr millimetre operator"" _km(unsigned long long const value) noexcept
{
  return static_cast<millimetre>(value * 1'000'000);
}
}
}

constexpr std::strong_ordering operator<=>(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<int>(lhs) <=> static_cast<int>(rhs);
}

constexpr millimetre operator+(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<millimetre>(static_cast<int>(lhs) + static_cast<int>(rhs));
}

constexpr millimetre operator-(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<millimetre>(static_cast<int>(lhs) - static_cast<int>(rhs));
}

constexpr millimetre operator*(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<millimetre>(static_cast<int>(lhs) * static_cast<int>(rhs));
}

constexpr millimetre operator/(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<millimetre>(static_cast<int>(lhs) / static_cast<int>(rhs));
}

constexpr millimetre operator%(millimetre const lhs, millimetre const rhs) noexcept
{
  return static_cast<millimetre>(static_cast<int>(lhs) % static_cast<int>(rhs));
}

constexpr millimetre & operator+=(millimetre & lhs, millimetre const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr millimetre & operator-=(millimetre & lhs, millimetre const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr millimetre & operator*=(millimetre & lhs, millimetre const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr millimetre & operator/=(millimetre & lhs, millimetre const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr millimetre & operator%=(millimetre & lhs, millimetre const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr millimetre operator-(millimetre const value) noexcept
{
  return static_cast<millimetre>(-static_cast<int>(value));
}

constexpr millimetre & operator++(millimetre & value) noexcept
{
  using namespace millimetre_literals;
  return value += 1_mm;
}

constexpr millimetre operator++(millimetre & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr millimetre & operator--(millimetre & value) noexcept
{
  using namespace millimetre_literals;
  return value -= 1_mm;
}

constexpr millimetre operator--(millimetre & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, millimetre const value)
{
  return os << static_cast<int>(value) << "mm";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, millimetre & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'm' and is.get() == 'm')
    value = static_cast<millimetre>(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
}

template <>
struct std::hash<glfw::millimetre>
{
    std::size_t operator()(glfw::millimetre const value) const noexcept
    {
      return std::hash<int>{}(static_cast<int>(value));
    }
};