#pragma once

#include <glfw_wrapper/version_3_4/cursor.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

GLFWcursor * glfw::cursor::get() const noexcept
{
  return _cursor.get();
}

void glfw::cursor::reset() noexcept
{
  _cursor.reset();
}

glfw::cursor::cursor() noexcept
: _cursor(nullptr, glfwDestroyCursor)
{
}

glfw::cursor::cursor(nullhandle_t) noexcept
: _cursor(nullptr, glfwDestroyCursor)
{
}

glfw::cursor & glfw::cursor::operator=(nullhandle_t) noexcept
{
  reset();
  return *this;
}

std::strong_ordering glfw::cursor::operator<=>(nullhandle_t) const noexcept
{
  return _cursor <=> nullptr;
}

std::strong_ordering glfw::cursor::operator<=>(cursor const & other) const noexcept
{
  return _cursor <=> other._cursor;
}

glfw::cursor::operator bool() const noexcept
{
  return static_cast<bool>(_cursor);
}

glfw::cursor::cursor(GLFWcursor * cursor, library const & library) noexcept
: _library(library),
  _cursor(cursor, glfwDestroyCursor)
{
}