#include <glfw_wrapper/types/millimetre.hpp>
#include <gtest/gtest.h>

#include <random>
#include <string>
#include <type_traits>

static_assert(std::is_trivial_v<glfw::millimetre>);
static_assert(std::is_standard_layout_v<glfw::millimetre>);
static_assert(sizeof(glfw::millimetre) == sizeof(int));

namespace
{
using namespace glfw::millimetre_literals;
static_assert(1_mm == static_cast<glfw::millimetre>(1));
static_assert(1_cm == static_cast<glfw::millimetre>(10));
static_assert(1_m == static_cast<glfw::millimetre>(1'000));
static_assert(1_km == static_cast<glfw::millimetre>(1'000'000));
}

TEST(glfw, millimetre_arithmetic)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_mm = static_cast<glfw::millimetre>(lhs);
  auto const rhs_mm = static_cast<glfw::millimetre>(rhs);

  ASSERT_EQ(lhs_mm * rhs_mm, static_cast<glfw::millimetre>(lhs * rhs));
  ASSERT_EQ(static_cast<int>(lhs_mm * rhs_mm), lhs * rhs);

  ASSERT_EQ(lhs_mm / rhs_mm, static_cast<glfw::millimetre>(lhs / rhs));
  ASSERT_EQ(static_cast<int>(lhs_mm / rhs_mm), lhs / rhs);

  ASSERT_EQ(lhs_mm + rhs_mm, static_cast<glfw::millimetre>(lhs + rhs));
  ASSERT_EQ(static_cast<int>(lhs_mm + rhs_mm), lhs + rhs);

  ASSERT_EQ(lhs_mm - rhs_mm, static_cast<glfw::millimetre>(lhs - rhs));
  ASSERT_EQ(static_cast<int>(lhs_mm - rhs_mm), lhs - rhs);

  ASSERT_EQ(lhs_mm % rhs_mm, static_cast<glfw::millimetre>(lhs % rhs));
  ASSERT_EQ(static_cast<int>(lhs_mm % rhs_mm), lhs % rhs);
}

TEST(glfw, millimetre_comparison)
{
  std::random_device rd;

  auto const lhs = static_cast<int>(std::default_random_engine(rd())());
  auto const rhs = static_cast<int>(std::default_random_engine(rd())());

  auto const lhs_mm = static_cast<glfw::millimetre>(lhs);
  auto const rhs_mm = static_cast<glfw::millimetre>(rhs);

  ASSERT_EQ(lhs_mm > rhs_mm, lhs > rhs);
  ASSERT_EQ(lhs_mm >= rhs_mm, lhs >= rhs);
  ASSERT_EQ(lhs_mm < rhs_mm, lhs < rhs);
  ASSERT_EQ(lhs_mm <= rhs_mm, lhs <= rhs);
  ASSERT_EQ(lhs_mm == rhs_mm, lhs == rhs);
  ASSERT_EQ(lhs_mm != rhs_mm, lhs != rhs);
  ASSERT_EQ(lhs_mm <=> rhs_mm, lhs <=> rhs);
}

TEST(glfw, millimetre_good_io)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_mm = static_cast<glfw::millimetre>(x);

  std::stringstream stream;

  stream << x_mm;

  ASSERT_EQ(stream.str(), std::to_string(x) + "mm");
  ASSERT_TRUE(stream.good());

  glfw::millimetre y_mm;

  stream >> y_mm;
  ASSERT_EQ(x_mm, y_mm);
  ASSERT_TRUE(stream.good());
}

TEST(glfw, millimetre_fail_io)
{
  std::random_device rd;

  std::stringstream stream;

  stream << std::default_random_engine(rd())();

  glfw::millimetre x_mm;

  stream >> x_mm;

  ASSERT_TRUE(stream.fail());
}

TEST(glfw, millimetre_hash)
{
  std::random_device rd;

  auto const x    = static_cast<int>(std::default_random_engine(rd())());
  auto const x_mm = static_cast<glfw::millimetre>(x);

  ASSERT_EQ(std::hash<glfw::millimetre>{}(x_mm), std::hash<int>{}(x));
}
