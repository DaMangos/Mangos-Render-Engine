#include "device.hpp"

#include "command_buffers.hpp"
#include "functional.hpp"
#include "queue.hpp"

#include <vector>

namespace vulkan
{
device::device(pointer device, deleter_type &&deleter)
: _device(device, deleter)
{
}

device::pointer device::get() const noexcept
{
  return _device.get();
}

buffer device::create_buffer(VkBufferCreateInfo create_info) const
{
  buffer::pointer ptr;
  return return_or_throw(vkCreateBuffer(get(), &create_info, nullptr, &ptr),
                         "vkCreateBuffer",
                         buffer(ptr, [device = get()](buffer::pointer ptr) { vkDestroyBuffer(device, ptr, nullptr); }));
}

image device::create_image(VkImageCreateInfo create_info) const
{
  image::pointer ptr;
  return return_or_throw(vkCreateImage(get(), &create_info, nullptr, &ptr),
                         "vkCreateImage",
                         image(ptr, [device = get()](image::pointer ptr) -> void { vkDestroyImage(device, ptr, nullptr); }));
}

semaphore device::create_semaphore(VkSemaphoreCreateInfo create_info) const
{
  semaphore::pointer ptr;
  return return_or_throw(
    vkCreateSemaphore(get(), &create_info, nullptr, &ptr),
    "vkCreateSemaphore",
    semaphore(ptr, [device = get()](semaphore::pointer ptr) -> void { vkDestroySemaphore(device, ptr, nullptr); }));
}

fence device::create_fence(VkFenceCreateInfo create_info) const
{
  fence::pointer ptr;
  return return_or_throw(vkCreateFence(get(), &create_info, nullptr, &ptr),
                         "vkCreateFence",
                         fence(ptr, [device = get()](fence::pointer ptr) -> void { vkDestroyFence(device, ptr, nullptr); }));
}

device_memory device::allocate_device_memory(VkMemoryAllocateInfo allocate_info) const
{
  device_memory::pointer ptr;
  return return_or_throw(
    vkAllocateMemory(get(), &allocate_info, nullptr, &ptr),
    "vkAllocateMemory",
    device_memory(ptr, [device = get()](device_memory::pointer ptr) -> void { vkFreeMemory(device, ptr, nullptr); }));
}

event device::create_event(VkEventCreateInfo create_info) const
{
  event::pointer ptr;
  return return_or_throw(vkCreateEvent(get(), &create_info, nullptr, &ptr),
                         "vkCreateEvent",
                         event(ptr, [device = get()](event::pointer ptr) -> void { vkDestroyEvent(device, ptr, nullptr); }));
}

query_pool device::create_query_pool(VkQueryPoolCreateInfo create_info) const
{
  query_pool::pointer ptr;
  return return_or_throw(
    vkCreateQueryPool(get(), &create_info, nullptr, &ptr),
    "vkCreateQueryPool",
    query_pool(ptr, [device = get()](query_pool::pointer ptr) -> void { vkDestroyQueryPool(device, ptr, nullptr); }));
}

buffer_view device::create_buffer_view(VkBufferViewCreateInfo create_info) const
{
  buffer_view::pointer ptr;
  return return_or_throw(
    vkCreateBufferView(get(), &create_info, nullptr, &ptr),
    "vkCreateBufferView",
    buffer_view(ptr, [device = get()](buffer_view::pointer ptr) -> void { vkDestroyBufferView(device, ptr, nullptr); }));
}

image_view device::create_image_view(VkImageViewCreateInfo create_info) const
{
  image_view::pointer ptr;
  return return_or_throw(
    vkCreateImageView(get(), &create_info, nullptr, &ptr),
    "vkCreateImageView",
    image_view(ptr, [device = get()](image_view::pointer ptr) -> void { vkDestroyImageView(device, ptr, nullptr); }));
}

shader_module device::create_shader_module(VkShaderModuleCreateInfo create_info) const
{
  shader_module::pointer ptr;
  return return_or_throw(
    vkCreateShaderModule(get(), &create_info, nullptr, &ptr),
    "vkCreateShaderModule",
    shader_module(ptr, [device = get()](shader_module::pointer ptr) -> void { vkDestroyShaderModule(device, ptr, nullptr); }));
}

pipeline_cache device::create_pipeline_cache(VkPipelineCacheCreateInfo create_info) const
{
  pipeline_cache::pointer ptr;
  return return_or_throw(vkCreatePipelineCache(get(), &create_info, nullptr, &ptr),
                         "vkCreatePipelineCache",
                         pipeline_cache(ptr,
                                        [device = get()](pipeline_cache::pointer ptr) -> void
                                        { vkDestroyPipelineCache(device, ptr, nullptr); }));
}

pipeline_layout device::create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const
{
  pipeline_layout::pointer ptr;
  return return_or_throw(vkCreatePipelineLayout(get(), &create_info, nullptr, &ptr),
                         "vkCreatePipelineLayout",
                         pipeline_layout(ptr,
                                         [device = get()](pipeline_layout::pointer ptr) -> void
                                         { vkDestroyPipelineLayout(device, ptr, nullptr); }));
}

render_pass device::create_render_pass(VkRenderPassCreateInfo create_info) const
{
  render_pass::pointer ptr;
  return return_or_throw(
    vkCreateRenderPass(get(), &create_info, nullptr, &ptr),
    "vkCreateRenderPass",
    render_pass(ptr, [device = get()](render_pass::pointer ptr) -> void { vkDestroyRenderPass(device, ptr, nullptr); }));
}

descriptor_set_layout device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo create_info) const
{
  descriptor_set_layout::pointer ptr;
  return return_or_throw(vkCreateDescriptorSetLayout(get(), &create_info, nullptr, &ptr),
                         "vkCreateDescriptorSetLayout",
                         descriptor_set_layout(ptr,
                                               [device = get()](descriptor_set_layout::pointer ptr) -> void
                                               { vkDestroyDescriptorSetLayout(device, ptr, nullptr); }));
}

