#pragma once

#include "non_dispatchable.hpp"

namespace vulkan
{
struct command_buffers;
struct device;
struct instance;
struct physical_device;
struct queue;

using buffer                = non_dispatchable<device_handle, buffer_handle>;
using buffer_view           = non_dispatchable<device_handle, buffer_view_handle>;
using command_pool          = non_dispatchable<device_handle, command_pool_handle>;
using descriptor_pool       = non_dispatchable<device_handle, descriptor_pool_handle>;
using descriptor_set_layout = non_dispatchable<device_handle, descriptor_set_layout_handle>;
using descriptor_sets       = non_dispatchable<descriptor_pool_handle, descriptor_sets_handle>;
using device_memory         = non_dispatchable<device_handle, device_memory_handle>;
using event                 = non_dispatchable<device_handle, event_handle>;
using fence                 = non_dispatchable<device_handle, fence_handle>;
using framebuffer           = non_dispatchable<device_handle, framebuffer_handle>;
using image                 = non_dispatchable<device_handle, image_handle>;
using image_view            = non_dispatchable<device_handle, image_view_handle>;
using pipeline_cache        = non_dispatchable<device_handle, pipeline_cache_handle>;
using pipeline              = non_dispatchable<device_handle, pipeline_handle>;
using pipeline_layout       = non_dispatchable<device_handle, pipeline_layout_handle>;
using query_pool            = non_dispatchable<device_handle, query_pool_handle>;
using render_pass           = non_dispatchable<device_handle, render_pass_handle>;
using sampler               = non_dispatchable<device_handle, sampler_handle>;
using semaphore             = non_dispatchable<device_handle, semaphore_handle>;
using shader_module         = non_dispatchable<device_handle, shader_module_handle>;

namespace ext
{
using debug_report_callback = non_dispatchable<instance_handle, debug_report_callback_handle>;
using debug_utils_messenger = non_dispatchable<instance_handle, debug_utils_messenger_handle>;
}

namespace khr
{
using surface   = non_dispatchable<instance_handle, surface_handle>;
using swapchain = non_dispatchable<device_handle, swapchain_handle>;
}
}