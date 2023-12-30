#include "exception.hpp"

namespace glfw
{
bad_handle_access::bad_handle_access()
: exception("bad handle access")
{
}
}