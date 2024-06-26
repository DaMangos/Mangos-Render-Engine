#pragma once

#include <glfw_wrapper/version_3_4/coordinates.hpp>
#include <glfw_wrapper/version_3_4/extent.hpp>

namespace glfw
{
inline namespace version_3_4
{
template <class ValueType>
requires std::is_arithmetic_v<ValueType> or std::is_enum_v<ValueType>
struct workarea
{
    coordinates<ValueType> position;
    extent<ValueType>      size;
};
}
}