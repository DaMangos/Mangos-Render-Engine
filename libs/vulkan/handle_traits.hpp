#pragma once

#include <functional>
#include <memory>

namespace vulkan
{
template <class handle>
struct handle_traits;

template <class handle>
struct handle_traits<handle *>
{
    using pointer       = handle *;
    using const_pointer = handle const *;
    using element_type  = handle;
    using deleter_type  = std::function<void(pointer)>;
    using unique_type   = std::unique_ptr<element_type, deleter_type>;
    using shared_type   = std::shared_ptr<element_type>;
};

template <class handle>
struct handle_traits<handle[]>
{
    using size_type              = std::size_t;
    using value_type             = handle;
    using difference_type        = std::ptrdiff_t;
    using pointer                = handle *;
    using const_pointer          = handle const *;
    using reference              = handle &;
    using const_reference        = handle const &;
    using iterator               = handle *;
    using const_iterator         = handle const *;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using element_type           = handle;
    using deleter_type           = std::function<void(pointer)>;
    using unique_type            = std::unique_ptr<element_type, deleter_type>;
    using shared_type            = std::shared_ptr<element_type>;
};
}