sampler device::create_sampler(VkSamplerCreateInfo create_info) const
{
  sampler::pointer ptr;
  return return_or_throw(
    vkCreateSampler(get(), &create_info, nullptr, &ptr),
    "vkCreateSampler",
    sampler(ptr, [device = get()](sampler::pointer ptr) -> void { vkDestroySampler(device, ptr, nullptr); }));
}

descriptor_sets device::allocate_descriptor_sets(VkDescriptorSetAllocateInfo allocate_info) const
{
  descriptor_sets::pointer ptr = new descriptor_sets::element_type[allocate_info.descriptorSetCount];
  return return_or_throw(vkAllocateDescriptorSets(get(), &allocate_info, ptr),
                         "vkAllocateDescriptorSets",
                         descriptor_sets(allocate_info.descriptorSetCount,
                                         ptr,
                                         [device          = get(),
                                          descriptor_pool = allocate_info.descriptorPool,
                                          count = allocate_info.descriptorSetCount](descriptor_sets::pointer ptr) -> void
                                         {
                                           vkFreeDescriptorSets(device, descriptor_pool, count, ptr);
                                           delete[] ptr;
                                         }));
}

descriptor_pool device::create_descriptor_pool(VkDescriptorPoolCreateInfo create_info) const
{
  descriptor_pool::pointer ptr;
  return return_or_throw(vkCreateDescriptorPool(get(), &create_info, nullptr, &ptr),
                         "vkCreateDescriptorPool",
                         descriptor_pool(ptr,
                                         [device = get()](descriptor_pool::pointer ptr) -> void
                                         { vkDestroyDescriptorPool(device, ptr, nullptr); }));
}

