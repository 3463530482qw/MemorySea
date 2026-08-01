void createCommandBuffers(const vk::raii::Device& device, const vk::raii::CommandPool& commandPool, uint32_t count);
void recordCommandBuffers(const vk::raii::RenderPass& renderPass, const std::vector<vk::raii::Framebuffer>& framebuffers, vk::Extent2D framebufferExtent, vk::Offset2D vpOffset = {}, vk::Extent2D vpExtent = {});
