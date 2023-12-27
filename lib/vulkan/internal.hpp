#pragma once

#include <memory>
#include <ranges>
#include <source_location>
#include <string>
#include <utility>
#include <vector>

#define ENABLE_BETA_EXTENSIONS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vulkan
{
struct device;
}

namespace vulkan::internal
{
enum struct smart_type
{
  unique,
  shared
};

template <smart_type type, auto delete_fn, class dispatcher_pointer, class managed_pointer>
struct handle final
{
    using pointer      = typename std::pointer_traits<managed_pointer>::pointer;
    using element_type = typename std::pointer_traits<managed_pointer>::element_type;

    [[nodiscard]]
    constexpr pointer get() const noexcept
    {
      return _smart_ptr.get();
    }

    constexpr operator bool() const noexcept
    {
      return static_cast<bool>(_smart_ptr);
    }

    constexpr bool operator==(handle const &other) noexcept
    {
      return _smart_ptr == other._handle;
    }

    constexpr bool operator!=(handle const &other) noexcept
    {
      return _smart_ptr != other._handle;
    }

    constexpr handle(handle &&)                 = default;
    constexpr handle(handle const &)            = delete;
    constexpr handle &operator=(handle &&)      = default;
    constexpr handle &operator=(handle const &) = delete;
    constexpr ~handle()                         = default;

  private:
    template <template <auto, class, class> class, auto, auto, class>
    friend struct make_handle_fn;

    template <auto, auto, class, class>
    friend struct make_collection_fn;

    template <auto, class, class>
    friend struct collection_of_handles;

    friend struct ::vulkan::device;

    constexpr handle(auto const &dispatcher, auto const ptr) noexcept
    : _smart_ptr(ptr, deleter{dispatcher})
    {
    }

    struct deleter final
    {
        constexpr void operator()(pointer const ptr) const noexcept
        {
          delete_fn(dispatcher.get(), ptr, nullptr);
        }

        std::shared_ptr<typename std::pointer_traits<dispatcher_pointer>::element_type> dispatcher;
    };

    std::conditional_t<type == smart_type::unique, std::unique_ptr<element_type, deleter>, std::shared_ptr<element_type>>
      _smart_ptr;
};

template <auto delete_fn, class managed, class pool_type>
struct collection_of_handles final
{
    using size_type              = std::uint32_t;
    using difference_type        = std::int32_t;
    using value_type             = std::vector<managed>::value_type;
    using reference              = std::vector<managed>::reference;
    using const_reference        = std::vector<managed>::const_reference;
    using pointer                = std::vector<managed>::pointer;
    using const_pointer          = std::vector<managed>::const_pointer;
    using iterator               = std::vector<managed>::iterator;
    using const_iterator         = std::vector<managed>::const_iterator;
    using reverse_iterator       = std::vector<managed>::reverse_iterator;
    using const_reverse_iterator = std::vector<managed>::const_reverse_iterator;

    [[nodiscard]]
    bool empty() const noexcept
    {
      return _ptrs.empty();
    }

    [[nodiscard]]
    constexpr size_type size() const noexcept
    {
      return static_cast<size_type>(_ptrs.size());
    }

    [[nodiscard]]
    constexpr const_pointer data() const noexcept
    {
      return _ptrs.data();
    }

    [[nodiscard]]
    constexpr const_iterator begin() const noexcept
    {
      return _ptrs.begin();
    }

    [[nodiscard]]
    constexpr const_iterator end() const noexcept
    {
      return _ptrs.end();
    }

    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept
    {
      return _ptrs.cbegin();
    }