framebuffer device::create_framebuffer(VkFramebufferCreateInfo create_info) const
{
  framebuffer::pointer ptr;
  return return_or_throw(
    vkCreateFramebuffer(get(), &create_info, nullptr, &ptr),
    "vkCreateFramebuffer",
    framebuffer(ptr, [device = get()](framebuffer::pointer ptr) -> void { vkDestroyFramebuffer(device, ptr, nullptr); }));
}

command_pool device::create_command_pool(VkCommandPoolCreateInfo create_info) const
{
  command_pool::pointer ptr;
  return return_or_throw(
    vkCreateCommandPool(get(), &create_info, nullptr, &ptr),
    "vkCreateCommandPool",
    command_pool(ptr, [device = get()](command_pool::pointer ptr) -> void { vkDestroyCommandPool(device, ptr, nullptr); }));
}

command_buffers device::allocate_command_buffers(VkCommandBufferAllocateInfo allocate_info) const
{
  command_buffers::pointer ptr = new command_buffers::element_type[allocate_info.commandBufferCount];
  return return_or_throw(vkAllocateCommandBuffers(get(), &allocate_info, ptr),
                         "vkAllocateCommandBuffers",
                         command_buffers(allocate_info.commandBufferCount,
                                         ptr,
                                         [device       = get(),
                                          command_pool = allocate_info.commandPool,
                                          count        = allocate_info.commandBufferCount](command_buffers::pointer ptr) -> void
                                         {
                                           vkFreeCommandBuffers(device, command_pool, count, ptr);
                                           delete[] ptr;
                                         }));
}

queue device::get_device_queue(VkDeviceQueueInfo2 queue_info) const
{
  queue::pointer ptr;
  vkGetDeviceQueue2(get(), &queue_info, &ptr);
  return queue(ptr);
}

std::vector<pipeline> device::create_compute_pipeline(VkPipelineCache                          pipeline_cache,
                                                      std::vector<VkComputePipelineCreateInfo> create_infos) const
{
  std::vector<pipeline::pointer> ptrs;
  return return_or_throw(
    vkCreateComputePipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, ptrs.data()),
    "vkCreateComputePipelines",
    [&]() -> std::vector<pipeline>
    {
      std::vector<pipeline> pipelines;
      for(auto ptr : ptrs)
        pipelines.emplace_back(
          pipeline(ptr, [device = get()](pipeline::pointer ptr) -> void { vkDestroyPipeline(device, ptr, nullptr); }));
      return pipelines;
    }());
}

std::vector<pipeline> device::create_graphics_pipeline(VkPipelineCache                           pipeline_cache,
                                                       std::vector<VkGraphicsPipelineCreateInfo> create_infos) const
{
  std::vector<pipeline::pointer> ptrs;
  return return_or_throw(
    vkCreateGraphicsPipelines(get(), pipeline_cache, to_count(create_infos), create_infos.data(), nullptr, ptrs.data()),
    "vkCreateGraphicsPipelines",
    [&]() -> std::vector<pipeline>
    {
      std::vector<pipeline> pipelines;
      for(auto ptr : ptrs)
        pipelines.emplace_back(
          pipeline(ptr, [device = get()](pipeline::pointer ptr) -> void { vkDestroyPipeline(device, ptr, nullptr); }));
      return pipelines;
    }());
}

khr::swapchain device::create_swapchain(VkSwapchainCreateInfoKHR create_info) const
{
  khr::swapchain::pointer ptr;
  return return_or_throw(vkCreateSwapchainKHR(get(), &create_info, nullptr, &ptr),
                         "vkCreateSwapchainKHR",
                         khr::swapchain(ptr,
                                        [device = get()](khr::swapchain::pointer ptr) -> void
                                        { vkDestroySwapchainKHR(device, ptr, nullptr); }));
}

