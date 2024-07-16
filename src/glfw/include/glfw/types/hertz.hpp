#pragma once

#include <compare>
#include <istream>
#include <ostream>

namespace glfw
{
enum class hertz : int
{
};

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

constexpr std::strong_ordering operator<=>(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<int>(lhs) <=> static_cast<int>(rhs);
}

constexpr hertz operator+(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<hertz>(static_cast<int>(lhs) + static_cast<int>(rhs));
}

constexpr hertz operator-(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<hertz>(static_cast<int>(lhs) - static_cast<int>(rhs));
}

constexpr hertz operator*(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<hertz>(static_cast<int>(lhs) * static_cast<int>(rhs));
}

constexpr hertz operator/(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<hertz>(static_cast<int>(lhs) / static_cast<int>(rhs));
}

constexpr hertz operator%(hertz const lhs, hertz const rhs) noexcept
{
  return static_cast<hertz>(static_cast<int>(lhs) % static_cast<int>(rhs));
}

constexpr hertz & operator+=(hertz & lhs, hertz const rhs) noexcept
{
  return lhs = lhs + rhs;
}

constexpr hertz & operator-=(hertz & lhs, hertz const rhs) noexcept
{
  return lhs = lhs - rhs;
}

constexpr hertz & operator*=(hertz & lhs, hertz const rhs) noexcept
{
  return lhs = lhs * rhs;
}

constexpr hertz & operator/=(hertz & lhs, hertz const rhs) noexcept
{
  return lhs = lhs / rhs;
}

constexpr hertz & operator%=(hertz & lhs, hertz const rhs) noexcept
{
  return lhs = lhs % rhs;
}

constexpr hertz operator-(hertz const value) noexcept
{
  return static_cast<hertz>(-static_cast<int>(value));
}

constexpr hertz & operator++(hertz & value) noexcept
{
  using namespace hertz_literals;
  return value += 1_hz;
}

constexpr hertz operator++(hertz & value, int) noexcept
{
  auto const tmp = value;
  ++value;
  return tmp;
}

constexpr hertz & operator--(hertz & value) noexcept
{
  using namespace hertz_literals;
  return value -= 1_hz;
}

constexpr hertz operator--(hertz & value, int) noexcept
{
  auto const tmp = value;
  --value;
  return tmp;
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, hertz const value)
{
  return os << static_cast<int>(value) << "Hz";
}

template <class CharT, class Traits = std::char_traits<CharT>>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is, hertz & value)
{
  int tmp = {};
  is >> tmp;

  if(is.get() == 'H' and is.get() == 'z')
    value = static_cast<hertz>(tmp);
  else
    is.setstate(std::ios_base::failbit);

  return is;
}
}

template <>
struct std::hash<glfw::hertz>
{
    std::size_t operator()(glfw::hertz const value) const noexcept
    {
      return std::hash<int>{}(static_cast<int>(value));
    }
};