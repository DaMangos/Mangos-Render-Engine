#pragma once

namespace mgo
{
template <class handling_type>
struct handle_traits;

template <class handling_type>
struct handle_traits<handling_type[]>
{
    using handle_type  = handling_type[];
    using element_type = handling_type;
    using pointer      = handling_type *;
};

template <class handling_type>
struct handle_traits<handling_type *>
{
    using handle_type  = handling_type;
    using element_type = handling_type;
    using pointer      = handling_type *;
};
}