// khr::video_session device::create_video_session(VkVideoSessionCreateInfoKHR create_info) const
// {
//   khr::video_session::pointer ptr;
//   return return_or_throw(vkCreateVideoSessionKHR(get(), &create_info, nullptr, &ptr),
//                          "vkCreateVideoSessionKHR",
//                          khr::video_session(ptr,
//                                             [device = get()](khr::video_session::pointer ptr) -> void
//                                            { vkDestroyVideoSessionKHR(device, ptr, nullptr); }));
// }

// khr::video_session_parameters device::create_video_session_parameters(VkVideoSessionParametersCreateInfoKHR create_info)
// const
// {
//   khr::video_session_parameters::pointer ptr;
//   return return_or_throw(vkCreateVideoSessionParametersKHR(get(), &create_info, nullptr, &ptr),
//                          "vkCreateVideoSessionParametersKHR",
//                          khr::video_session_parameters(ptr,
//                                                        [device = get()](khr::video_session_parameters::pointer ptr) -> void
//                                                        { vkDestroyVideoSessionParametersKHR(device, ptr, nullptr); }));
// }

// khr::deferred_operation device::create_deferred_operation() const
// {
//   khr::deferred_operation::pointer ptr;
//   return return_or_throw(vkCreateDeferredOperationKHR(get(), nullptr, &ptr),
//                          "vkCreateDeferredOperationKHR",
//                          khr::deferred_operation(ptr,
//                                                  [device = get()](khr::deferred_operation::pointer ptr) -> void
//                                                  { vkDestroyDeferredOperationKHR(device, ptr, nullptr); }));
// }

// khr::acceleration_structure device::create_acceleration_structure(VkAccelerationStructureCreateInfoKHR create_info) const
// {
//   khr::acceleration_structure::pointer ptr;
//   return return_or_throw(vkCreateAccelerationStructureKHR(get(), &create_info, nullptr, &ptr),
//                          "vkCreateAccelerationStructureKHR",
//                          khr::acceleration_structure(ptr,
//                                                      [device = get()](khr::acceleration_structure::pointer ptr) -> void
//                                                      { vkDestroyAccelerationStructureKHR(device, ptr, nullptr); }));
// }

// ext::validation_cache device::create_validation_cache(VkValidationCacheCreateInfoEXT create_info) const
// {
//   ext::validation_cache::pointer ptr;
//   return return_or_throw(vkCreateValidationCacheEXT(get(), &create_info, nullptr, &ptr),
//                          "vkCreateValidationCacheEXT",
//                          ext::validation_cache(ptr,
//                                                [device = get()](ext::validation_cache::pointer ptr) -> void
//                                                { vkDestroyValidationCacheEXT(device, ptr, nullptr); }));
// }

// ext::micromap device::create_micromap(VkMicromapCreateInfoEXT create_info) const
// {
//   ext::micromap::pointer ptr;
//   return return_or_throw(
//     vkCreateMicromapEXT(get(), &create_info, nullptr, &ptr),
//     "vkCreateMicromapEXT",
//     ext::micromap(ptr, [device = get()](ext::micromap::pointer ptr) -> void { vkDestroyMicromapEXT(device, ptr, nullptr);
//     }));
// }

// std::vector<ext::shader> device::create_shader(std::vector<VkShaderCreateInfoEXT> create_infos) const
// {
//   std::vector<ext::shader::pointer> ptrs;
//   return return_or_throw(vkCreateShadersEXT(get(), to_count(create_infos), create_infos.data(), nullptr, ptrs.data()),
//                          "vkCreateShadersEXT",
//                          [&]() -> std::vector<ext::shader>
//                          {
//                            std::vector<ext::shader> pipelines;
//                            for(auto ptr : ptrs)
//                              pipelines.emplace_back(ext::shader(ptr,
//                                                                 [device = get()](ext::shader::pointer ptr) -> void
//                                                                 { vkDestroyShaderEXT(device, ptr, nullptr); }));
//                            return pipelines;
//                          }());
// }
}