#pragma once

#include "non_dispatchable_handles.hpp"

#include <vector>

namespace vulkan
{
struct command_buffers
{
    friend device;

    using size_type              = typename handle_traits<VkCommandBuffer[]>::size_type;
    using value_type             = typename handle_traits<VkCommandBuffer[]>::value_type;
    using difference_type        = typename handle_traits<VkCommandBuffer[]>::difference_type;
    using pointer                = typename handle_traits<VkCommandBuffer[]>::pointer;
    using const_pointer          = typename handle_traits<VkCommandBuffer[]>::const_pointer;
    using reference              = typename handle_traits<VkCommandBuffer[]>::reference;
    using const_reference        = typename handle_traits<VkCommandBuffer[]>::const_reference;
    using iterator               = typename handle_traits<VkCommandBuffer[]>::iterator;
    using const_iterator         = typename handle_traits<VkCommandBuffer[]>::const_iterator;
    using reverse_iterator       = typename handle_traits<VkCommandBuffer[]>::reverse_iterator;
    using const_reverse_iterator = typename handle_traits<VkCommandBuffer[]>::const_reverse_iterator;
    using element_type           = typename handle_traits<VkCommandBuffer[]>::element_type;
    using deleter_type           = typename handle_traits<VkCommandBuffer[]>::deleter_type;
    using unique_type            = typename handle_traits<VkCommandBuffer[]>::unique_type;
    using shared_type            = typename handle_traits<VkCommandBuffer[]>::shared_type;

    size_type size() const noexcept;

    pointer get() const noexcept;

    pointer data() const noexcept;

    reference operator[](size_type i) const noexcept;

    reference at(size_type i) const;

    iterator begin() const noexcept;

    iterator end() const noexcept;

    iterator cbegin() const noexcept;

    iterator cend() const noexcept;

    reverse_iterator rbegin() const noexcept;

    reverse_iterator rend() const noexcept;

    reverse_iterator crbegin() const noexcept;

    reverse_iterator crend() const noexcept;

  private:
    command_buffers(size_type count, pointer ptr, deleter_type &&deleter);

    size_type   _count;
    unique_type _command_buffers;
};
}