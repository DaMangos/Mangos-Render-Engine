#include <glfw_wrapper/hertz.hpp>
#include <gtest/gtest.h>

#include <random>
#include <string>

static_assert(std::is_trivial_v<glfw::hertz>);
static_assert(std::is_standard_layout_v<glfw::hertz>);
static_assert(sizeof(glfw::hertz) == sizeof(int));

TEST(glfw, hertz_arithmetic)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_hz = glfw::to_hertz(lhs);
  auto const rhs_hz = glfw::to_hertz(rhs);

  ASSERT_EQ(lhs_hz * rhs_hz, glfw::to_hertz(lhs * rhs));
  ASSERT_EQ(glfw::to_int(lhs_hz * rhs_hz), lhs * rhs);

  ASSERT_EQ(lhs_hz / rhs_hz, glfw::to_hertz(lhs / rhs));
  ASSERT_EQ(glfw::to_int(lhs_hz / rhs_hz), lhs / rhs);

  ASSERT_EQ(lhs_hz + rhs_hz, glfw::to_hertz(lhs + rhs));
  ASSERT_EQ(glfw::to_int(lhs_hz + rhs_hz), lhs + rhs);

  ASSERT_EQ(lhs_hz - rhs_hz, glfw::to_hertz(lhs - rhs));
  ASSERT_EQ(glfw::to_int(lhs_hz - rhs_hz), lhs - rhs);

  ASSERT_EQ(lhs_hz % rhs_hz, glfw::to_hertz(lhs % rhs));
  ASSERT_EQ(glfw::to_int(lhs_hz % rhs_hz), lhs % rhs);
}

TEST(glfw, hertz_comparison)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_hz = glfw::to_hertz(lhs);
  auto const rhs_hz = glfw::to_hertz(rhs);

  ASSERT_EQ(lhs_hz > rhs_hz, lhs > rhs);
  ASSERT_EQ(lhs_hz >= rhs_hz, lhs >= rhs);
  ASSERT_EQ(lhs_hz < rhs_hz, lhs < rhs);
  ASSERT_EQ(lhs_hz <= rhs_hz, lhs <= rhs);
  ASSERT_EQ(lhs_hz == rhs_hz, lhs == rhs);
  ASSERT_EQ(lhs_hz != rhs_hz, lhs != rhs);
  ASSERT_EQ(lhs_hz <=> rhs_hz, lhs <=> rhs);
}

TEST(glfw, hertz_literals)
{
  using namespace glfw::hertz_literals;

  ASSERT_EQ(1_hz, glfw::to_hertz(1));
  ASSERT_EQ(1_khz, glfw::to_hertz(1'000));
  ASSERT_EQ(1_mhz, glfw::to_hertz(1'000'000));
  ASSERT_EQ(1_ghz, glfw::to_hertz(1'000'000'000));
}

TEST(glfw, hertz_good_io)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_hz = glfw::to_hertz(x);

  std::stringstream stream;

  stream << x_hz;

  ASSERT_EQ(stream.str(), std::to_string(x) + "Hz");
  ASSERT_TRUE(stream.good());

  glfw::hertz y_hz;

  stream >> y_hz;
  ASSERT_EQ(x_hz, y_hz);
  ASSERT_TRUE(stream.good());
}

TEST(glfw, hertz_fail_io)
{
  std::random_device rd;

  std::stringstream stream;

  stream << std::default_random_engine(rd())();

  glfw::hertz x_hz;

  stream >> x_hz;

  ASSERT_TRUE(stream.fail());
}

TEST(glfw, hertz_hash)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_hz = glfw::to_hertz(x);

  ASSERT_EQ(std::hash<glfw::hertz>{}(x_hz), std::hash<int>{}(x));
}