#include "create_surface.hpp"

vk::UniqueSurfaceKHR graphics::detail::vulkan_config::create_surface(vk::Instance const instance, GLFWwindow * const window)
{
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  auto const   result  = glfwCreateWindowSurface(instance, window, nullptr, &surface);

  switch(result)
  {
    case VK_ERROR_INITIALIZATION_FAILED :
      throw vk::InitializationFailedError("failed to create window surface");
    case VK_ERROR_EXTENSION_NOT_PRESENT :
      throw vk::ExtensionNotPresentError("failed to create window surface");
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
      throw vk::NativeWindowInUseKHRError("failed to create window surface");
    default :
    {
      assert(result == VK_SUCCESS);
      return vk::UniqueSurfaceKHR(surface, {instance});
    }
  }
}