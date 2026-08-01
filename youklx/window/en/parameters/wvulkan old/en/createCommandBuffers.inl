namespace youklx {
    void Wvulkan::createCommandBuffers(const vk::raii::Device& device) {
        commandBuffer.createCommandBuffers(
            device,
            commandPool.commandPool,
            static_cast<uint32_t>(swapchain.imageViews.size())
        );
    }
}
