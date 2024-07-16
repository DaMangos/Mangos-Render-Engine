#pragma once

#include <type_traits>

namespace glfw
{
template <class ValueType>
requires std::is_arithmetic_v<ValueType> or std::is_enum_v<ValueType>
struct offset
{
    ValueType x;
    ValueType y;
};
}
