#include <glfw/except/not_initialized.hpp>
#include <gtest/gtest.h>

TEST(Glfw, notInitializedMessage)
{
  try
  {
    throw glfw::not_initialized("not initialized");
  }
  catch(glfw::exception const & e)
  {
    ASSERT_STREQ(e.what(), "not initialized");
  }

  try
  {
    throw glfw::not_initialized("not initialized");
  }
  catch(std::exception const & e)
  {
    ASSERT_STREQ(e.what(), "not initialized");
  }
}

static_assert(std::is_nothrow_move_constructible_v<glfw::not_initialized>);
static_assert(std::is_nothrow_move_assignable_v<glfw::not_initialized>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::not_initialized>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::not_initialized>);

static_assert(std::is_base_of_v<glfw::exception, glfw::not_initialized>);
static_assert(std::is_base_of_v<std::exception, glfw::not_initialized>);