#include <glfw/except/bad_window_access.hpp>
#include <gtest/gtest.h>

#include <type_traits>

TEST(Glfw, badWindowAccessMessage)
{
  try
  {
    throw glfw::bad_window_access();
  }
  catch(glfw::exception const & e)
  {
    ASSERT_TRUE(e.what());
  }

  try
  {
    throw glfw::bad_window_access();
  }
  catch(std::exception const & e)
  {
    ASSERT_TRUE(e.what());
  }
}

static_assert(std::is_nothrow_move_constructible_v<glfw::bad_window_access>);
static_assert(std::is_nothrow_move_assignable_v<glfw::bad_window_access>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::bad_window_access>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::bad_window_access>);

static_assert(std::is_base_of_v<glfw::exception, glfw::bad_window_access>);
static_assert(std::is_base_of_v<std::exception, glfw::bad_window_access>);