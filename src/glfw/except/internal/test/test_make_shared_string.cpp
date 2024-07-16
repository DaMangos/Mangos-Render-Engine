#include <gtest/gtest.h>

#include "../make_shared_string.hpp"
#include <tuple>

TEST(GlfwInternal, makeSharedStringNullptr)
{
  ASSERT_THROW(std::ignore = glfw::internal::make_shared_string(nullptr), std::invalid_argument);
  ASSERT_THROW(std::ignore = glfw::internal::make_shared_string(static_cast<char const * const>(nullptr)), std::invalid_argument);
}

TEST(GlfwInternal, makeSharedStringEmpty)
{
  auto const ptr = glfw::internal::make_shared_string("");
  ASSERT_STREQ(ptr.get(), "");
}

TEST(GlfwInternal, makeSharedString)
{
  auto const ptr = glfw::internal::make_shared_string("test");
  ASSERT_STREQ(ptr.get(), "test");
}