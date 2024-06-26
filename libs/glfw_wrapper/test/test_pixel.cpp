#include <glfw_wrapper/pixel.hpp>
#include <gtest/gtest.h>

#include <random>
#include <string>
#include <type_traits>

static_assert(std::is_trivial_v<glfw::pixel>);
static_assert(std::is_standard_layout_v<glfw::pixel>);
static_assert(sizeof(glfw::pixel) == sizeof(int));

TEST(glfw, pixel_arithmetic)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_px = glfw::to_pixel(lhs);
  auto const rhs_px = glfw::to_pixel(rhs);

  ASSERT_EQ(lhs_px * rhs_px, glfw::to_pixel(lhs * rhs));
  ASSERT_EQ(glfw::to_int(lhs_px * rhs_px), lhs * rhs);

  ASSERT_EQ(lhs_px / rhs_px, glfw::to_pixel(lhs / rhs));
  ASSERT_EQ(glfw::to_int(lhs_px / rhs_px), lhs / rhs);

  ASSERT_EQ(lhs_px + rhs_px, glfw::to_pixel(lhs + rhs));
  ASSERT_EQ(glfw::to_int(lhs_px + rhs_px), lhs + rhs);

  ASSERT_EQ(lhs_px - rhs_px, glfw::to_pixel(lhs - rhs));
  ASSERT_EQ(glfw::to_int(lhs_px - rhs_px), lhs - rhs);

  ASSERT_EQ(lhs_px % rhs_px, glfw::to_pixel(lhs % rhs));
  ASSERT_EQ(glfw::to_int(lhs_px % rhs_px), lhs % rhs);
}

TEST(glfw, pixel_comparison)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_px = glfw::to_pixel(lhs);
  auto const rhs_px = glfw::to_pixel(rhs);

  ASSERT_EQ(lhs_px > rhs_px, lhs > rhs);
  ASSERT_EQ(lhs_px >= rhs_px, lhs >= rhs);
  ASSERT_EQ(lhs_px < rhs_px, lhs < rhs);
  ASSERT_EQ(lhs_px <= rhs_px, lhs <= rhs);
  ASSERT_EQ(lhs_px == rhs_px, lhs == rhs);
  ASSERT_EQ(lhs_px != rhs_px, lhs != rhs);
  ASSERT_EQ(lhs_px <=> rhs_px, lhs <=> rhs);
}

TEST(glfw, pixel_literals)
{
  using namespace glfw::pixel_literals;

  ASSERT_EQ(1_px, glfw::to_pixel(1));
}

TEST(glfw, pixel_good_io)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_px = glfw::to_pixel(x);

  std::stringstream stream;

  stream << x_px;

  ASSERT_EQ(stream.str(), std::to_string(x) + "px");
  ASSERT_TRUE(stream.good());

  glfw::pixel y_px;

  stream >> y_px;
  ASSERT_EQ(x_px, y_px);
  ASSERT_TRUE(stream.good());
}

TEST(glfw, pixel_fail_io)
{
  std::random_device rd;

  std::stringstream stream;

  stream << std::default_random_engine(rd())();

  glfw::pixel x_px;

  stream >> x_px;

  ASSERT_TRUE(stream.fail());
}

TEST(glfw, pixel_hash)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_px = glfw::to_pixel(x);

  ASSERT_EQ(std::hash<glfw::pixel>{}(x_px), std::hash<int>{}(x));
}