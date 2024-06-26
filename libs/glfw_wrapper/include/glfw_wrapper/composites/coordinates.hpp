#pragma once

#include <type_traits>

namespace glfw
{
inline namespace version_3_4
{
template <class ValueType>
requires std::is_arithmetic_v<ValueType> or std::is_enum_v<ValueType>
struct coordinates
{
    ValueType x;
    ValueType y;
};
}
}