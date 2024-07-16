#include <glfw/except/bad_monitor_access.hpp>
#include <gtest/gtest.h>

#include <type_traits>

TEST(Glfw, badMonitorAccessMessage)
{
  try
  {
    throw glfw::bad_monitor_access();
  }
  catch(glfw::exception const & e)
  {
    ASSERT_TRUE(e.what());
  }

  try
  {
    throw glfw::bad_monitor_access();
  }
  catch(std::exception const & e)
  {
    ASSERT_TRUE(e.what());
  }
}

static_assert(std::is_nothrow_move_constructible_v<glfw::bad_monitor_access>);
static_assert(std::is_nothrow_move_assignable_v<glfw::bad_monitor_access>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::bad_monitor_access>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::bad_monitor_access>);

static_assert(std::is_base_of_v<glfw::exception, glfw::bad_monitor_access>);
static_assert(std::is_base_of_v<std::exception, glfw::bad_monitor_access>);