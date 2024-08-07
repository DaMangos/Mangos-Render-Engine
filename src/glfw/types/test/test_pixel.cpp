#include <glfw/types/pixel.hpp>
#include <gtest/gtest.h>

#include <random>
#include <string>
#include <type_traits>

static_assert(std::is_trivial_v<glfw::pixel>);
static_assert(std::is_standard_layout_v<glfw::pixel>);
static_assert(sizeof(glfw::pixel) == sizeof(int));

namespace
{
using namespace glfw::pixel_literals;
static_assert(1_px == static_cast<glfw::pixel>(1));
}

TEST(Glfw, pixelArithmetic)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_px = static_cast<glfw::pixel>(lhs);
  auto const rhs_px = static_cast<glfw::pixel>(rhs);

  ASSERT_EQ(lhs_px * rhs_px, static_cast<glfw::pixel>(lhs * rhs));
  ASSERT_EQ(static_cast<int>(lhs_px * rhs_px), lhs * rhs);

  ASSERT_EQ(lhs_px / rhs_px, static_cast<glfw::pixel>(lhs / rhs));
  ASSERT_EQ(static_cast<int>(lhs_px / rhs_px), lhs / rhs);

  ASSERT_EQ(lhs_px + rhs_px, static_cast<glfw::pixel>(lhs + rhs));
  ASSERT_EQ(static_cast<int>(lhs_px + rhs_px), lhs + rhs);

  ASSERT_EQ(lhs_px - rhs_px, static_cast<glfw::pixel>(lhs - rhs));
  ASSERT_EQ(static_cast<int>(lhs_px - rhs_px), lhs - rhs);

  ASSERT_EQ(lhs_px % rhs_px, static_cast<glfw::pixel>(lhs % rhs));
  ASSERT_EQ(static_cast<int>(lhs_px % rhs_px), lhs % rhs);
}

TEST(Glfw, pixelComparison)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_px = static_cast<glfw::pixel>(lhs);
  auto const rhs_px = static_cast<glfw::pixel>(rhs);

  ASSERT_EQ(lhs_px > rhs_px, lhs > rhs);
  ASSERT_EQ(lhs_px >= rhs_px, lhs >= rhs);
  ASSERT_EQ(lhs_px < rhs_px, lhs < rhs);
  ASSERT_EQ(lhs_px <= rhs_px, lhs <= rhs);
  ASSERT_EQ(lhs_px == rhs_px, lhs == rhs);
  ASSERT_EQ(lhs_px != rhs_px, lhs != rhs);
  ASSERT_EQ(lhs_px <=> rhs_px, lhs <=> rhs);
}

TEST(Glfw, pixelGoodIo)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_px = static_cast<glfw::pixel>(x);

  std::stringstream stream;

  stream << x_px;

  ASSERT_EQ(stream.str(), std::to_string(x) + "px");
  ASSERT_TRUE(stream.good());

  glfw::pixel y_px;

  stream >> y_px;
  ASSERT_EQ(x_px, y_px);
  ASSERT_TRUE(stream.good());
}

TEST(Glfw, pixelFailIo)
{
  std::random_device rd;

  std::stringstream stream;

  stream << std::default_random_engine(rd())();

  glfw::pixel x_px;

  stream >> x_px;

  ASSERT_TRUE(stream.fail());
}

TEST(Glfw, pixelHash)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_px = static_cast<glfw::pixel>(x);

  ASSERT_EQ(std::hash<glfw::pixel>{}(x_px), std::hash<int>{}(x));
}
