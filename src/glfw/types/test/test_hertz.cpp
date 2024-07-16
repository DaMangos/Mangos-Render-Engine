#include <glfw/types/hertz.hpp>
#include <gtest/gtest.h>

#include <random>
#include <string>
#include <type_traits>

static_assert(std::is_trivial_v<glfw::hertz>);
static_assert(std::is_standard_layout_v<glfw::hertz>);
static_assert(sizeof(glfw::hertz) == sizeof(int));

namespace
{
using namespace glfw::hertz_literals;
static_assert(1_hz == static_cast<glfw::hertz>(1));
static_assert(1_khz == static_cast<glfw::hertz>(1'000));
static_assert(1_mhz == static_cast<glfw::hertz>(1'000'000));
static_assert(1_ghz == static_cast<glfw::hertz>(1'000'000'000));
}

TEST(Glfw, hertzArithmetic)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_hz = static_cast<glfw::hertz>(lhs);
  auto const rhs_hz = static_cast<glfw::hertz>(rhs);

  ASSERT_EQ(lhs_hz * rhs_hz, static_cast<glfw::hertz>(lhs * rhs));
  ASSERT_EQ(static_cast<int>(lhs_hz * rhs_hz), lhs * rhs);

  ASSERT_EQ(lhs_hz / rhs_hz, static_cast<glfw::hertz>(lhs / rhs));
  ASSERT_EQ(static_cast<int>(lhs_hz / rhs_hz), lhs / rhs);

  ASSERT_EQ(lhs_hz + rhs_hz, static_cast<glfw::hertz>(lhs + rhs));
  ASSERT_EQ(static_cast<int>(lhs_hz + rhs_hz), lhs + rhs);

  ASSERT_EQ(lhs_hz - rhs_hz, static_cast<glfw::hertz>(lhs - rhs));
  ASSERT_EQ(static_cast<int>(lhs_hz - rhs_hz), lhs - rhs);

  ASSERT_EQ(lhs_hz % rhs_hz, static_cast<glfw::hertz>(lhs % rhs));
  ASSERT_EQ(static_cast<int>(lhs_hz % rhs_hz), lhs % rhs);
}

TEST(Glfw, hertzComparison)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_hz = static_cast<glfw::hertz>(lhs);
  auto const rhs_hz = static_cast<glfw::hertz>(rhs);

  ASSERT_EQ(lhs_hz > rhs_hz, lhs > rhs);
  ASSERT_EQ(lhs_hz >= rhs_hz, lhs >= rhs);
  ASSERT_EQ(lhs_hz < rhs_hz, lhs < rhs);
  ASSERT_EQ(lhs_hz <= rhs_hz, lhs <= rhs);
  ASSERT_EQ(lhs_hz == rhs_hz, lhs == rhs);
  ASSERT_EQ(lhs_hz != rhs_hz, lhs != rhs);
  ASSERT_EQ(lhs_hz <=> rhs_hz, lhs <=> rhs);
}

TEST(Glfw, hertzGoodIo)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_hz = static_cast<glfw::hertz>(x);

  std::stringstream stream;

  stream << x_hz;

  ASSERT_EQ(stream.str(), std::to_string(x) + "Hz");
  ASSERT_TRUE(stream.good());

  glfw::hertz y_hz;

  stream >> y_hz;
  ASSERT_EQ(x_hz, y_hz);
  ASSERT_TRUE(stream.good());
}

TEST(Glfw, hertzFailIo)
{
  std::random_device rd;

  std::stringstream stream;

  stream << std::default_random_engine(rd())();

  glfw::hertz x_hz;

  stream >> x_hz;

  ASSERT_TRUE(stream.fail());
}

TEST(Glfw, hertzHash)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_hz = static_cast<glfw::hertz>(x);

  ASSERT_EQ(std::hash<glfw::hertz>{}(x_hz), std::hash<int>{}(x));
}
