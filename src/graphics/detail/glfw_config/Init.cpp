#include <GLFW/glfw3.h>

#include <system_error>

namespace
{
class glfw_category_type : public std::error_category
{
  public:
    [[nodiscard]]
    char const * name() const noexcept override
    {
      return "GLFW";
    }

    [[nodiscard]]
    std::string message(int const error_code) const override
    {
      switch(error_code)
      {
        case GLFW_NOT_INITIALIZED :
          return "GLFW has not been initialized";
        case GLFW_NO_CURRENT_CONTEXT :
          return "No context is current for this thread";
        case GLFW_INVALID_ENUM :
          return "One of the arguments to the function was an invalid enum value";
        case GLFW_INVALID_VALUE :
          return "One of the arguments to the function was an invalid value";
        case GLFW_OUT_OF_MEMORY :
          return "A memory allocation failed";
        case GLFW_API_UNAVAILABLE :
          return "GLFW could not find support for the requested API on the system";
        case GLFW_VERSION_UNAVAILABLE :
          return "The requested OpenGL or OpenGL ES version is not available";
        case GLFW_PLATFORM_ERROR :
          return "A platform-specific error occurred that does not match any of the more specific categories";
        case GLFW_FORMAT_UNAVAILABLE :
          return "The specified format is not supported or available";
        case GLFW_NO_WINDOW_CONTEXT :
          return "The specified _window does not have an OpenGL or OpenGL ES context";
        case GLFW_CURSOR_UNAVAILABLE :
          return "The specified cursor shape is not available";
        case GLFW_FEATURE_UNAVAILABLE :
          return "The requested feature is not provided by the platform";
        case GLFW_FEATURE_UNIMPLEMENTED :
          return "The requested feature is not implemented for the platform";
        case GLFW_PLATFORM_UNAVAILABLE :
          return "Platform unavailable or no matching platform was found";
        default :
          throw std::invalid_argument("invalid GLFW error code: " + std::to_string(error_code));
      }
    }
};

class Init
{
  public:
    Init()
    {
      glfwSetErrorCallback(
        [](int const error_code, char const * const description)
        {
          static glfw_category_type const category;
          throw std::system_error(error_code, category, description);
        });

      glfwInit();
    }

    ~Init()
    {
      glfwTerminate();
    }

    Init(Init &&) = delete;

    Init(Init const &) = delete;

    Init & operator=(Init &&) = delete;

    Init & operator=(Init const &) = delete;
};

Init const init = {};
}
