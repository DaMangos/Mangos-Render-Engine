#include <glfw/except/out_of_memory.hpp>
#include <gtest/gtest.h>

#include <type_traits>

TEST(Glfw, outWindowMemoryMessage)
{
  try
  {
    throw glfw::out_of_memory("out of memory");
  }
  catch(glfw::exception const & e)
  {
    ASSERT_STREQ(e.what(), "out of memory");
  }

  try
  {
    throw glfw::out_of_memory("out of memory");
  }
  catch(std::exception const & e)
  {
    ASSERT_STREQ(e.what(), "out of memory");
  }
}

static_assert(std::is_nothrow_move_constructible_v<glfw::out_of_memory>);
static_assert(std::is_nothrow_move_assignable_v<glfw::out_of_memory>);

static_assert(std::is_nothrow_copy_constructible_v<glfw::out_of_memory>);
static_assert(std::is_nothrow_copy_assignable_v<glfw::out_of_memory>);

static_assert(std::is_base_of_v<glfw::exception, glfw::out_of_memory>);
static_assert(std::is_base_of_v<std::bad_alloc, glfw::out_of_memory>);