#include "create_debug_utils_messenger.hpp"

#include <graphics/render_window.hpp>

#include <chrono>
#include <ostream>
#include <stdexcept>

namespace
{
vk::Bool32 callback(vk::DebugUtilsMessageSeverityFlagBitsEXT       message_severity,
                    vk::DebugUtilsMessageTypeFlagsEXT              message_type,
                    vk::DebugUtilsMessengerCallbackDataEXT const * callback_data,
                    void *)
{
  auto & log = [message_severity]() -> std::ostream &
  {
    switch(message_severity)
    {
      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose :
        return graphics::render_window::verbose_out;
      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo :
        return graphics::render_window::info_out;
      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning :
        return graphics::render_window::warning_out;
      case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError :
        return graphics::render_window::error_out;
    }

    throw std::invalid_argument("invalid message severity: " + vk::to_string(message_severity));
  }();

  if(not log)
    return vk::False;

  std::stringstream buffer;

  buffer << vk::to_string(message_type) << " { " << std::chrono::system_clock::now() << " } ";

  if(callback_data and callback_data->pMessage)
    buffer << callback_data->pMessage << "\n";

  log << buffer.str();

  return vk::False;
}
}

vk::DebugUtilsMessengerCreateInfoEXT graphics::detail::vulkan_config::create_debug_utils_messenger_create_info()
{
  auto const message_severity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;

  auto const message_type = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;

  auto const user_callback = [](auto message_severity, auto message_type, auto callback_data, auto user_data) -> VKAPI_ATTR VkBool32 VKAPI_CALL
  {
    return callback(static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(message_severity),
                    static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(message_type),
                    reinterpret_cast<vk::DebugUtilsMessengerCallbackDataEXT const *>(callback_data),
                    user_data);
  };

  return {
    .messageSeverity = message_severity,
    .messageType     = message_type,
    .pfnUserCallback = user_callback,
  };
}

vk::UniqueDebugUtilsMessengerEXT graphics::detail::vulkan_config::create_debug_utils_messenger(vk::Instance const instance)
{
  return instance.createDebugUtilsMessengerEXTUnique(create_debug_utils_messenger_create_info());
}
