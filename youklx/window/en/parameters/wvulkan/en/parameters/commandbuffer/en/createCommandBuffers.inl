namespace youklx {
    void CommandBuffer::createCommandBuffers(
        const vk::raii::Device& device,
        const vk::raii::CommandPool& commandPool,
        uint32_t count
    ) {
        // 从命令池中分配 count 个主命令缓冲
        vk::CommandBufferAllocateInfo allocInfo;
        allocInfo.setCommandPool(*commandPool);
        allocInfo.setLevel(vk::CommandBufferLevel::ePrimary);
        allocInfo.setCommandBufferCount(count);

        commandBuffers = vk::raii::CommandBuffers(device, allocInfo);
    }
}