    [[nodiscard]]
    constexpr const_iterator cend() const noexcept
    {
      return _ptrs.cend();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator rbegin() const noexcept
    {
      return _ptrs.rbegin();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator rend() const noexcept
    {
      return _ptrs.rend();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator crbegin() const noexcept
    {
      return _ptrs.crbegin();
    }

    [[nodiscard]]
    constexpr const_reverse_iterator crend() const noexcept
    {
      return _ptrs.crend();
    }

    [[nodiscard]]
    constexpr value_type at(size_type const i) const
    {
      return _ptrs.at(i);
    }

    constexpr value_type operator[](size_type const i) const noexcept
    {
      return _ptrs[i];
    }

    constexpr operator bool() const noexcept
    {
      return not empty();
    }

    constexpr bool operator==(collection_of_handles const &other) noexcept
    {
      return _ptrs == other._ptrs;
    }

    constexpr bool operator!=(collection_of_handles const &other) noexcept
    {
      return _ptrs != other._ptrs;
    }

    constexpr ~collection_of_handles()
    {
      if(not empty())
        delete_fn(std::get_deleter<typename pool_type::deleter>(_pool)->dispatcher.get(), _pool.get(), size(), data());
    }

    constexpr collection_of_handles(collection_of_handles &&)                 = default;
    constexpr collection_of_handles(collection_of_handles const &)            = delete;
    constexpr collection_of_handles &operator=(collection_of_handles &&)      = default;
    constexpr collection_of_handles &operator=(collection_of_handles const &) = delete;

  private:
    template <auto, auto, class, class>
    friend struct make_collection_fn;

    constexpr collection_of_handles(auto const &pool, std::vector<value_type> &&ptrs) noexcept
    : _pool(pool),
      _ptrs(std::move(ptrs))
    {
    }

    std::shared_ptr<typename pool_type::element_type> _pool;
    std::vector<value_type>                           _ptrs;
};

template <auto delete_fn, class dispatcher_pointer, class managed_pointer>
using unique_handle = handle<smart_type::unique, delete_fn, dispatcher_pointer, managed_pointer>;

template <auto delete_fn, class dispatcher_pointer, class managed_pointer>
using shared_handle = handle<smart_type::shared, delete_fn, dispatcher_pointer, managed_pointer>;

template <template <auto, class, class> class handle_type, auto create_fn, auto delete_fn, class managed_pointer>
struct make_handle_fn final
{
    constexpr auto operator()(auto const &dispatcher, auto const &info, std::source_location const &location)
    requires std::invocable<decltype(create_fn), decltype(dispatcher.get()), decltype(info), std::nullptr_t, managed_pointer *>
    {
      auto       ptr    = managed_pointer{};
      auto const result = create_fn(dispatcher.get(), info, nullptr, &ptr);
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(location.function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult. (" + std::to_string(result) +
                                 ")");
      return handle_type<delete_fn, decltype(dispatcher.get()), managed_pointer>(dispatcher, ptr);
    }
};

template <auto create_fn, auto delete_fn, class managed_pointer, class pool_type>
struct make_collection_fn final
{
    constexpr auto operator()(auto const                 &pool,
                              auto const                 &info,
                              std::uint32_t const         count,
                              std::source_location const &location)
    requires std::invocable<decltype(create_fn),
                            decltype(std::declval<typename pool_type::deleter>().dispatcher.get()),
                            decltype(info),
                            managed_pointer *>
    {
      auto       ptrs   = std::vector<managed_pointer>(count);
      auto const result = create_fn(std::get_deleter<typename pool_type::deleter>(pool)->dispatcher.get(), info, ptrs.data());
      if(std::to_underlying(result) < 0)
        throw std::runtime_error(std::string(location.function_name()) +
                                 ":\033[1;31m error:\033[0m vulkan return a negative VkResult. (" + std::to_string(result) +
                                 ")");
      return collection_of_handles<delete_fn, managed_pointer, pool_type>(pool, std::move(ptrs));
    }
};

template <auto create_fn, auto delete_fn, class managed_pointer>
[[nodiscard]]
constexpr auto make_unique(auto const          &dispatcher,
                           auto const          &info,
                           std::source_location location = std::source_location::current())
{
  return make_handle_fn<unique_handle, create_fn, delete_fn, managed_pointer>{}(dispatcher, info, location);
}

template <auto create_fn, auto delete_fn, class managed_pointer>
[[nodiscard]]
constexpr auto make_shared(auto const          &dispatcher,
                           auto const          &info,
                           std::source_location location = std::source_location::current())
{
  return make_handle_fn<shared_handle, create_fn, delete_fn, managed_pointer>{}(dispatcher, info, location);
}

template <auto create_fn, auto delete_fn, class managed_pointer, class pool_type>
[[nodiscard]]
constexpr auto make_collection(auto const          &pool,
                               auto const          &info,
                               std::uint32_t const  count,
                               std::source_location location = std::source_location::current())
{
  return make_collection_fn<create_fn, delete_fn, managed_pointer, pool_type>{}(pool, info, count, location);
}
}

namespace vulkan::ext::internal
{
VkResult create_debug_utils_messenger(VkInstance                                dispatcher,
                                      VkDebugUtilsMessengerCreateInfoEXT const *info,
                                      VkAllocationCallbacks const              *allocator,
                                      VkDebugUtilsMessengerEXT                 *ptr) noexcept;

VkResult create_debug_report_callback(VkInstance                                dispatcher,
                                      VkDebugReportCallbackCreateInfoEXT const *info,
                                      VkAllocationCallbacks const              *allocator,
                                      VkDebugReportCallbackEXT                 *ptr) noexcept;

void destroy_debug_report_callback(VkInstance                   dispatcher,
                                   VkDebugReportCallbackEXT     ptr,
                                   VkAllocationCallbacks const *allocator) noexcept;

void destroy_debug_utils_messenger(VkInstance                   dispatcher,
                                   VkDebugUtilsMessengerEXT     ptr,
                                   VkAllocationCallbacks const *allocator) noexcept;
}
