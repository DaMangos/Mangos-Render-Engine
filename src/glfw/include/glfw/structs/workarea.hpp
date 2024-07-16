#pragma once

#include <glfw/structs/coordinates.hpp>
#include <glfw/structs/extent.hpp>

namespace glfw
{
template <class ValueType>
requires std::is_arithmetic_v<ValueType> or std::is_enum_v<ValueType>
struct workarea
{
    coordinates<ValueType> position;
    extent<ValueType>      size;
};
}
