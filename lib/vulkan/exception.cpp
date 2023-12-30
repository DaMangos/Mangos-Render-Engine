#include "exception.hpp"

#include <utility>

namespace vulkan
{
bad_result::bad_result(VkResult result)
: exception("bad result (" + std::to_string(std::to_underlying(result)) + ")")
{
}

bad_result::bad_result(VkResult result, std::string const &message)
: exception("bad result (" + std::to_string(std::to_underlying(result)) + ") : " + message)
{
}

bad_handle_access::bad_handle_access()
: exception("bad handle access")
{
}

not_found::not_found(std::string const &name)
: exception(name + "not found")
{
}
}